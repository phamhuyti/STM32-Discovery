/*includes ----------------------------------------------------------*/
#include "main.h"
#include "Matric.h"
#include "Wheel_Init.h"
#include "rc522.h"
#include "UART_DMA.h"
#include "INIT.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart2_rx;

osThreadId Task_Check_Ready_Handle;
osThreadId Task_Uart_Handle;
osThreadId Task_Check_RFID_Handle;
osThreadId calculator_Dijkstra_Handle;
osThreadId TaskmoveDir_Handle;
osThreadId Taskmove_Handle;

uint8_t IDCard[5], move = 0;
uint64_t ID, temb;
static uint64_t ID_Matrix[5][5] = {
    {0xd9c86f81ff, 0x39a5ae82b0, 0x39d39481ff, 0xb9326a8263, 0x298f6d814a},
    {0x796ebb812d, 0x192f6c82d8, 0xc95e678272, 0x199fdc82d8, 0xd7440b3ea6},
    {0x99c7dd3bb8, 0x77f488353e, 0x9725083d87, 0xb98d6e4319, 0x69236f88ad},
    {0x2952ab8151, 0x49d8948184, 0xe92d628224, 0x59dfc683c3, 0x6969818100},
    {0x9fdca82bc, 0x998cca825d, 0xa91e6d8258, 0x17c10e3ee6, 0x896f0dc52e},
};
List_move_type List_Move;
uint8_t bufRX[10], bufTX[15];
uint8_t dma_bufferRX[5], dma_bufferTX[5];

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Task_Check_Ready(void const *argument);
void Task_Uart(void const *argument);
void Task_Check_ID(void const *argument);
void calculator_Dijkstra(void const *argument);
void TaskmoveDir(void const *argument);
void Taskmove(void const *argument);
void SendLocatiom(void);

int main(void)
{ /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MFRC522_Init();
  GPIO_Init();
  Wheel_GPIO_Init();
  UART_DMA_INIT();
  UART_INIT();
  Lora_Init();

  /* Create the thread(s) */
  /* definition and creation of Task_Check_Ready */
  osThreadDef(Task_Check_Ready_name, Task_Check_Ready, osPriorityNormal, 0, 128);
  Task_Check_Ready_Handle = osThreadCreate(osThread(Task_Check_Ready_name), NULL);

  /* definition and creation of Task_Uart */
  osThreadDef(Task_Uart_name, Task_Uart, osPriorityNormal, 0, 128);
  Task_Uart_Handle = osThreadCreate(osThread(Task_Uart_name), NULL);

  /* definition and creation of Task_Check_ID */
  osThreadDef(Task_Check_RFID_name, Task_Check_ID, osPriorityHigh, 0, 500);
  Task_Check_RFID_Handle = osThreadCreate(osThread(Task_Check_RFID_name), NULL);

  /* definition and creation of calculator_Dijkstra */
  osThreadDef(calculator_Dijkstra_name, calculator_Dijkstra, osPriorityNormal, 0, 128);
  calculator_Dijkstra_Handle = osThreadCreate(osThread(calculator_Dijkstra_name), NULL);

  /* definition and creation of TaskmoveDir */
  osThreadDef(TaskmoveDir_name, TaskmoveDir, osPriorityRealtime, 0, 128);
  TaskmoveDir_Handle = osThreadCreate(osThread(TaskmoveDir_name), NULL);

  /* definition and creation of Taskmove */
  osThreadDef(Taskmove_name, Taskmove, osPriorityHigh, 0, 128);
  Taskmove_Handle = osThreadCreate(osThread(Taskmove_name), NULL);

  vTaskSuspend(Task_Check_RFID_Handle);
  vTaskSuspend(calculator_Dijkstra_Handle);
  vTaskSuspend(Taskmove_Handle);
  vTaskSuspend(TaskmoveDir_Handle);
  vTaskSuspend(Task_Uart_Handle);

  /* Start scheduler */
  osKernelStart();
  // while (HAL_UART_Receive_DMA(&huart2, dma_bufferRX, 2))
  //   ;
  // HAL_UART_Transmit_DMA(&huart2, dma_bufferTX, 2);
}

/**
  * @brief  Function implementing the Task_Check_Ready thread.
  * @param  argument: Not used 
  * @retval None
  */
void Task_Check_Ready(void const *argument)
{
  if (MFRC522_Check(IDCard) == MI_ERR)
    while (1)
      led_DIR_circle(1, 100);
  sprintf(bufRX, "      ");
  // osDelay(100);
  bufTX[0] = 0xC1;
  bufTX[1] = 0xC1;
  bufTX[2] = 0xC1;
  HAL_UART_Transmit(&huart2, bufTX, 3, 100);
  HAL_UART_Receive(&huart2, bufRX, 6, 100);
  char a[6] = {0xC0, 0x00, 0x00, 0x1A, 0x17, 0x44};
  do
  {
    led_DIR_circle(3, 50);
  } while (strcmp(bufRX, a));
  osDelay(100);
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
  sprintf(bufTX, "OK!");
  HAL_UART_Transmit(&huart2, bufTX, 3, 100);
  HAL_UART_Receive(&huart2, bufRX, 3, 100);
  while (bufRX[0] != 'O' || bufRX[1] != 'K' || bufRX[2] != '!')
  {
    led_DIR_circle(1, 300);
    sprintf(bufTX, "OK!");
    HAL_UART_Transmit(&huart2, bufTX, 3, 100);
    HAL_UART_Receive(&huart2, bufRX, 3, 100);
  }
  bufRX[2] = ' ';
  for (;;)
  {
    HAL_UART_Receive(&huart2, bufRX, 3, 100);
    if (bufRX[2] == '.')
    {
      ID = 0;
      temb = 0;
      sprintf(bufTX, "Start");
      HAL_UART_Transmit(&huart2, bufTX, 5, 100);
      osDelay(100);
      vTaskResume(Task_Check_RFID_Handle);
      vTaskResume(calculator_Dijkstra_Handle);
      vTaskSuspend(Task_Uart_Handle);
    }
    if (bufRX[2] == '!')
    {
      vTaskResume(TaskmoveDir_Handle);
      switch (bufRX[1])
      {
      case '1':
        bufRX[2] = 0;
        move = 1;
        break;
      case '2':
        bufRX[2] = 0;
        move = 2;
        break;
      case '3':
        bufRX[2] = 0;
        move = 3;
        break;
      case '4':
        bufRX[2] = 0;
        move = 4;
        break;
      case '5':
        bufRX[2] = 0;
        move = 5;
        break;
      case '6':
        bufRX[2] = 0;
        move = 6;
        break;
      case '7':
        bufRX[2] = 0;
        move = 7;
        break;
      case '8':
        bufRX[2] = 0;
        move = 8;
        break;
      case '9':
        bufRX[2] = 0;
        move = 9;
        break;
      case '0':
        if (bufRX[0] == '1')
        {
          bufRX[2] = 0;
          move = 10;
          break;
        }
      default:
        if (bufRX[0] == 'O' && bufRX[1] == 'K')
        {
          sprintf(bufTX, "OK!");
          HAL_UART_Transmit(&huart2, bufTX, 3, 100);
          HAL_UART_Receive(&huart2, bufRX, 3, 100);
          vTaskSuspend(Task_Check_RFID_Handle);
          vTaskSuspend(calculator_Dijkstra_Handle);
          vTaskSuspend(Taskmove_Handle);
          vTaskSuspend(TaskmoveDir_Handle);
        }
        bufRX[2] = 0;
        move = 0;
        vTaskSuspend(TaskmoveDir_Handle);
        led_DIR_circle(1, 50);
        break;
      }
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
    if (MFRC522_Check(IDCard) == MI_NOTAGERR)
      for (int i = 0; i < 5; i++)
        IDCard[i] = 0;
    vTaskDelay(1);
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
        if (ID == ID_Matrix[i][j] && temb != ID)
        {
          sprintf(bufTX, "%d:%d", i, j);
          HAL_UART_Transmit(&huart2, bufTX, 3, 100);
          List_Move = Dijkstra(i * 5 + j, (bufRX[0] - 48) * 5 + (bufRX[1] - 48));
          vTaskResume(Taskmove_Handle);
          vTaskResume(TaskmoveDir_Handle);
          // vTaskSuspend(calculator_Dijkstra_Handle);
          temb = ID;
        }
    osDelay(1);
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
        move = 1;
        void SendLocatiom();
        break;
      case 2:
        move = 4;
        void SendLocatiom();
        break;
      case 3:
        move = 2;
        void SendLocatiom();
        break;
      case 4:
        move = 3;
        void SendLocatiom();
        break;

      default:
        if (List_Move.Length_way != 0xFF)
          List_Move.Length_way--;
        else
        {
          bufRX[2] = 0;
          move = 0;
          vTaskSuspend(TaskmoveDir_Handle);
          led_DIR_circle(2, 100);
          sprintf(bufTX, "Stop");
          HAL_UART_Transmit(&huart2, bufTX, 4, 100);
          vTaskSuspend(Task_Check_RFID_Handle);
          vTaskSuspend(calculator_Dijkstra_Handle);
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
      move = 0;
      vTaskSuspend(TaskmoveDir_Handle);
      led_DIR_circle(22, 500);
      sprintf(bufTX, "Stop");
      HAL_UART_Transmit(&huart2, bufTX, 4, 100);
      vTaskResume(Task_Uart_Handle);
      vTaskSuspend(Taskmove_Handle);
    }
    osDelay(1);
  }
}

/**
* @brief Function implementing the TaskmoveForward thread.
* @param argument: Not used
* @retval None
*/
void TaskmoveDir(void const *argument)
{
  for (;;)
  {
    switch (move)
    {
    case 1:
      moveForward();
      break;
    case 2:
      moveBackward();
      break;
    case 3:
      moveSidewaysLeft();
      break;
    case 4:
      moveSidewaysRight();
      break;
    case 5:
      moveLeftForward();
      break;
    case 6:
      moveLeftBackward();
      break;
    case 7:
      moveRightForward();
      break;
    case 8:
      moveRightBackward();
      break;
    case 9:
      moveclockwise();
      break;
    case 10:
      moveAnticlockwise();
      break;

    default:
      reset(LD_GPIO_Port, LD3_Pin);
      reset(LD_GPIO_Port, LD4_Pin);
      reset(LD_GPIO_Port, LD5_Pin);
      reset(LD_GPIO_Port, LD6_Pin);
      osDelay(1);
      break;
    }
  }
}

void SendLocatiom()
{
  if (ID == ID_Matrix[List_Move.x[List_Move.Length_way]][List_Move.y[List_Move.Length_way]])
  {
    sprintf(bufTX, "%d:%d", List_Move.x[List_Move.Length_way], List_Move.y[List_Move.Length_way]);
    HAL_UART_Transmit(&huart2, bufTX, 3, 100);
    List_Move.Length_way--;
  }
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
void SendLocaltion()
{
  if (ID == ID_Matrix[List_Move.x[List_Move.Length_way]][List_Move.y[List_Move.Length_way]])
  {
    sprintf(bufTX, "%d:%d", List_Move.x[List_Move.Length_way], List_Move.y[List_Move.Length_way]);
    HAL_UART_Transmit(&huart2, bufTX, 3, 100);
    List_Move.Length_way--;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
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
