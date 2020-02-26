#include "RegisterAddresses.h"
void WaitForSPI1RXReady(void)
{
	// See page 605 of the datasheet for info on the SPI status register
	// If Bit0 == 0 then SPI RX is empty
	// If Bit7 == 1 then SPI is busy
	while((ACCESS(SPI1_SR) & 1) == 0 || (ACCESS(SPI1_SR) & (1 << 7)) == 1) { }
}

void WaitForSPI1TXReady(void)
{
	// See page 605 of the datasheet for info on the SPI status register
	// If Bit1 == 0 then SPI TX buffer is not empty
	// If Bit7 == 1 then SPI is busy
	while((ACCESS(SPI1_SR) & (1 << 1)) == 0 || (ACCESS(SPI1_SR) & (1 << 7)) == 1) { }
}

void SPI_Init(void){
	// Give a clock to port A as pins PA5-thru-PA7 are connected to the gyro (pg 20 of UM1842) and
	// page 116 of RM0383 for the RCC AHB register info.
	ACCESS(RCC_AHB1ENR) |= 1;

	// Give a clock to port E as pin PE3 is connected to the chip select of the gyro (pg 20 of
	// UM1842) and page 116 of RM0383 for the RCC AHB register info.
	ACCESS(RCC_AHB1ENR) |= (1 << 4);

	// See pg 20 of the ST UM1842 document.  We'll be using SPI1 to communicate with the gyro.
	// See pg 149 of RM0383.  It shows SPI1 to be alternate function 5.
	// See pg 156 of RM0383 for documentation on the GPIO mode register.  It shows how to set
	// pins to alternate mode.  We do this for pins PA5, PA6, PA7.
	ACCESS(GPIOA_MODER) |= ((1 << 11) | (1 << 13) | (1 << 15));
	ACCESS(GPIOE_MODER) |= (1 << 6)|(1 << 4)|(1 << 2);

	// See pg 149 of ST RM0383 document.  SPI1 is AF5.  And pg 160 of the same document shows
	// alternate function for pin 5 = bits 20-23, pin 6 = bits 24-27, pin 7 = bits 28-31.
	// We set these to 5.
	ACCESS(GPIOA_AFRL) |= ((5 << 20) | (5 << 24) | (5 << 28));

	// Set the pins to fast speed.  See pg 157 for more info on the register.  Pin 5 corresponds to
	// bits 10/11, 6=12/13, and 7=14,15.  And for port E pin 3 corresponds to bits 6/7,2=4/5.
	ACCESS(GPIOA_OSPEEDR) |= ((2 << 10) | (2 << 12) | (2 << 14));
	ACCESS(GPIOE_OSPEEDR) |= (2 << 6)|(2 << 4)|(2 << 2);

	// Enable clock for SPI1
	ACCESS(RCC_APB2ENR) |= (1 << 12);

	// See page 602 for details of configuring SPI1 Control Register
	// Set Bit 0: The second clock transition is the first data capture edge
	// Set Bit 1: CK to 1 when idle
	// Set Bit 2: The STM32 is the master, the gyro is the slave
	// Set Bits 3-5 to 010 for a baud rate of fPCLK/8
	// Set Bits 8-9: Software slave management enabled, Internal slave select to 1
	ACCESS(SPI1_CR1) |= (1 | (1 << 1) | (1 << 2) | (2 << 3) | (1 << 8) | (1 << 9));

	// Set Bit 6: Enable SPI.  See page 603.
	ACCESS(SPI1_CR1) |= (1 << 6);

	// Set the CS high on the gyro as setting it low indicates communication.  See
	// 25 of the L3GD20 datasheet and page 159 of RM0383 for more info on BSRR.
	ACCESS(GPIOE_BSRR) |= (1 << 3)|(1 << 2)|(1 << 1);
}
