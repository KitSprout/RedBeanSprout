/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "experiment_stm32f3.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  GPIO_Config();

  while(1) {
    GPIO_SetBits(GPIOA, GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3  | GPIO_Pin_4  | GPIO_Pin_5  |
                        GPIO_Pin_6  | GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
                        GPIO_Pin_15);
    GPIO_SetBits(GPIOB, GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_3  | GPIO_Pin_4  | GPIO_Pin_5  |
                        GPIO_Pin_6  | GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
                        GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    LED_R_Set;
    LED_G_Set;
    LED_B_Set;
    Delay_100ms(1);
    GPIO_ResetBits(GPIOA, GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3  | GPIO_Pin_4  | GPIO_Pin_5  |
                          GPIO_Pin_6  | GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
                          GPIO_Pin_15);
    GPIO_ResetBits(GPIOB, GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_3  | GPIO_Pin_4  | GPIO_Pin_5  |
                          GPIO_Pin_6  | GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
                          GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    LED_R_Reset;
    LED_G_Reset;
    LED_B_Reset;
    Delay_100ms(1);

    while(KEY_WU_Read == 1) {
      LED_R_Toggle;
      LED_G_Toggle;
      LED_B_Toggle;
      Delay_100ms(2);
    }
    while(KEY_BO_Read == 1) {
      LED_R_Toggle;
      Delay_100ms(1);
      LED_G_Toggle;
      Delay_100ms(1);
      LED_B_Toggle;
      Delay_100ms(1);
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC, ENABLE);

  /* LED_B PC13 */  /* LED_G PC14 */  /* LED_R PC15 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY_WU PA0 */  /* KEY_BO PB2 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  LED_R_Set;
  LED_G_Set;
  LED_B_Set;

  /* other pin */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3  | GPIO_Pin_4  | GPIO_Pin_5  |
                             GPIO_Pin_6  | GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
                             GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_3  | GPIO_Pin_4  | GPIO_Pin_5  |
                             GPIO_Pin_6  | GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
                             GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
}
/*====================================================================================================*/
/*====================================================================================================*/
