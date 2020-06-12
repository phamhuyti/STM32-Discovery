#include "main.h"
extern UART_HandleTypeDef huart2;
// extern uint8_t bufferTX[6], bufferRX[6];
void GPIO_Init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LD_GPIO_Port, LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin, GPIO_PIN_RESET);
    set(M_GPIO_Port, M0_Pin | M1_Pin);
    /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin M1_Pin M0_Pin*/
    GPIO_InitStruct.Pin = LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin | M0_Pin | M1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void Lora_Init(void)
{
    uint8_t bufferTX[6];
    set(M_GPIO_Port, M0_Pin | M1_Pin);
    // Save the parameters when power-down
    bufferTX[0] = 0xC0;
    //High address byte of module
    bufferTX[1] = 0x00;
    //Low address byte of module
    bufferTX[2] = 0x00;
    /*Rate parameter，including UART baud rate and air date rate
        7，6 UART parity bit
              00：8N1（default）
              01：8O1
              10：8E1
              11：8N1（equal to 00）
        5，4，3 TTL UART baud rate（bps）
              000：1200bps
              001：2400bps
              010：4800bps
              011：9600bps（Default）
              100：19200bps
              101：38400bps
              110：57600bps
              111：115200bps
        2，1，0 Air date rate（bps）
              000：0.3kbps
              001：1.2kbps
              010：2.4kbps（Default）
              011：4.8kbps
              100：9.6kbps
              101：19.2kbps
              110：19.2kbps(equal to 101)
              111：19.2kbps(equal to 101)
  */
    bufferTX[3] = 0x1A; //0001-1010: 8N1-9600bps-2.4kbps
    // Communication frequency（410M + CHAN * 1M）Default 17H（433MHz)
    bufferTX[4] = 0x17;
    /*7， Fixed transmission（similar to MODBUS）
        0： Transparent transmission mode（default）
        1： Fixed transmission mode
    6 IO drive mode(the default 1)
        1：TXD and AUX push-pull outputs, RXD pull-up inputs
        0：TXD、AUX open-collector outputs, RXD open-collector inputs
    5，4，3 wireless wake-up time（for the receiver, it means the monitor interval time, 
    while for the transmitter it means continuously sending preamble code time.）
        000：250ms（default）
        001：500ms
        010：750ms
        011：1000ms
        100：1250ms
        101：1500ms
        110：1750ms
        111：2000ms 
    2， FEC switch
        0：Turn off FEC
        1：Turn on FEC（Default） 
    1, 0 transmission power (approximation)
        00： 20dBm（Default）
        01： 17dBm
        10： 14dBm
        11： 10dBm */
    bufferTX[5] = 0x44; //0100-0100: Transparent transmission mode-pull up 250ms-FEC-20dBm
    // HAL_UART_Transmit(&huart2, bufferTX, 6, 100);
    HAL_UART_Transmit_DMA(&huart2, bufferTX, 6);
    vTaskDelay(100);
    reset(M_GPIO_Port, M0_Pin | M1_Pin);
}
void led_DIR_circle(uint8_t n, uint16_t delay)
{
    for (uint8_t i = 0; i < n; i++)
    {
        set(LD_GPIO_Port, LD3_Pin);
        osDelay(delay);
        reset(LD_GPIO_Port, LD3_Pin);
        osDelay(delay);
        set(LD_GPIO_Port, LD4_Pin);
        osDelay(delay);
        reset(LD_GPIO_Port, LD4_Pin);
        osDelay(delay);
        set(LD_GPIO_Port, LD6_Pin);
        osDelay(delay);
        reset(LD_GPIO_Port, LD6_Pin);
        osDelay(delay);
        set(LD_GPIO_Port, LD5_Pin);
        osDelay(delay);
        reset(LD_GPIO_Port, LD5_Pin);
        osDelay(delay);
    }
}
void led_DIR_Toggle(uint16_t delay)
{
    toggle(LD_GPIO_Port, LD3_Pin);
    osDelay(delay);
    toggle(LD_GPIO_Port, LD4_Pin);
    osDelay(delay);
    toggle(LD_GPIO_Port, LD6_Pin);
    osDelay(delay);
    toggle(LD_GPIO_Port, LD5_Pin);
    osDelay(delay);
}
