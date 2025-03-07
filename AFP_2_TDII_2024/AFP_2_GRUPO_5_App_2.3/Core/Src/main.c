/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "string.h"
#include <stdbool.h>
#include "API_GPIO.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

ETH_TxPacketConfig TxConfig;
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

ETH_HandleTypeDef heth;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ETH_Init(void);
void MX_USART3_UART_Init(void);
void MX_USB_OTG_FS_PCD_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t vector_leds [CANT_LEDS] = {LD1_Pin, LD2_Pin, LD3_Pin};
uint8_t secuencia_actual = 1; // Secuencia inicial
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
	  MX_ETH_Init();
	  MX_USART3_UART_Init();
	  MX_USB_OTG_FS_PCD_Init();
	  /* USER CODE BEGIN 2 */

	  /* USER CODE END 2 */

	  /* Infinite loop */
	  /* USER CODE BEGIN WHILE */
	  while (1)
	  {
		  switch(secuencia_actual){
		  	  	  case 1:
		  	  		  secuencia_actual = secuencia1(vector_leds, 150);
		  	  		  break;
		  	  	  case 2:
		  	  		  secuencia_actual = secuencia2(vector_leds, 300);
		  	  		  break;
		  	  	  case 3:
		  	  		  secuencia_actual = secuencia3(vector_leds);
		  	  		  break;
		  	  	  case 4:
		  	  		  secuencia_actual = secuencia4(vector_leds);
		  	  		  break;
		  	  	  default:
		  	  		  for(int j=0;j<CANT_LEDS;j++){
		  	  			writeLedOff_GPIO(vector_leds[j]);
		  	  		  }
		  	  		  break;
		  	  }
	  /* USER CODE END 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

uint8_t secuencia1(uint16_t* vector_leds, uint8_t retardo_ms){
	for(int i=0; i<CANT_LEDS;i++){
			/*TIEMPO DE ENCENDIDO*/
			for(int tick=0;tick<retardo_ms;tick++){
				if(readButton_GPIO()){
					while(readButton_GPIO()){}; //Antirebote por SW
					for(int j=0;j<CANT_LEDS;j++){
						writeLedOff_GPIO(vector_leds[j]);
					}
					return 2;
				}
				writeLedOn_GPIO(vector_leds[i]);
				HAL_Delay(1);
			}
			/*TIEMPO DE APAGADO*/
			for(int tick=0;tick<retardo_ms;tick++){
				if(readButton_GPIO()){
					while(readButton_GPIO()){};
					for(int j=0;j<CANT_LEDS;j++){
						writeLedOff_GPIO(vector_leds[j]);
					}
					return 2;
				}
				writeLedOff_GPIO(vector_leds[i]);
				HAL_Delay(1);
			}
		}
		return 1;
}

uint8_t secuencia2(uint16_t* vector_leds, uint16_t retardo_ms){
	/*TIEMPO DE ENCENDIDO*/
	for(int tick=0;tick<(retardo_ms/2);tick++){
		if(readButton_GPIO()){
			while(readButton_GPIO()){}; //Antirebote por SW
			for(int j=0;j<CANT_LEDS;j++){
				writeLedOff_GPIO(vector_leds[j]);
			}
			return 3;
		}
		for(int j=0; j<CANT_LEDS;j++){
			writeLedOn_GPIO(vector_leds[j]);
		}
    HAL_Delay(1);
	}
	/*TIEMPO DE APAGADO*/
	for(int tick=0;tick<(retardo_ms/2);tick++){
		if(readButton_GPIO()){
			while(readButton_GPIO()){};
			for(int j=0;j<CANT_LEDS;j++){
				writeLedOff_GPIO(vector_leds[j]);
			}
			return 3;
		}
		for(int j=0; j<CANT_LEDS;j++){
			writeLedOff_GPIO(vector_leds[j]);
		}
    HAL_Delay(1);
	}
	return 2;
}

uint8_t secuencia3(uint16_t* vector_leds){
	/*TIEMPO DE ENCENDIDO*/
	for(int tick=0;tick<1200;tick++){
		if(readButton_GPIO()){
			while(readButton_GPIO()){}; //Antirebote por SW
			for(int j=0;j<CANT_LEDS;j++){
				writeLedOff_GPIO(vector_leds[j]);
			}
			return 4;
		}
		if((tick%100) == 0){
			toggleLed_GPIO(vector_leds[0]);
		}
		if((tick%300) == 0){
			toggleLed_GPIO(vector_leds[1]);
		}
		if((tick%600) == 0){
			toggleLed_GPIO(vector_leds[2]);
		}
		HAL_Delay(1);
	}
	return 3;
}

uint8_t secuencia4(uint16_t* vector_leds){
	/*CONFIGURACION INICIAL*/
	for(int i=0;i<CANT_LEDS;i++){
		if((i%2 == 1)){
			writeLedOn_GPIO(vector_leds[i]);
		}else{
			writeLedOff_GPIO(vector_leds[i]);
		}
	}

	/*SECUENCIA*/
	for(int tick=0;tick<300;tick++){
		if(readButton_GPIO()){
			while(readButton_GPIO()){}; //Antirebote por SW
			for(int j=0;j<CANT_LEDS;j++){
				writeLedOff_GPIO(vector_leds[j]);
			}
			return 1;
		}
		if((tick%150) == 0){
			for(int i=0;i<CANT_LEDS;i++){
				toggleLed_GPIO(vector_leds[i]);
			}
		}
		HAL_Delay(1);
	}
	return 4;
}


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
