#include "main.h"
void Gyro(void);
unsigned char ReadGyro(unsigned char gyroRegister);
void WriteGyro(uint8_t gyroRegister, uint8_t val);
short GetAxisValue(unsigned char lowRegister, unsigned char highRegister);
void GetGyroValues(short* x, short* y, short* z);
// void GetGyroValues();
