/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_BTN_4_Pin GPIO_PIN_13
#define USER_BTN_4_GPIO_Port GPIOC
#define USER_BTN_4_EXTI_IRQn EXTI15_10_IRQn
#define DISPLAY_D13_Pin GPIO_PIN_0
#define DISPLAY_D13_GPIO_Port GPIOC
#define DISPLAY_D14_Pin GPIO_PIN_1
#define DISPLAY_D14_GPIO_Port GPIOC
#define DISPLAY_D15_Pin GPIO_PIN_2
#define DISPLAY_D15_GPIO_Port GPIOC
#define DISPLAY_D16_Pin GPIO_PIN_3
#define DISPLAY_D16_GPIO_Port GPIOC
#define DISPLAY_D00_Pin GPIO_PIN_0
#define DISPLAY_D00_GPIO_Port GPIOA
#define DISPLAY_D01_Pin GPIO_PIN_1
#define DISPLAY_D01_GPIO_Port GPIOA
#define DISPLAY_D02_Pin GPIO_PIN_2
#define DISPLAY_D02_GPIO_Port GPIOA
#define DISPLAY_D03_Pin GPIO_PIN_3
#define DISPLAY_D03_GPIO_Port GPIOA
#define DISPLAY_D04_Pin GPIO_PIN_4
#define DISPLAY_D04_GPIO_Port GPIOA
#define DISPLAY_D05_Pin GPIO_PIN_5
#define DISPLAY_D05_GPIO_Port GPIOA
#define DISPLAY_D06_Pin GPIO_PIN_6
#define DISPLAY_D06_GPIO_Port GPIOA
#define DISPLAY_D07_Pin GPIO_PIN_7
#define DISPLAY_D07_GPIO_Port GPIOA
#define DISPLAY_D17_Pin GPIO_PIN_4
#define DISPLAY_D17_GPIO_Port GPIOC
#define SDIO_CD_Pin GPIO_PIN_0
#define SDIO_CD_GPIO_Port GPIOB
#define DISPLAY_RD_Pin GPIO_PIN_12
#define DISPLAY_RD_GPIO_Port GPIOB
#define DISPLAY_WR_Pin GPIO_PIN_13
#define DISPLAY_WR_GPIO_Port GPIOB
#define DISPLAY_DC_Pin GPIO_PIN_14
#define DISPLAY_DC_GPIO_Port GPIOB
#define DISPLAY_CS_Pin GPIO_PIN_15
#define DISPLAY_CS_GPIO_Port GPIOB
#define DISPLAY_RESET_Pin GPIO_PIN_6
#define DISPLAY_RESET_GPIO_Port GPIOC
#define ESP32_EN_Pin GPIO_PIN_7
#define ESP32_EN_GPIO_Port GPIOC
#define DISPLAY_D08_Pin GPIO_PIN_8
#define DISPLAY_D08_GPIO_Port GPIOA
#define DISPLAY_D09_Pin GPIO_PIN_9
#define DISPLAY_D09_GPIO_Port GPIOA
#define DISPLAY_D10_Pin GPIO_PIN_10
#define DISPLAY_D10_GPIO_Port GPIOA
#define DISPLAY_D11_Pin GPIO_PIN_11
#define DISPLAY_D11_GPIO_Port GPIOA
#define DISPLAY_D12_Pin GPIO_PIN_12
#define DISPLAY_D12_GPIO_Port GPIOA
#define REVOLUTION_SIGNAL_Pin GPIO_PIN_15
#define REVOLUTION_SIGNAL_GPIO_Port GPIOA
#define REVOLUTION_SIGNAL_EXTI_IRQn EXTI15_10_IRQn
#define POWER_ALERT_Pin GPIO_PIN_3
#define POWER_ALERT_GPIO_Port GPIOB
#define GAUGE_ALERT_Pin GPIO_PIN_4
#define GAUGE_ALERT_GPIO_Port GPIOB
#define USER_BTN_1_Pin GPIO_PIN_5
#define USER_BTN_1_GPIO_Port GPIOB
#define USER_BTN_1_EXTI_IRQn EXTI9_5_IRQn
#define USER_BTN_2_Pin GPIO_PIN_8
#define USER_BTN_2_GPIO_Port GPIOB
#define USER_BTN_2_EXTI_IRQn EXTI9_5_IRQn
#define USER_BTN_3_Pin GPIO_PIN_9
#define USER_BTN_3_GPIO_Port GPIOB
#define USER_BTN_3_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
