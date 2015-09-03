/* #include "experiment_stm32f1.h" */

#ifndef __EXPERIMENT_STM32F1_H
#define __EXPERIMENT_STM32F1_H

#include "stm32f1xx_hal.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LED_R_PIN                   GPIO_PIN_15
#define LED_R_GPIO_PORT             GPIOC
#define LED_R_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_R_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOC_CLK_DISABLE()

#define LED_G_PIN                   GPIO_PIN_14
#define LED_G_GPIO_PORT             GPIOC
#define LED_G_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_G_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOC_CLK_DISABLE()

#define LED_B_PIN                   GPIO_PIN_13
#define LED_B_GPIO_PORT             GPIOC
#define LED_B_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_B_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOC_CLK_DISABLE()

#define KEY_WU_PIN                  GPIO_PIN_0
#define KEY_WU_GPIO_PORT            GPIOA
#define KEY_WU_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOC_CLK_ENABLE()
#define KEY_WU_GPIO_CLK_DISABLE()   __HAL_RCC_GPIOC_CLK_DISABLE()

#define KEY_BO_PIN                  GPIO_PIN_2
#define KEY_BO_GPIO_PORT            GPIOB
#define KEY_BO_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOC_CLK_ENABLE()
#define KEY_BO_GPIO_CLK_DISABLE()   __HAL_RCC_GPIOC_CLK_DISABLE()

#define LED_R_Set     _GPIO_SET(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_R_Reset   _GPIO_RST(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_R_Toggle  _GPIO_TOG(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_G_Set     _GPIO_SET(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_G_Reset   _GPIO_RST(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_G_Toggle  _GPIO_TOG(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_B_Set     _GPIO_SET(LED_B_GPIO_PORT, LED_B_PIN)
#define LED_B_Reset   _GPIO_RST(LED_B_GPIO_PORT, LED_B_PIN)
#define LED_B_Toggle  _GPIO_TOG(LED_B_GPIO_PORT, LED_B_PIN)

#define KEY_WU_Read   (_GPIO_READ(KEY_WU_GPIO_PORT, KEY_WU_PIN) == KEY_WU_PIN)
#define KEY_BO_Read   (_GPIO_READ(KEY_BO_GPIO_PORT, KEY_BO_PIN) == KEY_BO_PIN)
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void );
void TIM_PWM_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
