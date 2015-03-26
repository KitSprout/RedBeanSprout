/* #include "experiment_stm32f3.h" */

#ifndef __EXPERIMENT_STM32F3_H
#define __EXPERIMENT_STM32F3_H

#include "stm32f30x.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LED_R_Set     GPIOC->BSRR = GPIO_Pin_15
#define LED_R_Reset   GPIOC->BRR  = GPIO_Pin_15
#define LED_R_Toggle  GPIOC->ODR ^= GPIO_Pin_15
#define LED_G_Set     GPIOC->BSRR = GPIO_Pin_14
#define LED_G_Reset   GPIOC->BRR  = GPIO_Pin_14
#define LED_G_Toggle  GPIOC->ODR ^= GPIO_Pin_14
#define LED_B_Set     GPIOC->BSRR = GPIO_Pin_13
#define LED_B_Reset   GPIOC->BRR  = GPIO_Pin_13
#define LED_B_Toggle  GPIOC->ODR ^= GPIO_Pin_13

#define KEY_WU_Read   ((GPIOA->IDR & GPIO_Pin_0) == GPIO_Pin_0)
#define KEY_BO_Read   ((GPIOB->IDR & GPIO_Pin_2) == GPIO_Pin_2)
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void );
void TIM_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
