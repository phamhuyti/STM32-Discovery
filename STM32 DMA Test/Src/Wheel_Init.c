#include "Wheel_Init.h"

void Wheel_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  // __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_1 | Wheel_Dir_2 | Wheel_Dir_3 | Wheel_Dir_4, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1 | Wheel_Pulse_2 | Wheel_Pulse_3 | Wheel_Pulse_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : Wheel_Dir_1|Wheel_Dir_2|Wheel_Dir_3|Wheel_Dir_4 */
  GPIO_InitStruct.Pin = Wheel_Dir_1 | Wheel_Dir_2 | Wheel_Dir_3 | Wheel_Dir_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(Wheel_Dir_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Wheel_Pulse_1|Wheel_Pulse_2|Wheel_Pulse_3|Wheel_Pulse_4 */
  GPIO_InitStruct.Pin = Wheel_Pulse_1 | Wheel_Pulse_2 | Wheel_Pulse_3 | Wheel_Pulse_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(Wheel_Pulse_Port, &GPIO_InitStruct);
}
/**
  * @brief move Sideways Left
  * @retval None
  */
void moveSidewaysLeft(void)
{
  HAL_GPIO_WritePin(LD_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_3, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_4, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, Clockwise);
  // osDelay(2);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, AntiClockwise);
  osDelay(2);
}
/**
  * @brief move Sideways Right
  * @retval None
  */
void moveSidewaysRight(void)
{
  HAL_GPIO_WritePin(LD_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_3, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_4, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, Clockwise);
  // osDelay(2);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, AntiClockwise);
  osDelay(2);
}
/**
  * @brief move Forward
  * @retval None
  */
void moveForward(void)
{
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_3, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_4, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, Clockwise);
  // osDelay(2);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, AntiClockwise);
  osDelay(2);
}
/**
  * @brief move Backward
  * @retval None
  */
void moveBackward(void)
{
  HAL_GPIO_WritePin(LD_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_3, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_4, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, Clockwise);
  // osDelay(2);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, AntiClockwise);
  osDelay(2);
}
/**
  * @brief move Right Forward
  * @retval None
  */
void moveRightForward(void)
{
  HAL_GPIO_WritePin(LD_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_3, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_4, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, Clockwise);
  // osDelay(2);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, AntiClockwise);
  osDelay(2);
}
/**
  * @brief move Left Forward
  * @retval None
  */
void moveLeftForward(void)
{
  HAL_GPIO_WritePin(LD_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_3, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_4, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, Clockwise);
  // osDelay(2);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, AntiClockwise);
  osDelay(2);
}
/**
  * @brief move Right Backward
  * @retval None
  */
void moveRightBackward(void)
{
  HAL_GPIO_WritePin(LD_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_3, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_4, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, Clockwise);
  // osDelay(2);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, AntiClockwise);
  osDelay(2);
}
/**
  * @brief move Left Backward
  * @retval None
  */
void moveLeftBackward(void)
{
  HAL_GPIO_WritePin(LD_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_3, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_4, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, Clockwise);
  // osDelay(2);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, AntiClockwise);
  osDelay(2);
}
/**
  * @brief move clockwise
  * @retval None
  */
void moveclockwise(void)
{
  HAL_GPIO_WritePin(LD_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_3, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_4, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, Clockwise);
  // osDelay(2);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, AntiClockwise);
  osDelay(2);
}
/**
  * @brief move anticlockwise
  * @retval None
  */
void moveAnticlockwise(void)
{
  HAL_GPIO_WritePin(LD_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LD_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_3, Clockwise);
  HAL_GPIO_WritePin(Wheel_Dir_Port, Wheel_Dir_4, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, Clockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, Clockwise);
  // osDelay(2);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_1, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_2, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_3, AntiClockwise);
  HAL_GPIO_WritePin(Wheel_Pulse_Port, Wheel_Pulse_4, AntiClockwise);
  osDelay(2);
}
