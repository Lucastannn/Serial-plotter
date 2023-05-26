/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include <stdio.h> // add in main.c
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
HRTIM_HandleTypeDef hhrtim1;

UART_HandleTypeDef hlpuart1;
DMA_HandleTypeDef hdma_lpuart1_tx;

/* USER CODE BEGIN PV */
/* Sine wave values for a complete symbol */
uint32_t sinewave[100] = {
		0x800000,0x880985,0x900aeb,0x97fc1c,0x9fd511,0xa78dde,0xaf1eb4,0xb67fef,
		0xbdaa1a,0xc495f8,0xcb3c8b,0xd1971b,0xd79f3c,0xdd4ed7,0xe2a02d,0xe78dde,
		0xec12ef,0xf02ad0,0xf3d15e,0xf702ea,0xf9bc37,0xfbfa87,0xfdbb96,0xfefd9c,
		0xffbf56,0xffffff,0xffbf56,0xfefd9c,0xfdbb96,0xfbfa87,0xf9bc37,0xf702ea,
		0xf3d15e,0xf02ad0,0xec12ef,0xe78dde,0xe2a02d,0xdd4ed7,0xd79f3c,0xd1971b,
		0xcb3c8b,0xc495f8,0xbdaa1a,0xb67fef,0xaf1eb4,0xa78dde,0x9fd511,0x97fc1c,
		0x900aeb,0x880985,0x800000,0x77f67a,0x6ff514,0x6803e3,0x602aee,0x587221,
		0x50e14b,0x498010,0x4255e5,0x3b6a07,0x34c374,0x2e68e4,0x2860c3,0x22b128,
		0x1d5fd2,0x187221,0x13ed10,0xfd52f,0xc2ea1,0x8fd15,0x643c8,0x40578,
		0x24469,0x10263,0x40a9,0x0,0x40a9,0x10263,0x24469,0x40578,
		0x643c8,0x8fd15,0xc2ea1,0xfd52f,0x13ed10,0x187221,0x1d5fd2,0x22b128,
		0x2860c3,0x2e68e4,0x34c374,0x3b6a07,0x4255e5,0x498010,0x50e14b,0x587221,
		0x602aee,0x6803e3,0x6ff514,0x77f67a,0x800000};
uint16_t sinewave2[100] = {0x8000,0x8809,0x900a,0x97fc,0x9fd4,0xa78d,0xaf1e,0xb67f,
		0xbda9,0xc495,0xcb3c,0xd196,0xd79e,0xdd4e,0xe29f,0xe78d,
		0xec12,0xf02a,0xf3d0,0xf702,0xf9bb,0xfbfa,0xfdbb,0xfefd,
		0xffbe,0xffff,0xffbe,0xfefd,0xfdbb,0xfbfa,0xf9bb,0xf702,
		0xf3d0,0xf02a,0xec12,0xe78d,0xe29f,0xdd4e,0xd79e,0xd196,
		0xcb3c,0xc495,0xbda9,0xb67f,0xaf1e,0xa78d,0x9fd4,0x97fc,
		0x900a,0x8809,0x8000,0x77f6,0x6ff5,0x6803,0x602b,0x5872,
		0x50e1,0x4980,0x4256,0x3b6a,0x34c3,0x2e69,0x2861,0x22b1,
		0x1d60,0x1872,0x13ed,0xfd5,0xc2f,0x8fd,0x644,0x405,
		0x244,0x102,0x41,0x0,0x41,0x102,0x244,0x405,
		0x644,0x8fd,0xc2f,0xfd5,0x13ed,0x1872,0x1d60,0x22b1,
		0x2861,0x2e69,0x34c3,0x3b6a,0x4256,0x4980,0x50e1,0x5872,
		0x602b,0x6803,0x6ff5,0x77f6,0x8000};

uint8_t send_data[10];

uint32_t sinewave_send[4];
uint8_t i = 0;
uint8_t counter = 0;
uint8_t counter_ = 0;
uint8_t HAL_UART_TxCpltCallback_done = 0;
uint8_t cs = 0;
uint8_t channel1 = 0;
uint16_t channel2 = 0;
uint32_t channel3 = 0;

int8_t channel1_ = 0;
int16_t channel2_ = 0;
int32_t channel3_ = 0;

uint16_t channel1__ = 0;
uint8_t channel2__ = 0;
uint16_t channel3__ = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_HRTIM1_Init(void);
/* USER CODE BEGIN PFP */
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
void send_sine(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_LPUART1_UART_Init();
  MX_HRTIM1_Init();
  /* USER CODE BEGIN 2 */
//
  HAL_HRTIM_WaveformCountStart_IT(&hhrtim1, HRTIM_TIMERID_MASTER);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV6;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief HRTIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_HRTIM1_Init(void)
{

  /* USER CODE BEGIN HRTIM1_Init 0 */

  /* USER CODE END HRTIM1_Init 0 */

  HRTIM_TimeBaseCfgTypeDef pTimeBaseCfg = {0};
  HRTIM_TimerCfgTypeDef pTimerCfg = {0};

  /* USER CODE BEGIN HRTIM1_Init 1 */

  /* USER CODE END HRTIM1_Init 1 */
  hhrtim1.Instance = HRTIM1;
  hhrtim1.Init.HRTIMInterruptResquests = HRTIM_IT_NONE;
  hhrtim1.Init.SyncOptions = HRTIM_SYNCOPTION_NONE;
  if (HAL_HRTIM_Init(&hhrtim1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_HRTIM_DLLCalibrationStart(&hhrtim1, HRTIM_CALIBRATIONRATE_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_HRTIM_PollForDLLCalibration(&hhrtim1, 10) != HAL_OK)
  {
    Error_Handler();
  }
  pTimeBaseCfg.Period = 54400;
  pTimeBaseCfg.RepetitionCounter = 149;
  pTimeBaseCfg.PrescalerRatio = HRTIM_PRESCALERRATIO_MUL16;
  pTimeBaseCfg.Mode = HRTIM_MODE_CONTINUOUS;
  if (HAL_HRTIM_TimeBaseConfig(&hhrtim1, HRTIM_TIMERINDEX_MASTER, &pTimeBaseCfg) != HAL_OK)
  {
    Error_Handler();
  }
  pTimerCfg.InterruptRequests = HRTIM_MASTER_IT_MREP;
  pTimerCfg.DMARequests = HRTIM_MASTER_DMA_NONE;
  pTimerCfg.DMASrcAddress = 0x0000;
  pTimerCfg.DMADstAddress = 0x0000;
  pTimerCfg.DMASize = 0x1;
  pTimerCfg.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
  pTimerCfg.InterleavedMode = HRTIM_INTERLEAVED_MODE_DISABLED;
  pTimerCfg.StartOnSync = HRTIM_SYNCSTART_DISABLED;
  pTimerCfg.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
  pTimerCfg.DACSynchro = HRTIM_DACSYNC_DACTRIGOUT_2;
  pTimerCfg.PreloadEnable = HRTIM_PRELOAD_DISABLED;
  pTimerCfg.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
  pTimerCfg.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
  pTimerCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_DISABLED;
  pTimerCfg.ReSyncUpdate = HRTIM_TIMERESYNC_UPDATE_UNCONDITIONAL;

  if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_MASTER, &pTimerCfg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN HRTIM1_Init 2 */

  /* USER CODE END HRTIM1_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 15000000;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin PA7 PA8 */
  GPIO_InitStruct.Pin = LD2_Pin|GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
__INLINE void send_sine(void)
{
	HAL_UART_TxCpltCallback_done = 0;

//---------------test conditions --------------
//baudrate = 15Mbps
//interval = ~3ms

//	-------------------test1---------------

//	send_data[0] = 0xA0 + counter;
//
//	send_data[1] = channel1;
//	send_data[2] = (channel2 >> 8) & 0xFF;
//	send_data[3] = channel2 & 0xFF;
//	send_data[4] = channel3 >> 24;
//	send_data[5] = (channel3 >> 16) & 0xFF;
//	send_data[6] = (channel3 >> 8) & 0xFF;
//	send_data[7] = channel3 & 0xFF;
//
//	counter++;
//	channel1++;
//	channel2++;
//	channel3++;
//
//	HAL_UART_Transmit_DMA(&hlpuart1, (uint8_t*)send_data, 8)
//
//	if(counter == 0x10){
//	  counter = 0;
//	}

//	---------------------------------------


//	-------------------test2---------------

//	send_data[0] = 0xA0 + counter;
//
//	send_data[1] = channel1_;
//	send_data[2] = (channel2_ >> 8) & 0xFF;
//	send_data[3] = channel2_ & 0xFF;
//	send_data[4] = channel3_ >> 24;
//	send_data[5] = (channel3_ >> 16) & 0xFF;
//	send_data[6] = (channel3_ >> 8) & 0xFF;
//	send_data[7] = channel3_ & 0xFF;
//
//	counter++;
//	channel1_--;
//	channel2_--;
//	channel3_--;
//
//	HAL_UART_Transmit_DMA(&hlpuart1, (uint8_t*)send_data, 8)
//
//	if(counter == 0x10){
//	  counter = 0;
//	}
//	if (channel1_ == -128){
//	//		  channel1_ = 127;
//	  channel1_ = 0;
//	}
//	if(channel2_ == -32768){
//	  channel2_ = 32767;
//	  channel2_ = 0;
//	}
//	if(channel3_ == -2147483648 ){
//	//		  channel3_ = 2147483647;
//	  channel3_ = 0;
//	}

//	---------------------------------------

//	-------------------test3---------------

//	frame start = 101010 = 0x2A

//	send_data[0] = 0xA8 + counter_;
//
//	send_data[1] = channel1__ >> 2;
//	send_data[2] = ((channel1__ & 0x3) << 6) + channel2__;
//	send_data[3] = (channel3__ >> 8) & 0xFF;
//	send_data[4] = channel3__ & 0xFF;
//
//	counter_++;
//	channel1__+=2;
//	channel2__++;
//	channel3__+=5;
//
//	HAL_UART_Transmit_DMA(&hlpuart1, (uint8_t*)send_data, 5)
//
//	if(counter_ == 4){
//		counter_ = 0;
//	}
//	if (channel1__ == 0x400){
//	  channel1_ = 0;
//	}
//	if(channel2__ == 0x40){
//	  channel2_ = 0;
//	}
//	if(channel3__ == 0x10000){
//	  channel3_ = 0;
//	}

//	---------------------------------------

//	-------------------checksum test------------------

//	send_data[1] = sinewave[i] & 0xFF;
//	send_data[2] = (sinewave[i] >> 8) & 0xFF;
//	send_data[3] = (sinewave[i] >> 16) & 0xFF;
//	send_data[4] = sinewave[i] >> 24;
//	send_data[5] = sinewave[i] & 0xFF;
//	send_data[6] = (sinewave[i] >> 8) & 0xFF;
//	send_data[7] = (sinewave[i] >> 16) & 0xFF;
//	send_data[8] = sinewave[i] >> 24;
//
//	cs = 0;
//	for (int a=1; a< 9; a++){
//		cs += send_data[a];
//	}
//	cs %= 0xFF;
//
//	send_data[9] = cs;
//
//	i++;
//	HAL_UART_Transmit_DMA(&hlpuart1, (uint8_t*)send_data, 9)
//
//	if (i == 100){
//	  i = 0;
//	}

//	-------------------------------------------------

//	-------------------simple binary test------------------


//	sinewave_send[0] = sinewave[i];
//	HAL_UART_Transmit_DMA(&hlpuart1, (uint8_t*)sinewave_send, 4)
//
//	i++;
//
//	if (i == 100){
//	  i = 0;
//	}

//	-------------------------------------------------------

//	-------------------pointer test------------------

	int32_t* sinewave_ptr = &sinewave[i];

//	channel3 = 0xFFFFFFFF;
//	counter = 0xA;

	send_data[0] = 0xA0 + counter;
	send_data[1] = channel3 & 0xFF; // lower 8 bits of counter
	send_data[2] = (channel3 >> 8) & 0xFF; // next 8 bits of counter
	send_data[3] = (channel3 >> 16) & 0xFF; // next 8 bits of counter
	send_data[4] = (channel3 >> 24) & 0xFF; // upper 8 bits of counter

	uint8_t* sinewave_bytes = (uint8_t*)sinewave_ptr;
	send_data[5] = sinewave_bytes[0];
	send_data[6] = sinewave_bytes[1];
	send_data[7] = sinewave_bytes[2];
	send_data[8] = sinewave_bytes[3];


	i++;
	counter++;
	channel3+=100000;

	HAL_UART_Transmit_DMA(&hlpuart1, (uint8_t*)send_data, 9);

	if (i == 100){
	  i = 0;
	}
	if(counter == 0x10){
	  counter = 0;
	}

//	-------------------------------------------------

	while (!HAL_UART_TxCpltCallback_done)
	{
	}

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_TxCpltCallback can be implemented in the user file.
   */
  HAL_UART_TxCpltCallback_done = 1;
}

void HAL_HRTIM_RepetitionEventCallback(HRTIM_HandleTypeDef * hhrtim,
                                              uint32_t TimerIdx)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhrtim);
  UNUSED(TimerIdx);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_HRTIM_Master_RepetitionEventCallback could be implemented in the user file
   */
  send_sine();
}


//PUTCHAR_PROTOTYPE {
//	/* Place your implementation of fputc here */
//	/* e.g. write a character to the LPUART1 and Loop until the end of transmission */
//	HAL_UART_Transmit(&hlpuart1, (uint8_t*) &ch, 1, 0xFFFF);
////	HAL_UART_Transmit_DMA(&hlpuart1, (uint8_t*) &ch, 1);
//
//	return ch;
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  printf(" Error \n");
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
  __disable_irq();
  while (1)
  {

  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
