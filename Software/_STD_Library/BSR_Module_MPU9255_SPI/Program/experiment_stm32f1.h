/* #include "experiment_stm32f1.h" */

#ifndef __EXPERIMENT_STM32F1_H
#define __EXPERIMENT_STM32F1_H

#include "stm32f10x.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LED_R_Set     _GPIO_SET(GPIOC, GPIO_Pin_15)
#define LED_R_Reset   _GPIO_RST(GPIOC, GPIO_Pin_15)
#define LED_R_Toggle  _GPIO_TOG(GPIOC, GPIO_Pin_15)
#define LED_G_Set     _GPIO_SET(GPIOC, GPIO_Pin_14)
#define LED_G_Reset   _GPIO_RST(GPIOC, GPIO_Pin_14)
#define LED_G_Toggle  _GPIO_TOG(GPIOC, GPIO_Pin_14)
#define LED_B_Set     _GPIO_SET(GPIOC, GPIO_Pin_13)
#define LED_B_Reset   _GPIO_RST(GPIOC, GPIO_Pin_13)
#define LED_B_Toggle  _GPIO_TOG(GPIOC, GPIO_Pin_13)

#define KEY_WU_Read   (_GPIO_READ(GPIOA, GPIO_Pin_0) == GPIO_Pin_0)
#define KEY_BO_Read   (_GPIO_READ(GPIOB, GPIO_Pin_2) == GPIO_Pin_2)
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
