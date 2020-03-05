/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
/* Private includes ----------------------------------------------------------*/
#include "rc522.h"
#include "Wheel_Init.h"
#include "Matric.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
osThreadId myTask01Handle;
osThreadId myTask02Handle;
uint8_t IDCard[5];
uint64_t ID;
uint8_t Move[25], x[25], y[25], Length_way = 0;
static uint64_t ID_Matrix[5][5] = {
    {0xd9c86f81ff, 0x39a5ae82b0, 0x39d39481ff, 0xb9326a8263, 0x298f6d814a},
    {0x796ebb812d, 0x192f6c82d8, 0xc95e678272, 0x199fdc82d8, 0xd7440b3ea6},
    {0x99c7dd3bb8, 0x77f488353e, 0x9725083d87, 0xb98d6e4319, 0x69236f88ad},
    {0x2952ab8151, 0x49d8948184, 0xe92d628224, 0x59dfc683c3, 0x6969818100},
    {0x9fdca82bc, 0x998cca825d, 0xa91e6d8258, 0x17c10e3ee6, 0x896f0dc52e},
};
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_SPI1_Init(void);
void StartTask01(void const *argument);
void StartTask02(void const *argument);
void led_DIR_circle(uint8_t n, uint8_t delay);
/* Private user code ---------------------------------------------------------*/
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{ /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_SPI1_Init();
  MFRC522_Init();
  Wheel_GPIO_Init();
  /* definition and creation of myTask01 */
  osThreadDef(myTask01, StartTask01, osPriorityNormal, 0, 500);
  myTask01Handle = osThreadCreate(osThread(myTask01), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityHigh, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  while (1)
  {
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
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */
}
/* USER CODE BEGIN Header_StartTask01 */
/**
  * @brief  Function implementing the myTask01 thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartTask01 */
void StartTask01(void const *argument)
{
  uint8_t IDCard[5];
  /* Infinite loop */
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
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const *argument)
{
  /* Infinite loop */
  for (uint8_t i = 0; i < 25; i++)
  {
    Move[i] = 0;
    x[i] = 0;
    y[i] = 0;
  }
  Dijkstra(0, 7, Move, x, y, &Length_way);
  for (;;)
  {
    switch (Move[Length_way])
    {
    case 1:
      moveForward(1);
      if (ID == ID_Matrix[x[Length_way]][y[Length_way]])
      {
        Length_way--;
        for (uint8_t i = 0; i < 10; i++)
          moveForward(1);
        osDelay(100);
      }
      /* code */
      break;
    case 2:
      moveSidewaysRight();
      if (ID == ID_Matrix[x[Length_way]][y[Length_way]])
      {
        Length_way--;
        for (uint8_t i = 0; i < 10; i++)
          moveSidewaysRight();
        osDelay(100);
      }
      /* code */
      break;
    case 3:
      moveBackward(1);
      if (ID == ID_Matrix[x[Length_way]][y[Length_way]])
      {
        Length_way--;
        for (uint8_t i = 0; i < 10; i++)
          moveBackward(1);
        osDelay(100);
      }
      /* code */
      break;
    case 4:
      moveSidewaysLeft();
      if (ID == ID_Matrix[x[Length_way]][y[Length_way]])
      {
        Length_way--;
        for (uint8_t i = 0; i < 10; i++)
          moveSidewaysLeft();
        osDelay(100);
      }
      /* code */
      break;

    default:
      led_DIR_circle(7, 20);
      Length_way--;
      break;
    }
  }
  /* USER CODE END StartTask02 */
}
void led_DIR_circle(uint8_t n, uint8_t delay)
{
  for (uint8_t i = 0; i < n; i++)
  {
    set(led_R_GPIO_Port, led_R_Pin);
    osDelay(delay);
    reset(led_R_GPIO_Port, led_R_Pin);
    osDelay(delay);
    set(led_B_GPIO_Port, led_B_Pin);
    osDelay(delay);
    reset(led_B_GPIO_Port, led_B_Pin);
    osDelay(delay);
    set(led_G_GPIO_Port, led_G_Pin);
    osDelay(delay);
    reset(led_G_GPIO_Port, led_G_Pin);
    osDelay(delay);
    set(led_O_GPIO_Port, led_O_Pin);
    osDelay(delay);
    reset(led_O_GPIO_Port, led_O_Pin);
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
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM10)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
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
