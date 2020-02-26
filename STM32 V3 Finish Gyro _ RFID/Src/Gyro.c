#include "Gyro.h"
#define Gyro_CS_LOW HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_RESET)
#define Gyro_CS_HIGH HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port,CS_I2C_SPI_Pin,GPIO_PIN_SET)
#define uint8_t unsigned char
extern SPI_HandleTypeDef hspi1;
void PORTGyro_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	/*Configure GPIO pin Output Level */
  	HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);
	/*Configure GPIO pin : CS_Gyro_SPI_Pin */
	GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);  
}
void Gyro(void){
    // See page 31 of the L3GD20 datasheet.  If communication to the gyro is properly
	// setup, reading from register 0x0F will give us b11010100 (0xD4).
	PORTGyro_Init();
    while(ReadGyro(0x0F) != 0xD4)
	{
		// Initializing Gyro Device Failed
        HAL_GPIO_TogglePin(LD5_GPIO_Port,LD5_Pin);
		HAL_Delay(50);
	}
    // See page 31 of the L3GD20 datasheet.  Writing 0x0F to register 0x20 will power up
	// the gyro and enables the X, Y, Z axes.
	WriteGyro(0x20, 0x0F);
}
uint8_t ReadGyro(uint8_t gyroRegister)
{
	Gyro_CS_LOW;
	gyroRegister = 0x80 | (gyroRegister);
	uint8_t readValue;
	HAL_SPI_Transmit(&hspi1,&gyroRegister,1,1);
	HAL_SPI_Receive(&hspi1,&readValue,1,1);
	Gyro_CS_HIGH;

	return readValue;
}
void WriteGyro(uint8_t gyroRegister, uint8_t val)
{
	Gyro_CS_LOW;
	HAL_SPI_Transmit(&hspi1,&gyroRegister,1,1);
	HAL_SPI_Transmit(&hspi1,&val,1,1);
	Gyro_CS_HIGH;
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
// void GetGyroValues()
void GetGyroValues(short* x, short* y, short* z)
{
	// See page 36 of the L3GD20 datasheet.  It shows the hi/lo addresses of each of the axes.
	*x = GetAxisValue(0x28, 0x29);
	*y = GetAxisValue(0x2A, 0x2B);
	*z = GetAxisValue(0x2C, 0x2D);
}
