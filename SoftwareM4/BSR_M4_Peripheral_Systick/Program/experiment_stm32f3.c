/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "experiment_stm32f3.h"
/*====================================================================================================*/
/*====================================================================================================*/
volatile uint32_t Systick_Delay = 0;

void SystickDelay_1ms( volatile uint32_t DelayTimes )
{
  Systick_Delay = DelayTimes;
  while(Systick_Delay != 0);
}

int main( void )
{
  GPIO_Config();

  if(SysTick_Config(SystemCoreClock / 72000)) {
    while(1);
  }

  while(1) {
    LED_R_Toggle;
    Delay_100ms(1);
    if(KEY_WU_Read == 1 | KEY_BO_Read == 1) {
      LED_G_Toggle;
      Delay_100ms(1);
    }
    LED_B_Toggle;
    SystickDelay_1ms(100);
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
