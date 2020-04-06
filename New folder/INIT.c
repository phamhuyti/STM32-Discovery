#include "main.h"
extern UART_HandleTypeDef huart2;
void Lora_Init(void)
{
    uint8_t bufTX[6];
    set(M_GPIO_Port, M0_Pin | M1_Pin);
    // Save the parameters when power-down
    bufTX[0] = 0xC0;
    //High address byte of module
    bufTX[1] = 0x00;
    //Low address byte of module
    bufTX[2] = 0x00;
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
    bufTX[3] = 0x1A; //0001-1010: 8N1-9600bps-2.4kbps
    // Communication frequency（410M + CHAN * 1M）Default 17H（433MHz)
    bufTX[4] = 0x17;
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
    bufTX[5] = 0x44; //0100-0100: Transparent transmission mode-pull up 250ms-FEC-20dBm
    // HAL_UART_Transmit(&huart2, bufTX, 6, 100);
    HAL_UART_Transmit_DMA(&huart2, bufTX, 6);
}
