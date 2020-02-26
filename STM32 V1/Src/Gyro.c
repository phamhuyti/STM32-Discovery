#include "RegisterAddresses.h"
#include "SPI.h"
// See page 25 of the L3GD20 datasheet for details on how we send commands to, and make
// queries of, the gyro.  If you look at figure 14 of UM1842 on page 33 you'll see how
// the L3GD20 pins are connected to the STM32F411:
//    CS  --> PE3   // Chip Select
//    SPC --> PA5   // Clock
//    SDI --> PA7   // Data In
//    SDO --> PA6   // Data Out
// As shown on page 25 of the L3GD20 communication with the gyro takes the following steps:
// 1) The chip select must go from high to low to indicate we're doing a read or write.
// 2) The first byte we send is the register of the gyro (combined with 0x80 if we're going
//    to do a read operation).
// 3) Do a read from SDO
// 4) Write the next byte
// 5) Read a result
// 6) Set CS back to high

void WriteGyro(unsigned char gyroRegister, unsigned char value)
{
	ACCESS(GPIOE_BSRR) |= (1 << 19);
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = gyroRegister;
	WaitForSPI1RXReady();
	ACCESS(SPI1_DR);  // I believe we need this simply because a read must follow a write
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = value;
	WaitForSPI1RXReady();
	ACCESS(SPI1_DR);  // Don't care what valley the device put into the data register
	ACCESS(GPIOE_BSRR) |= (1 << 3);
}
unsigned char ReadGyro(unsigned char gyroRegister)
{
	ACCESS(GPIOE_BSRR) |= (1 << 19);
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = (gyroRegister | 0x80); // 0x80 indicates we're doing a read
	WaitForSPI1RXReady();
	ACCESS(SPI1_DR);  // I believe we need this simply because a read must follow a write
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = 0xFF;
	WaitForSPI1RXReady();
	volatile unsigned char readValue = (unsigned char)ACCESS(SPI1_DR);
	ACCESS(GPIOE_BSRR) |= (1 << 3);

	return readValue;
}

void GyroInit()
{
	// See page 31 of the L3GD20 datasheet.  If communication to the gyro is properly
	// setup, reading from register 0x0F will give us b11010100 (0xD4).
	if(ReadGyro(0x0F) != 0xD4)
	{
		// Initializing Gyro Device Failed
	}

	// See page 31 of the L3GD20 datasheet.  Writing 0x0F to register 0x20 will power up
	// the gyro and enables the X, Y, Z axes.
	WriteGyro(0x20, 0x0F);
}

short GetAxisValue(unsigned char lowRegister, unsigned char highRegister)
{
	// See page 9 of L3GD20.  It shows the mechanical characteristics of the gyro.  Note
	// that we leave the sensitivity as is (i.e. 0) so that it's 250 dps.  So, we read
	// the value from the gyro and convert it to a +/- 360 degree value.
	float scaler = 8.75 * 0.001;
	short temp = (ReadGyro(lowRegister) | (ReadGyro(highRegister) << 8));
	return (short)((float)temp * scaler);
}

void GetGyroValues(short* x, short* y, short* z)
{
	// See page 36 of the L3GD20 datasheet.  It shows the hi/lo addresses of each of the axes.
	*x = GetAxisValue(0x28, 0x29);
	*y = GetAxisValue(0x2A, 0x2B);
	*z = GetAxisValue(0x2C, 0x2D);
}
