#include "main.h"

#define Wheel_Pulse_Port GPIOA
#define Wheel_Pulse_1 GPIO_PIN_0
#define Wheel_Pulse_2 GPIO_PIN_1
#define Wheel_Pulse_3 GPIO_PIN_2
#define Wheel_Pulse_4 GPIO_PIN_3

#define Wheel_Dir_Port GPIOB
#define Wheel_Dir_1 GPIO_PIN_4
#define Wheel_Dir_2 GPIO_PIN_5
#define Wheel_Dir_3 GPIO_PIN_6
#define Wheel_Dir_4 GPIO_PIN_7

#define Clockwise GPIO_PIN_SET
#define AntiClockwise GPIO_PIN_RESET

void Wheel_GPIO_Init(void);
void moveSidewaysLeft(void);
void moveSidewaysRight(void);
void moveForward(void);
void moveBackward(void);
void moveRightForward(void);
void moveLeftForward(void);
void moveRightBackward(void);
void moveLeftBackward(void);
void moveclockwise(void);
void moveAnticlockwise(void);
