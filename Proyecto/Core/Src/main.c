/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "API_ALARMA.h"
#include "API_Debounce.h"
#include "API_Delay.h"
#include "API_GPIO.h"
#include "API_LEDS.h"
#include "API_MOTOR.h"
#include "API_SM.h"
#include "liquidcrystal_i2c.h"

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
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim9;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);
void MX_TIM5_Init(void);
void MX_TIM9_Init(void);
void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

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
   MX_I2C1_Init();
   MX_TIM5_Init();
   MX_TIM9_Init();
   MX_USART2_UART_Init();
   /* USER CODE BEGIN 2 */
   	/* Initialize */
 #define STEPS_90_DEGREES 50
   uint8_t rx_data;
   uint8_t alarma_estado=0;
   HAL_TIM_Base_Start(&htim5);
   	debounceFSM_Init();
   	ultrasonic_init();
   	Alarm_Init();
   	HD44780_Init(2);
   	HD44780_Clear();
   	HD44780_SetCursor(0,0);
   	HD44780_PrintStr("Nucleo");
   	HD44780_SetCursor(5,1);
   	HD44780_PrintStr("STM32f439zi");
   	HAL_Delay(3000);

   	HD44780_Display();
   	/* Clear buffer */
   /* USER CODE END 2 */

   /* Infinite loop */
   /* USER CODE BEGIN WHILE */
   while (1)
   {
     /* USER CODE END WHILE */
 	  debounceFSM_Update();

 	  	  if(readKey()){
 	  		  switch(alarma_estado){
 	  		  case 0:
 	  			if (PIR_Read() == GPIO_PIN_SET)  // Movimiento detectado
 	  			        {
 	  			            // Encender los LEDs
 	  			            LED_On();
 	  			            //Mostrar mensaje en lcd
 	  			            Mostrar_Alarma_Desactivada();
 	  			        }
 	  			        else
 	  			        {
 	  			            // Apagar los LEDs
 	  			            LED_Off();
 	  			            ////Mostrar mensaje en lcd
 	  			            Mostrar_Alarma_Activada();
 	  			        }
 	  			        HAL_Delay(100);  // Esperar 100ms antes de volver a leer el sensor
 	  			  break;
 	  		  case 1:
 	  			Alarm_Process();
 	  			HAL_Delay(100);
 	  			  break;
 	  		  default:
 	  		  }
 	  	  }
 	  	if (HAL_UART_Receive(&huart2, (uint8_t*)&rx_data, 1, HAL_MAX_DELAY) == HAL_OK) {
 	  	            Bluetooth_ProcessCommand(rx_data);
 	  	        }
     /* USER CODE BEGIN 3 */
   }
   /* USER CODE END 3 */
 }

 /**
   * @brief System Clock Configuration
   * @retval None
   */

 void Bluetooth_ProcessCommand(char command) {
     if (command == 'A') {  // Señal para mover 90°
         Stepper_Step(STEPS_90_DEGREES);
     } else if (command == 'B') {  // Señal para regresar
         Stepper_Step(-STEPS_90_DEGREES);
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
   RCC_OscInitStruct.HSEState = RCC_HSE_ON;
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
   * @brief I2C1 Initialization Function
   * @param None
   * @retval None
   */
 void MX_I2C1_Init(void)
 {

   /* USER CODE BEGIN I2C1_Init 0 */

   /* USER CODE END I2C1_Init 0 */

   /* USER CODE BEGIN I2C1_Init 1 */

   /* USER CODE END I2C1_Init 1 */
   hi2c1.Instance = I2C1;
   hi2c1.Init.ClockSpeed = 100000;
   hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
   hi2c1.Init.OwnAddress1 = 0;
   hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
   hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
   hi2c1.Init.OwnAddress2 = 0;
   hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
   hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
   if (HAL_I2C_Init(&hi2c1) != HAL_OK)
   {
     Error_Handler();
   }

   /** Configure Analogue filter
   */
   if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
   {
     Error_Handler();
   }

   /** Configure Digital filter
   */
   if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
   {
     Error_Handler();
   }
   /* USER CODE BEGIN I2C1_Init 2 */

   /* USER CODE END I2C1_Init 2 */

 }

 /**
   * @brief TIM5 Initialization Function
   * @param None
   * @retval None
   */
 void MX_TIM5_Init(void)
 {

   /* USER CODE BEGIN TIM5_Init 0 */

   /* USER CODE END TIM5_Init 0 */

   TIM_ClockConfigTypeDef sClockSourceConfig = {0};
   TIM_MasterConfigTypeDef sMasterConfig = {0};

   /* USER CODE BEGIN TIM5_Init 1 */

   /* USER CODE END TIM5_Init 1 */
   htim5.Instance = TIM5;
   htim5.Init.Prescaler = 71;
   htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
   htim5.Init.Period = 4294967295;
   htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
   htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
   if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
   {
     Error_Handler();
   }
   sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
   if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
   {
     Error_Handler();
   }
   sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
   sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
   if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
   {
     Error_Handler();
   }
   /* USER CODE BEGIN TIM5_Init 2 */

   /* USER CODE END TIM5_Init 2 */

 }

 /**
   * @brief TIM9 Initialization Function
   * @param None
   * @retval None
   */
 void MX_TIM9_Init(void)
 {

   /* USER CODE BEGIN TIM9_Init 0 */

   /* USER CODE END TIM9_Init 0 */

   TIM_ClockConfigTypeDef sClockSourceConfig = {0};

   /* USER CODE BEGIN TIM9_Init 1 */

   /* USER CODE END TIM9_Init 1 */
   htim9.Instance = TIM9;
   htim9.Init.Prescaler = 0;
   htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
   htim9.Init.Period = 65535;
   htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
   htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
   if (HAL_TIM_Base_Init(&htim9) != HAL_OK)
   {
     Error_Handler();
   }
   sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
   if (HAL_TIM_ConfigClockSource(&htim9, &sClockSourceConfig) != HAL_OK)
   {
     Error_Handler();
   }
   /* USER CODE BEGIN TIM9_Init 2 */

   /* USER CODE END TIM9_Init 2 */

 }

 /**
   * @brief USART2 Initialization Function
   * @param None
   * @retval None
   */
 void MX_USART2_UART_Init(void)
 {

   /* USER CODE BEGIN USART2_Init 0 */

   /* USER CODE END USART2_Init 0 */

   /* USER CODE BEGIN USART2_Init 1 */

   /* USER CODE END USART2_Init 1 */
   huart2.Instance = USART2;
   huart2.Init.BaudRate = 115200;
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
   /* USER CODE BEGIN USART2_Init 2 */

   /* USER CODE END USART2_Init 2 */

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
