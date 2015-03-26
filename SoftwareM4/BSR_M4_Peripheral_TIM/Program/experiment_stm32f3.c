/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "experiment_stm32f3.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  GPIO_Config();
  Timer_Config();

  while(1) {
    LED_R_Toggle;
    LED_G_Toggle;
    Delay_100ms(1);
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
#define TIMx              TIM2
#define TIMx_CLK          RCC_APB1Periph_TIM2
#define TIMx_NVIC_CHANNEL TIM2_IRQn

void Timer_Config( void )
{
  NVIC_InitTypeDef NVIC_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;

  RCC_APB1PeriphClockCmd(TIMx_CLK, ENABLE);

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStruct.NVIC_IRQChannel = TIMx_NVIC_CHANNEL;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);

  /* TIM Time Base */
  TIM_TimeBaseStruct.TIM_Period = 1000;     // 100us * 1000 = 100ms
  TIM_TimeBaseStruct.TIM_Prescaler = (SystemCoreClock / 10000) - 1;   // F_APB1 / 7200 = 10kHz ( 100us )
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Down;
  TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStruct);

  /* TIM Start */
  TIM_ClearFlag(TIMx, TIM_FLAG_Update);
  TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIMx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*/
