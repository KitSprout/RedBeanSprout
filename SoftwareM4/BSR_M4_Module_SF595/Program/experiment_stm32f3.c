/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "experiment_stm32f3.h"
#include "module_sf595.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  uint8_t test = 0x01;

  GPIO_Config();
  SF595_Config();

  while(1) {

    for(test = 0x01; test < 0x80; test = test << 1) {
      LED_G_Toggle;
      SF595_SendByte(~test);
      Delay_10ms(5);
    }
    LED_G_Reset;
    for(test = 0x80; test > 0x01; test = test >> 1) {
      LED_B_Toggle;
      SF595_SendByte(~test);
      Delay_10ms(5);
    }
    LED_B_Reset;

    LED_R_Toggle;
    if(KEY_BO_Read == 1)
      SF595_Cmd(ENABLE);
    if(KEY_WU_Read == 1)
      SF595_Cmd(DISABLE);
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
}
/*====================================================================================================*/
/*====================================================================================================*/
