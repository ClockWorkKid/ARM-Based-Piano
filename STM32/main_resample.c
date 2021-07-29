/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#define PI 3.1415926535
#define pi 3.1415926535
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

SD_HandleTypeDef hsd1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/*************************** SD CARD FILE OPERATION VARIABLES ****************************/

#define BUFF_SIZE  64000
# define SIZE 800
# define full_SIZE 64000
double fs = 44100;
int u = 25; //upsampling ratio
int d = 33; //downsampling ratio
# define up_SIZE 19976 // SIZE*u - u + 1
# define down_SIZE 606 // (int)ceil((double)up_SIZE/d)
double a[SIZE];
double x[SIZE];
double up_x[up_SIZE];
double down_x[down_SIZE];
uint8_t FINAL_BUFFER[down_SIZE];

FRESULT res;						// status variable for file operations
FATFS SDFatFs;						// file system mount variable
FIL myFile;							// file handle
uint8_t DATA_BUFFER[BUFF_SIZE];		// temporary data buffer to store file data
uint8_t AUDIO_BUFFER[BUFF_SIZE];	// circular audio buffer continuously playing audio

int AUDIO_PTR;						// pointer for audio buffer

unsigned int bytesRead;				// number of bytes that was read from a file
unsigned int bytesWrt;				// number of bytes to be written into file

enum _bool{
	false=0,
	true=1
};
typedef enum _bool boolean;			// declared a boolean data type

char audio_filenames[36][8] = 		// filenames for binary audio files
{
	"C3.bin","C3s.bin","D3.bin","D3s.bin","E3.bin","F3.bin","F3s.bin","G3.bin","G3s.bin","A3.bin","A3s.bin","B3.bin",
	"C4.bin","C4s.bin","D4.bin","D4s.bin","E4.bin","F4.bin","F4s.bin","G4.bin","G4s.bin","A4.bin","A4s.bin","B4.bin",
	"c5.bin","C5s.bin","D5.bin","D5s.bin","E5.bin","F5.bin","F5s.bin","G5.bin","G5s.bin","A5.bin","A5s.bin","B5.bin"
};

/***************************** KEYBOARD PERPHERAL VARIABLES ******************************/

uint8_t DAC_REG;					// DAC register containing 8 bit audio samples to be output

uint32_t Fs = 8000;					// sampling frequency for note play-back

uint8_t key_ID[6], key_info[6];		// key_ID reads from Arduino DUE which key is pressed/released
									// key_info reads from Arduino DUE whether a key is pressed/released
uint8_t keypress;

/*float base_frequencies[36] =		// core audio tone frequencies starting from C3-B5
{130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94,
 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88,
 523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00, 932.33, 987.77};*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SDMMC1_SD_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/******************************* SD CARD HANDLER FUNCTIONS *********************************/

void init_SD()
{
	res = BSP_SD_Init();				// initialize SD stuff
	res = f_mount(&SDFatFs, "", 1);		// mount the SD card
}

void read_BIN_AUDIO(int note)
{
	//res = f_open(&myFile, "c5.bin", FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
	res = f_open(&myFile, audio_filenames[note], FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
	res = f_read(&myFile, DATA_BUFFER, BUFF_SIZE, &bytesRead);
	f_close(&myFile);
}

void upsample()
{
    int k,j;
    double t_step;
    double fs_u;
    double b;
    t_step = 1/fs;
    fs_u = fs*u;

    double sum;

    t0 = HAL_GetTick();
    for(k=0; k<up_SIZE; k++)
    {

        b = (double)k/fs_u;
        sum = 0;
        for (j=0;j<SIZE;j++)
        {
        	a[j] = (b/t_step) - j;

            if (a[j]!=0)
            {
                a[j] = sin(pi*a[j])/(pi*a[j]);
            }
            else
            {
                a[j] = 1;
            }
            sum = sum + a[j]*x[j];
        }

        up_x[k] = sum;
    }

}

void downsample()
{
    int k;
    for(k = 0; k<down_SIZE; k++)
    {
        down_x[k] = up_x[d*k];
    }
}

void conv_BIN_AUDIO(){

	int note = 9;	// a3 note saved in memory
	res = f_open(&myFile, audio_filenames[note], FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
	res = f_read(&myFile, DATA_BUFFER, BUFF_SIZE, &bytesRead);
	f_close(&myFile);

	int num_iter = full_SIZE/SIZE;
    int i,j;
    double float_value;

    for(i=0; i<num_iter; i++)
    {
        /*get 1000 values and load into x*/
        for (j=0; j<SIZE; j++)
        {
            //convert integer to float
           float_value = (double)((DATA_BUFFER[i*SIZE + j] - 127));
           x[j] = float_value/128;
        }

        //upsample
        upsample();

        //downsample
        downsample();

        //convert to integer again
        for (j=0; j<down_SIZE; j++)
        {
        	FINAL_BUFFER[j] = (uint8_t)(down_x[j]*128.0 + 127.0);
        }

    }

    note = 14;
	res = f_open(&myFile, audio_filenames[note], FA_OPEN_ALWAYS|FA_WRITE);
	res = f_write(&myFile, FINAL_BUFFER, down_SIZE, &bytesWrt);
	f_close(&myFile);
}




void umount_SD()
{
	f_mount(0, "", 1);					// unmount the SD card
}

/***************************** KEYBOARD PERPHERAL FUNCTIONS ******************************/
/*
ARDUINO HEADERS ON STM32F746 DISCOVERY BOARD (used for 8 bit DAC)
pin7	PI3
pin6	PH6
pin5	PI0
pin4	PG7
pin3	PB4
pin2	PG6
pin1	PC6
pin0	PC7
*/

// this function reads DAC_REG and generates corresponding DC voltage level to the DAC
void DAC_OUTPUT(){
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, !!(DAC_REG & (1<<7)));
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, !!(DAC_REG & (1<<6)));
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, !!(DAC_REG & (1<<5)));
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, !!(DAC_REG & (1<<4)));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, !!(DAC_REG & (1<<3)));
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, !!(DAC_REG & (1<<2)));
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, !!(DAC_REG & (1<<1)));
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, !!(DAC_REG & (1<<0)));
}

// starts at the current audio_pointer location and from there keeps adding values of data
// buffer to audio buffer for new tone.
void update_audio_buffer(){
	int idx_audio, idx_data;
	// int scaling_factor = 2;		// scaling factor to make sure value does not overflow
	idx_audio = AUDIO_PTR + 1;	// get current position of audio buffer pointer
	for (idx_data=0; idx_data<bytesRead; idx_data++){
		idx_audio = (idx_audio+1) % BUFF_SIZE;
		AUDIO_BUFFER[idx_audio]+=AUDIO_BUFFER[idx_audio] + DATA_BUFFER[idx_data];
	}
}

/*
Key ID data Pins	Information Pins
IDP[0] A0 PA0		INF[0] pin8 PI2
IDP[1] A1 PF10		INF[1] pin9 PA15
IDP[2] A2 PF9		INF[2] pin10 PA8
IDP[3] A3 PF8		INF[3] pin11 PB15
IDP[4] A4 PF7		INF[4] pin12 PB14
IDP[5] A5 PF6		INF[5] pin13 PI1
*/
// reads key press/release information from Arduino DUE
void keyboard_interrupt_handler(){
	key_ID[0] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	key_ID[1] = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10);
	key_ID[2] = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9);
	key_ID[3] = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8);
	key_ID[4] = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_7);
	key_ID[5] = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6);

	keypress = (key_ID[5]<<5) + (key_ID[4]<<4) + (key_ID[3]<<3) + (key_ID[2]<<2) + (key_ID[1]<<1) + (key_ID[0]<<0);

//	key_info[0] = HAL_GPIO_ReadPin(GPIOI, GPIO_PIN_2);		// interrupt
//	key_info[1] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);
//	key_info[2] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
//	key_info[3] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
//	key_info[4] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
//	key_info[5] = HAL_GPIO_ReadPin(GPIOI, GPIO_PIN_1);

	read_BIN_AUDIO(keypress);	// read the corresponding audio file from SD card and save to data buffer
	update_audio_buffer();		// add the tone to the audio buffer

}


/******************************* AUDIO HANDLER FUNCTIONS *********************************/

// initializing the audio buffer to all values = 127 (mid value of DAC)
void init_audio_buffer()
{
	int idx;
	for (idx=0; idx<BUFF_SIZE; idx++){
		AUDIO_BUFFER[idx] = 127;
	}
}

// Timer interrupt service routine, regularly reads a value from the audio
// buffer at the sampling frequency and outputs the sample via DAC
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	AUDIO_PTR = (AUDIO_PTR+1) % BUFF_SIZE;

	DAC_REG = AUDIO_BUFFER[AUDIO_PTR];
	AUDIO_BUFFER[AUDIO_PTR] = 127;		// after reading a sample, reset it

	DAC_OUTPUT();
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

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
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_SDMMC1_SD_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

  init_audio_buffer();

  init_SD();
  conv_BIN_AUDIO();
  // read_BIN_AUDIO(0);
  // umount_SD();

  HAL_TIM_Base_Start_IT(&htim2);	// initialize timer counter interrupt for audio sample rate

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  //keyboard_update();			// reads the keyboard input infinitely

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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_SDMMC1
                              |RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 50;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 5;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV4;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_8;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_CLK48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SDMMC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDMMC1_SD_Init(void)
{

  /* USER CODE BEGIN SDMMC1_Init 0 */

  /* USER CODE END SDMMC1_Init 0 */

  /* USER CODE BEGIN SDMMC1_Init 1 */

  /* USER CODE END SDMMC1_Init 1 */
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockBypass = SDMMC_CLOCK_BYPASS_DISABLE;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_1B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 0;
  /* USER CODE BEGIN SDMMC1_Init 2 */

  /* USER CODE END SDMMC1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 100;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 124;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3|GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA15 PA8 PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PI3 PI0 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : PI2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : PI1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pins : PC7 PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PG7 PG6 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PF7 PF6 PF10 PF9
                           PF8 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_9
                          |GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PH6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
