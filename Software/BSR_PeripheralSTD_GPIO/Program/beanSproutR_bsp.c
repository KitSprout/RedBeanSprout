/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"

#include "beanSproutR_bsp.h"
/*====================================================================================================*/
/*====================================================================================================*/
void BSR_GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk ******************************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* GPIO all analog input *****************************************************/
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_All;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_All & (~(GPIO_Pin_13 | GPIO_Pin_14));
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* GPIO Pin ******************************************************************/
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_InitStruct.GPIO_Pin   = LED_R_PIN;
  GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = LED_G_PIN;
  GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = LED_B_PIN;
  GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_InitStruct.GPIO_Pin   = KEY_WU_PIN;
  GPIO_Init(KEY_WU_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = KEY_BO_PIN;
  GPIO_Init(KEY_BO_GPIO_PORT, &GPIO_InitStruct);

  LED_R_Set();
  LED_G_Set();
  LED_B_Set();
}
/*====================================================================================================*/
/*====================================================================================================*/
