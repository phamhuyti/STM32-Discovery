/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
#include "UART_DMA.h"
#include "INIT.h"
#include "rc522.h"
#include "Wheel_Init.h"
#include "Matric.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

osThreadId Task_Check_Ready_Handle;
osThreadId Task_Uart_Handle;
osThreadId TaskmoveDir_Handle;
osThreadId Task_Check_RFID_Handle;
osThreadId calculator_Dijkstra_Handle;
osThreadId Taskmove_Handle;

static uint64_t ID_Matrix[5][5] =
{
  {0xd9c86f81ff, 0x39a5ae82b0, 0x39d39481ff, 0xb9326a8263, 0x298f6d814a},
  {0x796ebb812d, 0x192f6c82d8, 0xc95e678272, 0x199fdc82d8, 0xd7440b3ea6},
  {0x99c7dd3bb8, 0x77f488353e, 0x9725083d87, 0xb98d6e4319, 0x69236f88ad},
  {0x2952ab8151, 0x49d8948184, 0xe92d628224, 0x59dfc683c3, 0x6969818100},
  {0x9fdca82bc, 0x998cca825d, 0xa91e6d8258, 0x17c10e3ee6, 0x896f0dc52e},
};

uint8_t bufferTX[10], bufferRX[10], move = 0;
uint64_t ID = 0;
List_move_type List_Move;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Task_Uart(void const *argument);
void Task_Check_Ready(void const *argument);
void TaskmoveDir(void const *argument);
void Task_Check_RFID(void const *argument);
void calculator_Dijkstra(void const *argument);
void Taskmove(void const *argument);
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
  // MX_SPI1_Init();

  UART_DMA_INIT();
  UART_INIT();
  GPIO_Init();
  MFRC522_Init();
  Wheel_GPIO_Init();
  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(Task_Check_Ready_name, Task_Check_Ready, osPriorityNormal, 0, 128);
  Task_Check_Ready_Handle = osThreadCreate(osThread(Task_Check_Ready_name), NULL);

  /* definition and creation of Task_Uart */
  osThreadDef(Task_Uart_name, Task_Uart, osPriorityNormal, 0, 128);
  Task_Uart_Handle = osThreadCreate(osThread(Task_Uart_name), NULL);

  /* definition and creation of TaskmoveDir */
  osThreadDef(TaskmoveDir_name, TaskmoveDir, osPriorityRealtime, 0, 128);
  TaskmoveDir_Handle = osThreadCreate(osThread(TaskmoveDir_name), NULL);

  /* definition and creation of Task_Check_ID */
  osThreadDef(Task_Check_RFID_name, Task_Check_RFID, osPriorityHigh, 0, 500);
  Task_Check_RFID_Handle = osThreadCreate(osThread(Task_Check_RFID_name), NULL);

  /* definition and creation of calculator_Dijkstra */
  osThreadDef(calculator_Dijkstra_name, calculator_Dijkstra, osPriorityNormal, 0, 128);
  calculator_Dijkstra_Handle = osThreadCreate(osThread(calculator_Dijkstra_name), NULL);

  /* definition and creation of Taskmove */
  osThreadDef(Taskmove_name, Taskmove, osPriorityHigh, 0, 128);
  Taskmove_Handle = osThreadCreate(osThread(Taskmove_name), NULL);

  vTaskSuspend(Task_Uart_Handle);
  vTaskSuspend(TaskmoveDir_Handle);
  vTaskSuspend(Task_Check_RFID_Handle);
  vTaskSuspend(calculator_Dijkstra_Handle);
  vTaskSuspend(Taskmove_Handle);
  /* Start scheduler */
  osKernelStart();
}

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
void Task_Check_Ready(void const *argument)
{
  char a[6] = {0xC0, 0x00, 0x00, 0x1A, 0x17, 0x44};
  /*Configuration and Check Configuration*/
  do
  {
    Lora_Init();
    set(M_GPIO_Port, M0_Pin | M1_Pin);
    vTaskDelay(10);
    bufferTX[0] = 0xC1;
    bufferTX[1] = 0xC1;
    bufferTX[2] = 0xC1;
    // HAL_UART_Receive(&huart2, bufferRX, 6, 100);
    HAL_UART_Receive_DMA(&huart2, bufferRX, 6);
    // HAL_UART_Transmit(&huart2, bufferTX, 3, 100);
    HAL_UART_Transmit_DMA(&huart2, bufferTX, 3);
    led_DIR_circle(1, 50);
  } while (strcmp(bufferRX, a));
  reset(M_GPIO_Port, M0_Pin | M1_Pin);
  vTaskDelay(10);
  while (MFRC522_Check(0) == MI_ERR)
    led_DIR_Toggle(100);
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
  sprintf(bufferTX, "OK!");
  while (bufferRX[0] != 'O' || bufferRX[1] != 'K' || bufferRX[2] != '!')
  {
    HAL_UART_Transmit_DMA(&huart2, bufferTX, 3);
    HAL_UART_Receive_DMA(&huart2, bufferRX, 3);
    led_DIR_circle(1, 300);
  }
  bufferRX[2] = ' ';
  for (;;)
  {
    HAL_UART_Receive_DMA(&huart2, bufferRX, 3);
    switch (bufferRX[2])
    {
    case '.':
      ID = 0;
      sprintf(bufferTX, "Start");
      // HAL_UART_Transmit(&huart2, bufferTX, 5, 100);
      HAL_UART_Transmit_DMA(&huart2, bufferTX, 5);
      vTaskResume(Task_Check_RFID_Handle);
      vTaskResume(calculator_Dijkstra_Handle);
      // vTaskSuspend(Task_Uart_Handle);
      break;
    case '!'://Lenh RESET va Manual
      vTaskResume(TaskmoveDir_Handle);
      switch (bufferRX[1])
      {
      case '1':
        move = 1;
        break;
      case '2':
        move = 2;
        break;
      case '3':
        move = 3;
        break;
      case '4':
        move = 4;
        break;
      case '5':
        move = 5;
        break;
      case '6':
        move = 6;
        break;
      case '7':
        move = 7;
        break;
      case '8':
        move = 8;
        break;
      case '9':
        move = 9;
        break;
      case '0':
        if (bufferRX[0] == '1')
        {
          move = 10;
          break;
        }
      default:
        if (bufferRX[0] == 'R' && bufferRX[1] == 'E')
        {
          move = 0;
          HAL_UART_Transmit_DMA(&huart2, bufferTX, 3);
          vTaskSuspend(Task_Check_RFID_Handle);
          vTaskSuspend(calculator_Dijkstra_Handle);
          vTaskSuspend(Taskmove_Handle);
          vTaskSuspend(TaskmoveDir_Handle);
        }
        break;
      }
      break;
    case 'T'://Lenh Cai dat Matric
      move = 0;
      vTaskSuspend(Task_Check_RFID_Handle);
      vTaskSuspend(calculator_Dijkstra_Handle);
      vTaskSuspend(Taskmove_Handle);
      vTaskSuspend(TaskmoveDir_Handle);
      if (bufferRX[0] != 'S' && bufferRX[1] != 'E' )
      {
        while (1)
        {
          HAL_UART_Receive_DMA(&huart2, bufferRX, 3);
          if (bufferRX[0] != 'R' && bufferRX[1] != 'E' && bufferRX[2] != '!') 
            UpdateMatric(bufferRX[0],bufferRX[1],bufferRX[2]);
          else break;
        }
        
      }
      
      break;
    default:
      bufferRX[2] = ' ';
      break;
    }
    bufferRX[2] = ' ';
    osDelay(1);
  }
}

/**
  * @brief  Function implementing the Task_Check_RFID thread.
  * @param  argument: Not used 
  * @retval None
  */
void Task_Check_RFID(void const *argument)
{
  for (;;)
  {
    if (MFRC522_Check(&ID) == MI_NOTAGERR)
    {
      ID = 0;
    }
    vTaskDelay(1);
  }
}

/**
* @brief Function implementing the calculator_Dijkstra thread.
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
          sprintf(bufferTX, "%d:%d", i, j);
          HAL_UART_Transmit_DMA(&huart2, bufferTX, 3);
          List_Move = Dijkstra(i * 5 + j, (bufferRX[0] - 48) * 5 + (bufferRX[1] - 48));
          vTaskResume(Taskmove_Handle);
          vTaskResume(TaskmoveDir_Handle);
          // vTaskSuspend(calculator_Dijkstra_Handle);
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
        break;
      }
    else
    {
      move = 0;
      vTaskSuspend(Task_Check_RFID_Handle);
      vTaskSuspend(calculator_Dijkstra_Handle);
      vTaskSuspend(TaskmoveDir_Handle);
      sprintf(bufferTX, "Stop");
      HAL_UART_Transmit_DMA(&huart2, bufferTX, 4);
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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
// static void MX_SPI1_Init(void)
// {
//   /* SPI1 parameter configuration*/
//   hspi1.Instance = SPI1;
//   hspi1.Init.Mode = SPI_MODE_MASTER;
//   hspi1.Init.Direction = SPI_DIRECTION_2LINES;
//   hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
//   hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
//   hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
//   hspi1.Init.NSS = SPI_NSS_SOFT;
//   hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
//   hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
//   hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
//   hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
//   hspi1.Init.CRCPolynomial = 10;
//   if (HAL_SPI_Init(&hspi1) != HAL_OK)
//   {
//     Error_Handler();
//   }
// }

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4)
  {
    HAL_IncTick();
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
