/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct s_data
{
	uint8_t str12[1];
	char *str;
}				t_data;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
t_data *data;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int		ft_create_morze_array(char ***morze_array)
{
	*morze_array = (char **)malloc(sizeof(char *) * 36);
	(*morze_array)[0] = strdup("11111");
	(*morze_array)[1] = strdup("01111");
	(*morze_array)[2] = strdup("00111");
	(*morze_array)[3] = strdup("00011");
	(*morze_array)[4] = strdup("00001");
	(*morze_array)[5] = strdup("00000");
	(*morze_array)[6] = strdup("10000");
	(*morze_array)[7] = strdup("11000");
	(*morze_array)[8] = strdup("11100");
	(*morze_array)[9] = strdup("11110");
	(*morze_array)[10] = strdup("01");//a
	(*morze_array)[11] = strdup("1000");//b
	(*morze_array)[12] = strdup("1010");//c
	(*morze_array)[13] = strdup("100");//d
	(*morze_array)[14] = strdup("0");//e
	(*morze_array)[15] = strdup("0010");//f
	(*morze_array)[16] = strdup("110");//g
	(*morze_array)[17] = strdup("0000");//h
	(*morze_array)[18] = strdup("00");//i
	(*morze_array)[19] = strdup("0111");//j
	(*morze_array)[20] = strdup("101");//k
	(*morze_array)[21] = strdup("0100");//l
	(*morze_array)[22] = strdup("11");//m
	(*morze_array)[23] = strdup("10");//n
	(*morze_array)[24] = strdup("111");//o
	(*morze_array)[25] = strdup("0110");//p
	(*morze_array)[26] = strdup("1101");//q
	(*morze_array)[27] = strdup("010");//r
	(*morze_array)[28] = strdup("000");//s
	(*morze_array)[29] = strdup("1");//t
	(*morze_array)[30] = strdup("001");//u
	(*morze_array)[31] = strdup("0001");//v
	(*morze_array)[32] = strdup("011");//w
	(*morze_array)[33] = strdup("1001");//x
	(*morze_array)[34] = strdup("1011");//y
	(*morze_array)[35] = strdup("1100");//z
	return (0);
}

void	ft_strdel(char **str)
{
	free (*str);
	*str = NULL;
}

char	*ft_strjoin(char *str1, uint8_t *str12)
{
	int i;
	int len;
	char *tmp;

	if (!str1)
		return (0);
	len = strlen(str1) + 2;
	tmp = (char *)malloc(sizeof(char) * len);
	i = 0;
	while (i < strlen(str1))
	{
		tmp[i] = str1[i];
		i++;
	}
	tmp[i] = (char)(str12[0]);
	tmp[i + 1] = '\0';
	return (tmp);
}

int		ft_pause_1(uint32_t point)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_Delay(point);
	return (0);
}

int		ft_pause_3(uint32_t point)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_Delay(3 * point);
	return (0);
}

int		ft_small_signal(uint32_t point)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_Delay(point);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	return (0);
}

int		ft_big_signal(uint32_t point)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_Delay(3 * point);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	return (0);
}

int		ft_light_letter(char c, char **morze_array, uint32_t point)
{
	int num;
	int i;

	if (c >= '0' && c <= '9')
	{
		num = c - '0';
	}
	else if (c >= 'a' && c <= 'z')
	{
		num = 10 + c - 'a';
	}
	else if (c >= 'A' && c <= 'Z')
	{
		num = 10 + c - 'A';
	}
	else
	{
		return (0);
	}
	i = 0;
	while (morze_array[num][i] != '\0')
	{
		if (morze_array[num][i] == '0')
			ft_small_signal(point);
		else
			ft_big_signal(point);
		i++;
		if (morze_array[num][i] != '\0')
			ft_pause_1(point);
		if (morze_array[num][i] == '\0')
			ft_pause_3(point);
	}
	return (0);
}

int		ft_delete_first(char **str)
{
	int i;
	int len;
	char *tmp;

	len = strlen(*str);
	if (len == 1)
	{
		ft_strdel(str);
		return (0);
	}
	else
	{
		i = 1;
		tmp = (char *)malloc(sizeof(char) * len);
		while (i < len)
		{
			tmp[i - 1] = (*str)[i];
			i++;
		}
		tmp[i - 1] = '\0';
		ft_strdel(str);
		*str = strdup(tmp);
		ft_strdel(&tmp);
	}
	return (0);
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  char **morze_array = NULL;
  int point = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  data = (t_data *)malloc(sizeof(t_data));
  data->str = NULL;
  point = 400;
  ft_create_morze_array(&morze_array);
  HAL_UART_Receive_IT(&huart1, data->str12, 1);

  while (1)
  {
	  if (data->str)
	  {
		  ft_light_letter((data->str)[0], morze_array, point);
		  ft_delete_first(&(data->str));
	  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	char *tmp;

	HAL_UART_Transmit(&huart1, data->str12, 1, 0xFFFF);
	if (data->str)
	{
		tmp = ft_strjoin(data->str, data->str12);
		ft_strdel(&(data->str));
		data->str = strdup(tmp);
		ft_strdel(&tmp);
	}
	else
	{
		data->str = (char *)malloc(sizeof(char)*2);
		(data->str)[0] = (char)(data->str12)[0];
		(data->str)[1] = '\0';
	}
	HAL_UART_Receive_IT(&huart1, data->str12, 1);
}
/* USER CODE END 4 */

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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
