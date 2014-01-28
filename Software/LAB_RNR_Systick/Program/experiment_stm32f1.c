/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define LED_B   PCO(13)
#define LED_G   PCO(14)
#define LED_R   PCO(15)

#define KEY_WU  PAI(0)
#define KEY_BO  PBI(2)
/*=====================================================================================================*/
/*=====================================================================================================*/
vu32 Systick_Delay = 0;
void GPIO_Config( void );
void SystickDelay_1ms( vu32 DelayTimes );
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  SystemInit();
  GPIO_Config();

  if(SysTick_Config(SystemCoreClock / 72000)) {
    while (1);
  }

  while(1) {
    LED_R = ~LED_R;
    Delay_10ms(10);
    if(KEY_BO == 1 | KEY_WU == 1) {
      LED_G = ~LED_G;
      Delay_10ms(10);
    }
    LED_B = ~LED_B;
    SystickDelay_1ms(100);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

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

  LED_R = 0;
  LED_G = 0;
  LED_B = 0;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void SystickDelay_1ms( vu32 DelayTimes )
{
  Systick_Delay = DelayTimes;
  while(Systick_Delay != 0);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
