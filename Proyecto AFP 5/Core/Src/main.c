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
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "API_liquidcrystal_i2c.h"
#include "stm32f4xx_hal.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RX_PIN GPIO_PIN_8 //RX del HC-05
#define TX_PIN GPIO_PIN_9 //TX del HC-05
#define SENSOR_IR_PIN GPIO_PIN_0   // Pin de entrada del sensor IR (PA0)
#define SENSOR_PIR_PIN GPIO_PIN_1  // Pin de entrada del sensor PIR (PB1)
#define BUZZER_PIN GPIO_PIN_0      // Pin de salida del buzzer (PB0)
#define LED_PIN GPIO_PIN_15			// pin de salida de led
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
uint8_t modoIR = 0;  // 1 para modo IR, 0 para modo PIR
uint32_t tiempoUltimoMovimiento = 0; // Variable para almacenar el tiempo del último movimiento detectado
uint32_t tiempoEspera = 2000;
uint32_t tiempoActivacionIR = 0;
uint32_t tiempoDeteccionIR = 0; //
uint8_t alarmaIRActivada = 0;
uint8_t conteoIRIniciado = 0; //
uint8_t zumbadorActivadoIR = 0; //
uint8_t rxData; // Variable para almacenar los datos recibidos
char comandoRecibido[20]; // Buffer para los comandos
uint8_t indiceComando = 0;
/* USER CODE BEGIN PV */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
		    if (huart->Instance == USART3) { // Comprueba que es USART3
		        if (rxData == '\n' || rxData == '\r') { // Detecta fin de comando
		            comandoRecibido[indiceComando] = '\0'; // Cierra el string
		            indiceComando = 0;

		            // Compara el comando recibido
		            if (strcmp(comandoRecibido, "activar alarma") == 0) {
		                modoIR = 1; // Cambia a modo IR
		            } else if (strcmp(comandoRecibido, "desactivar alarma") == 0) {
		                modoIR = 0; // Cambia a modo PIR
		            }
		        } else {
		            comandoRecibido[indiceComando++] = rxData; // Guarda datos en el buffer
		        }

		        // Reactiva la recepción de UART
		        HAL_UART_Receive_IT(&huart3, &rxData, 1);
		    }
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
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
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Habilitar el reloj de los puertos GPIO
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  // Configuración del pin del sensor IR (entrada)
  GPIO_InitStruct.Pin = SENSOR_IR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Sin resistencias internas
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Configuración del pin del sensor PIR (entrada)
  GPIO_InitStruct.Pin = SENSOR_PIR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Configuración del pin del buzzer (salida)
  GPIO_InitStruct.Pin = BUZZER_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Push-pull para salida
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // Baja velocidad
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  //Configuracion del pin de recepcion UART del HC-05.
      GPIO_InitStruct.Pin = RX_PIN;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
      GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
      HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

      //Configuracion del pin de Transmision UART del HC-05.
      GPIO_InitStruct.Pin = TX_PIN;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
      GPIO_InitStruct.Pull = GPIO_PULLUP;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
      GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
      HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

      //Inicializar UART3.
          huart3.Instance = USART3;
          huart3.Init.BaudRate = 9600;
          huart3.Init.WordLength = UART_WORDLENGTH_8B;
          huart3.Init.StopBits = UART_STOPBITS_1;
          huart3.Init.Parity = UART_PARITY_NONE;
          huart3.Init.Mode = UART_MODE_TX_RX;
          huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
          huart3.Init.OverSampling = UART_OVERSAMPLING_16;
          if (HAL_UART_Init(&huart3) != HAL_OK) {
              Error_Handler();
          }

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  HD44780_Init(2);
  HD44780_Clear();
  HD44780_SetCursor(0,0);
  HD44780_PrintStr("Proyecto");
  HD44780_SetCursor(3,1);
  HD44780_PrintStr("Digitales II");
  HAL_Delay(3000);
  HD44780_Display();

  HAL_UART_Receive_IT(&huart3, &rxData, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  if (modoIR) {

	    		  HAL_GPIO_WritePin(GPIOD, LED_PIN, GPIO_PIN_RESET);
	    	          if (alarmaIRActivada == 0) {
	    	        	  activando_alarma();
	    	              // Esperar 3 segundos antes de activar el sensor IR
	    	              if (tiempoActivacionIR == 0) {
	    	                  tiempoActivacionIR = HAL_GetTick();
	    	              }

	    	              if (HAL_GetTick() - tiempoActivacionIR >= 3000) {
	    	                  alarmaIRActivada = 1; // Activar alarma IR después de 3 segundos
	    	                  tiempoActivacionIR = 0; // Reiniciar el tiempo de activación
	    	              }
	    	          } else {
	    	              // Modo IR activado
	    	              GPIO_PinState sensorEstadoIR = HAL_GPIO_ReadPin(GPIOA, SENSOR_IR_PIN);

	    	              if (sensorEstadoIR == GPIO_PIN_RESET && conteoIRIniciado == 0) {
	    	                  // Detección de movimiento IR, iniciar conteo
	    	                  tiempoDeteccionIR = HAL_GetTick();
	    	                  conteoIRIniciado = 1;
	    	              }

	    	              if (conteoIRIniciado) {
	    	                  alarma_conteo();
	    	              }
	    	              if (zumbadorActivadoIR == 1){
	    	                  alarma_sonando();
	    	              }else{
	    	                  HAL_GPIO_WritePin(GPIOB, BUZZER_PIN, GPIO_PIN_RESET);
	    	              }
	    	          }
	    	      } else {
	    	          // Modo PIR: Si el sensor PIR detecta algo (señal HIGH), enciende el led
	    	          GPIO_PinState sensorEstadoPIR = HAL_GPIO_ReadPin(GPIOB, SENSOR_PIR_PIN);
	    	          HAL_GPIO_WritePin(GPIOB, BUZZER_PIN, GPIO_PIN_RESET);
	    	          HAL_GPIO_WritePin(GPIOD, LED_PIN, GPIO_PIN_RESET);
	    	          if (sensorEstadoPIR == GPIO_PIN_SET) {
	    	              led_on();
	    	          } else {
	    	        	  if (HAL_GetTick() - tiempoUltimoMovimiento >= tiempoEspera) {
	    	        		  led_off();
	    	        	    }
	    	          }
	    	          alarma_desactivada();
	    	          alarmaIRActivada = 0; // Reiniciar estado IR al cambiar a PIR
	    	          conteoIRIniciado = 0;
	    	          zumbadorActivadoIR = 0; //asegurar que el zumbador este apagado.
	    	          HAL_GPIO_WritePin(GPIOB, BUZZER_PIN, GPIO_PIN_RESET); //asegurar que el buzzer este apagado.
	    	          tiempoActivacionIR =0; //reiniciar tiempo de activacion para la siguiente vez que se active el modo IR.
	    	      }
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
