/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "experiment_stm32f3.h"
#include "module_sf138.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  uint8_t i = 0;
  uint8_t dir = 0;

  GPIO_Config();
  SF138_Config();

  while(1) {
    LED_R_Toggle;
    LED_G_Toggle;
    LED_B_Toggle;

    SF138_WriteData(i);
    switch(dir) {
      case 0:   i++;  if(i == 7)  dir = 1;  break;
      case 1:   i--;  if(i == 0)  dir = 0;  break;
    }

    Delay_10ms(5);

    while(KEY_BO_Read == 1)
      SF138_Cmd(ENABLE);
    while(KEY_WU_Read == 1)
      SF138_Cmd(DISABLE);
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
