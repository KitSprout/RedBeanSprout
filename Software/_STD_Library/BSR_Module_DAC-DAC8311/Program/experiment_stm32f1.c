/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "experiment_stm32f1.h"
#include "module_dac8311.h"

#include <math.h>
/*=====================================================================================================*/
/*=====================================================================================================*/
#define toRad( Math_D )	((float)(Math_D)*0.0174532925f)

int main( void )
{
  float theta = 0.0f;
  uint16_t tmpOutput = 0;

  GPIO_Config();
  DAC8311_Config();

  Delay_100ms(1);

  LED_R = 0;
  LED_G = 0;
  LED_B = 0;

  while(1) {
    DAC8311_SetOutput(tmpOutput);
    theta = (theta == 180.0f) ? 0 : theta + 0.02f;
    tmpOutput = (uint16_t)(sinf(toRad(theta)) * 16384.0f);
    if(tmpOutput == 16384)  tmpOutput--;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Clk Init *************************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
  
  /* PC13 LED_B */	/* PC14 LED_G */	/* PC15 LED_R */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY_WU PA0 */	/* KEY_BO PB2 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  LED_R = 1;
  LED_G = 1;
  LED_B = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
