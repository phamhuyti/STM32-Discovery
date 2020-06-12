#include "main.h"
#include "cmsis_os.h"
#define Wheel_Pulse_Port GPIOE
#define Wheel_Pulse_1 GPIO_PIN_7
#define Wheel_Pulse_2 GPIO_PIN_8
#define Wheel_Pulse_3 GPIO_PIN_9
#define Wheel_Pulse_4 GPIO_PIN_10

#define Wheel_Dir_Port GPIOE
#define Wheel_Dir_1 GPIO_PIN_11
#define Wheel_Dir_2 GPIO_PIN_12
#define Wheel_Dir_3 GPIO_PIN_13
#define Wheel_Dir_4 GPIO_PIN_14

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
