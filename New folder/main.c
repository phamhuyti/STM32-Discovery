/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
#include "Matric.h"
#include "Wheel_Init.h"
#include "rc522.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
osThreadId Task_Check_Ready_Handle;
osThreadId Task_Uart_Handle;
osMessageQId myQueue01Handle;
osThreadId Task_Check_RFID_Handle;
osThreadId calculator_Dijkstra_Handle;
osThreadId TaskmoveForward_Handle;
osThreadId TaskmoveBackward_Handle;
osThreadId TaskmoveSidewaysLeft_Handle;
osThreadId TaskmoveSidewaysRight_Handle;
osThreadId Taskmove_Handle;
uint8_t IDCard[5];
uint64_t ID;
static uint64_t ID_Matrix[5][5] = {
    {0xd9c86f81ff, 0x39a5ae82b0, 0x39d39481ff, 0xb9326a8263, 0x298f6d814a},
    {0x796ebb812d, 0x192f6c82d8, 0xc95e678272, 0x199fdc82d8, 0xd7440b3ea6},
    {0x99c7dd3bb8, 0x77f488353e, 0x9725083d87, 0xb98d6e4319, 0x69236f88ad},
    {0x2952ab8151, 0x49d8948184, 0xe92d628224, 0x59dfc683c3, 0x6969818100},
    {0x9fdca82bc, 0x998cca825d, 0xa91e6d8258, 0x17c10e3ee6, 0x896f0dc52e},
};
List_move_type List_Move;
char bufRX[10], bufTX[15];
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_USART2_UART_Init(void);
void Task_Check_Ready(void const *argument);
void Task_Uart(void const *argument);
void Task_Check_ID(void const *argument);
void calculator_Dijkstra(void const *argument);
void TaskmoveForward(void const *argument);
void TaskmoveBackward(void const *argument);
void TaskmoveSidewaysLeft(void const *argument);
void TaskmoveSidewaysRight(void const *argument);
void Taskmove(void const *argument);
void Lora_Init(void);
/* Private user code ---------------------------------------------------------*/
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_USART2_UART_Init();
  MFRC522_Init();
  GPIO_Init();
  Wheel_GPIO_Init();
  Lora_Init();
  /* Create the queue(s) */
  /* definition and creation of myQueue01 */
  // osMessageQDef(myQueue01, 10, uint8_t);
  // myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);

  /* Create the thread(s) */
  /* definition and creation of Task_Check_Ready */
  osThreadDef(Task_Check_Ready_name, Task_Check_Ready, osPriorityNormal, 0, 128);
  Task_Check_Ready_Handle = osThreadCreate(osThread(Task_Check_Ready_name), NULL);

  /* definition and creation of Task_Uart */
  osThreadDef(Task_Uart_name, Task_Uart, osPriorityNormal, 0, 128);
  Task_Uart_Handle = osThreadCreate(osThread(Task_Uart_name), NULL);

  /* definition and creation of Task_Uart */
  osThreadDef(Task_Check_RFID_name, Task_Check_ID, osPriorityHigh, 0, 500);
  Task_Check_RFID_Handle = osThreadCreate(osThread(Task_Check_RFID_name), NULL);

  /* definition and creation of calculator_Dijkstra */
  osThreadDef(calculator_Dijkstra_name, calculator_Dijkstra, osPriorityNormal, 0, 128);
  calculator_Dijkstra_Handle = osThreadCreate(osThread(calculator_Dijkstra_name), NULL);

  /* definition and creation of TaskmoveForward */
  osThreadDef(TaskmoveForward_name, TaskmoveForward, osPriorityRealtime, 0, 128);
  TaskmoveForward_Handle = osThreadCreate(osThread(TaskmoveForward_name), NULL);

  /* definition and creation of TaskmoveBackward */
  osThreadDef(TaskmoveBackward_name, TaskmoveBackward, osPriorityRealtime, 0, 128);
  TaskmoveBackward_Handle = osThreadCreate(osThread(TaskmoveBackward_name), NULL);

  /* definition and creation of TaskmoveSidewaysLeft */
  osThreadDef(TaskmoveSidewaysLeft_name, TaskmoveSidewaysLeft, osPriorityRealtime, 0, 128);
  TaskmoveSidewaysLeft_Handle = osThreadCreate(osThread(TaskmoveSidewaysLeft_name), NULL);

  /* definition and creation of TaskmoveSidewaysRight */
  osThreadDef(TaskmoveSidewaysRight_name, TaskmoveSidewaysRight, osPriorityRealtime, 0, 128);
  TaskmoveSidewaysRight_Handle = osThreadCreate(osThread(TaskmoveSidewaysRight_name), NULL);

  /* definition and creation of Taskmove */
  osThreadDef(Taskmove_name, Taskmove, osPriorityHigh, 0, 128);
  Taskmove_Handle = osThreadCreate(osThread(Taskmove_name), NULL);

  vTaskSuspend(Task_Check_RFID_Handle);
  vTaskSuspend(calculator_Dijkstra_Handle);
  vTaskSuspend(Taskmove_Handle);
  vTaskSuspend(TaskmoveForward_Handle);
  vTaskSuspend(TaskmoveBackward_Handle);
  vTaskSuspend(TaskmoveSidewaysLeft_Handle);
  vTaskSuspend(TaskmoveSidewaysRight_Handle);
  vTaskSuspend(Task_Uart_Handle);

  /* Start scheduler */
  osKernelStart();
}
void Lora_Init(void)
{
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
  HAL_UART_Transmit(&huart2, bufTX, 6, 1);
  HAL_UART_Receive(&huart2, bufRX, 6, 100);
}
/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief  Function implementing the Task_Check_Ready thread.
  * @param  argument: Not used 
  * @retval None
  */
void Task_Check_Ready(void const *argument)
{
  osDelay(1000);
  bufTX[0] = 0xC1;
  bufTX[1] = 0xC1;
  bufTX[2] = 0xC1;
  HAL_UART_Transmit(&huart2, bufTX, 3, 1);
  HAL_UART_Receive(&huart2, bufRX, 6, 100);
  char a[6] = {0xC0, 0x00, 0x00, 0x1A, 0x17, 0x44};
  do
  {
    led_DIR_circle(1, 200);
  } while (strcmp(bufRX, a));
  osDelay(1000);
  reset(M_GPIO_Port, M0_Pin | M1_Pin);
  vTaskResume(Task_Uart_Handle);
  vTaskSuspend(Task_Check_Ready_Handle);
}
/**
  * @brief  Function implementing the Task_Uart thread.
  * @param  argument: Not used 
  * @retval None
  */
void Task_Uart(void const *argument)
{

  sprintf(bufTX, "HELLO!!!");
  HAL_UART_Transmit(&huart2, bufTX, 8, 1);
  for (;;)
  {
    HAL_UART_Receive(&huart2, bufRX, 3, 1);
    if (bufRX[2] == '.')
    {
      ID = 0;
      sprintf(bufTX, "Start");
      HAL_UART_Transmit(&huart2, bufTX, 5, 1);
      vTaskResume(Task_Check_RFID_Handle);
      vTaskResume(calculator_Dijkstra_Handle);
      vTaskSuspend(Task_Uart_Handle);
    }
    osDelay(1);
  }
}
/**
  * @brief  Function implementing the myTask01 thread.
  * @param  argument: Not used 
  * @retval None
  */
void Task_Check_ID(void const *argument)
{
  uint8_t IDCard[5];
  for (;;)
  {
    if (MFRC522_Check(IDCard) == MI_OK)
    {
      ID = 0;
      ID = IDCard[0];
      for (int i = 1; i < 5; i++)
      {
        ID <<= 8;
        ID += IDCard[i];
      }
    }
    else
      for (int i = 0; i < 5; i++)
        IDCard[i] = 0;
    vTaskDelay(100);
  }
}
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
void calculator_Dijkstra(void const *argument)
{
  for (;;)
  {
    for (uint8_t i = 0; i < 5; i++)
      for (uint8_t j = 0; j < 5; j++)
        if (ID == ID_Matrix[i][j])
        {
          sprintf(bufTX, "%d:%d", i, j);
          HAL_UART_Transmit(&huart2, bufTX, 3, 1);
          List_Move = Dijkstra(i * 5 + j, (bufRX[0] - 48) * 5 + (bufRX[1] - 48));
          vTaskResume(Taskmove_Handle);
          vTaskSuspend(calculator_Dijkstra_Handle);
        }
  }
}
/**
* @brief Function implementing the Taskmove thread.
* @param argument: Not used
* @retval None
*/
void Taskmove(void const *argument)
{
  while (1)
  {
    if (List_Move.Length_way < 25 || List_Move.Length_way == 0xFF)
      switch (List_Move.Move[List_Move.Length_way])
      {
      case 1:
        vTaskResume(TaskmoveForward_Handle);
        vTaskSuspend(TaskmoveBackward_Handle);
        vTaskSuspend(TaskmoveSidewaysLeft_Handle);
        vTaskSuspend(TaskmoveSidewaysRight_Handle);
        if (ID == ID_Matrix[List_Move.x[List_Move.Length_way]][List_Move.y[List_Move.Length_way]])
        {
          sprintf(bufTX, "%d:%d", List_Move.x[List_Move.Length_way], List_Move.y[List_Move.Length_way]);
          HAL_UART_Transmit(&huart2, bufTX, 3, 1);
          List_Move.Length_way--;
        }
        /* code */
        break;
      case 2:
        vTaskResume(TaskmoveSidewaysRight_Handle);
        vTaskSuspend(TaskmoveBackward_Handle);
        vTaskSuspend(TaskmoveSidewaysLeft_Handle);
        vTaskSuspend(TaskmoveForward_Handle);
        if (ID == ID_Matrix[List_Move.x[List_Move.Length_way]][List_Move.y[List_Move.Length_way]])
        {
          sprintf(bufTX, "%d:%d", List_Move.x[List_Move.Length_way], List_Move.y[List_Move.Length_way]);
          HAL_UART_Transmit(&huart2, bufTX, 3, 1);
          List_Move.Length_way--;
        }
        /* code */
        break;
      case 3:
        vTaskResume(TaskmoveBackward_Handle);
        vTaskSuspend(TaskmoveForward_Handle);
        vTaskSuspend(TaskmoveSidewaysLeft_Handle);
        vTaskSuspend(TaskmoveSidewaysRight_Handle);
        if (ID == ID_Matrix[List_Move.x[List_Move.Length_way]][List_Move.y[List_Move.Length_way]])
        {
          sprintf(bufTX, "%d:%d", List_Move.x[List_Move.Length_way], List_Move.y[List_Move.Length_way]);
          HAL_UART_Transmit(&huart2, bufTX, 3, 1);
          List_Move.Length_way--;
        }
        /* code */
        break;
      case 4:
        vTaskResume(TaskmoveSidewaysLeft_Handle);
        vTaskSuspend(TaskmoveBackward_Handle);
        vTaskSuspend(TaskmoveForward_Handle);
        vTaskSuspend(TaskmoveSidewaysRight_Handle);
        if (ID == ID_Matrix[List_Move.x[List_Move.Length_way]][List_Move.y[List_Move.Length_way]])
        {
          sprintf(bufTX, "%d:%d", List_Move.x[List_Move.Length_way], List_Move.y[List_Move.Length_way]);
          HAL_UART_Transmit(&huart2, bufTX, 3, 1);
          List_Move.Length_way--;
        }
        /* code */
        break;

      default:
        if (List_Move.Length_way != 0xFF)
          List_Move.Length_way--;
        else
        {
          bufRX[2] = 0;
          vTaskSuspend(Task_Check_RFID_Handle);
          vTaskSuspend(calculator_Dijkstra_Handle);
          vTaskSuspend(TaskmoveForward_Handle);
          vTaskSuspend(TaskmoveBackward_Handle);
          vTaskSuspend(TaskmoveSidewaysLeft_Handle);
          vTaskSuspend(TaskmoveSidewaysRight_Handle);
          led_DIR_circle(15, 20);
          sprintf(bufTX, "Stop");
          HAL_UART_Transmit(&huart2, bufTX, 4, 1);
          vTaskResume(Task_Uart_Handle);
          vTaskSuspend(Taskmove_Handle);
        }
        break;
      }
    else
    {
      bufRX[2] = 0;
      vTaskSuspend(Task_Check_RFID_Handle);
      vTaskSuspend(calculator_Dijkstra_Handle);
      vTaskSuspend(TaskmoveForward_Handle);
      vTaskSuspend(TaskmoveBackward_Handle);
      vTaskSuspend(TaskmoveSidewaysLeft_Handle);
      vTaskSuspend(TaskmoveSidewaysRight_Handle);
      led_DIR_circle(7, 200);
      sprintf(bufTX, "Stop");
      HAL_UART_Transmit(&huart2, bufTX, 4, 1);
      vTaskResume(Task_Uart_Handle);
      vTaskSuspend(Taskmove_Handle);
    }
    osDelay(100);
  }
}
/**
* @brief Function implementing the TaskmoveForward thread.
* @param argument: Not used
* @retval None
*/
void TaskmoveForward(void const *argument)
{
  for (;;)
  {
    moveForward();
  }
}
/**
* @brief Function implementing the TaskmoveBackward thread.
* @param argument: Not used
* @retval None
*/
void TaskmoveBackward(void const *argument)
{
  for (;;)
  {
    moveBackward();
  }
}
/**
* @brief Function implementing the TaskmoveSidewaysLeft thread.
* @param argument: Not used
* @retval None
*/
void TaskmoveSidewaysLeft(void const *argument)
{
  for (;;)
  {
    moveSidewaysLeft();
  }
}
/**
* @brief Function implementing the TaskmoveSidewaysRight thread.
* @param argument: Not used
* @retval None
*/
void TaskmoveSidewaysRight(void const *argument)
{
  for (;;)
  {
    moveSidewaysRight();
  }
}

void led_DIR_circle(uint8_t n, uint8_t delay)
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

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM10 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM10)
  {
    HAL_IncTick();
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  set(LD_GPIO_Port, LD3_Pin);
  HAL_Delay(100);
  reset(LD_GPIO_Port, LD3_Pin);
  HAL_Delay(100);
  set(LD_GPIO_Port, LD4_Pin);
  HAL_Delay(100);
  reset(LD_GPIO_Port, LD4_Pin);
  HAL_Delay(100);
  set(LD_GPIO_Port, LD6_Pin);
  HAL_Delay(100);
  reset(LD_GPIO_Port, LD6_Pin);
  HAL_Delay(100);
  set(LD_GPIO_Port, LD5_Pin);
  HAL_Delay(100);
  reset(LD_GPIO_Port, LD5_Pin);
  HAL_Delay(100);
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
