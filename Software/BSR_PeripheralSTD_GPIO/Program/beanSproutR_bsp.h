/* #include "beanSproutR_bsp.h" */

#ifndef __BEANSPROUTR_BSP_H
#define __BEANSPROUTR_BSP_H

#include "stm32f10x.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LED_R_PIN                 GPIO_Pin_15
#define LED_R_GPIO_PORT           GPIOC
#define LED_R_Set()               __GPIO_SET(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_R_Reset()             __GPIO_RST(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_R_Toggle()            __GPIO_TOG(LED_R_GPIO_PORT, LED_R_PIN)

#define LED_G_PIN                 GPIO_Pin_14
#define LED_G_GPIO_PORT           GPIOC
#define LED_G_Set()               __GPIO_SET(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_G_Reset()             __GPIO_RST(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_G_Toggle()            __GPIO_TOG(LED_G_GPIO_PORT, LED_G_PIN)

#define LED_B_PIN                 GPIO_Pin_13
#define LED_B_GPIO_PORT           GPIOC
#define LED_B_Set()               __GPIO_SET(LED_B_GPIO_PORT, LED_B_PIN)
#define LED_B_Reset()             __GPIO_RST(LED_B_GPIO_PORT, LED_B_PIN)
#define LED_B_Toggle()            __GPIO_TOG(LED_B_GPIO_PORT, LED_B_PIN)

#define KEY_WU_PIN                GPIO_Pin_0
#define KEY_WU_GPIO_PORT          GPIOA
#define KEY_WU_Read()             (__GPIO_READ(KEY_WU_GPIO_PORT, KEY_WU_PIN) == KEY_WU_PIN)

#define KEY_BO_PIN                GPIO_Pin_2
#define KEY_BO_GPIO_PORT          GPIOB
#define KEY_BO_Read()             (__GPIO_READ(KEY_BO_GPIO_PORT, KEY_BO_PIN) == KEY_BO_PIN)
/*====================================================================================================*/
/*====================================================================================================*/
void BSR_GPIO_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
