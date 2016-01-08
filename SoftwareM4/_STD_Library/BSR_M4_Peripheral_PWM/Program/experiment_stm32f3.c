/*====================================================================================================*/
/*====================================================================================================*/
#include <stdio.h>

#include "stm32f3_system.h"
#include "experiment_stm32f3.h"
#include "module_rs232.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define PWM_PERIOD_MIN  200
#define PWM_PERIOD_MAX  2000

#define PWM1_Period     TIM3->ARR
#define PWM5_Period     TIM1->ARR

#define PWM_DUTY_MIN    0
#define PWM_DUTY_MAX    2000

#define PWM1_DutyCycle  TIM3->CCR1
#define PWM2_DutyCycle  TIM3->CCR2
#define PWM3_DutyCycle  TIM3->CCR3
#define PWM4_DutyCycle  TIM3->CCR4
#define PWM5_DutyCycle  TIM1->CCR1

extern volatile uint32_t IC1Value;
extern volatile uint32_t IC2Value;
extern volatile uint32_t DutyCycle;
extern volatile uint32_t Frequency;

int main( void )
{
  uint8_t state = 0;
  uint8_t statePeri = 1;
  int32_t i = 1000;
  int32_t j = 2000;

  GPIO_Config();
  TIM_Config();
  RS232_Config();

  while(1) {
    LED_G_Toggle;
    Delay_10ms(5);
    printf("IC1Value  = %d\r\n", IC1Value);
    printf("IC2Value  = %d\r\n", IC2Value);
    printf("DutyCycle = %d\r\n", DutyCycle);
    printf("Frequency = %d\r\n", Frequency);
    printf("\r\n");

    PWM5_DutyCycle = (uint32_t)(PWM_DUTY_MAX * DutyCycle / 200.0f);

    if(KEY_BO_Read == 1) {
      PWM1_Period = j;

      if(j >= PWM_PERIOD_MAX) statePeri = 0;
      if(j <= PWM_PERIOD_MIN) statePeri = 1;
      j = (statePeri) ? j + 50 : j - 50;
    }
    if(KEY_WU_Read == 1) {
      PWM1_DutyCycle = i;
      PWM2_DutyCycle = i;
      PWM3_DutyCycle = i;
      PWM4_DutyCycle = i;

      if(i >= PWM_DUTY_MAX) state = 0;
      if(i <= PWM_DUTY_MIN) state = 1;
      i = (state) ? i + 50 : i - 50;
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
}
/*====================================================================================================*/
/*====================================================================================================*/
void TIM_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  NVIC_InitTypeDef NVIC_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;
  TIM_ICInitTypeDef TIM_ICInitStruct;

  /* TIM Clk Init *************************************************************/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  /* TIM AF Init **************************************************************/
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_6); 
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_2);

  /* TIM GPIO Init ************************************************************/
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_6  | GPIO_Pin_7  | GPIO_Pin_8;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* TIM NVIC Base */
  NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);

  /* TIM Time Base */
  TIM_TimeBaseStruct.TIM_Period = 2000;     // 100us * 1000 = 100ms
  TIM_TimeBaseStruct.TIM_Prescaler = 72 - 1;   // F_APB1 / 72 = 1MHz
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);
  TIM_TimeBaseStruct.TIM_Period = 2000;     // 100us * 1000 = 100ms
  TIM_TimeBaseStruct.TIM_Prescaler = 72 - 1;   // F_APB1 / 72 = 1MHz
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);

  /************************** PWM Output **************************************/
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStruct.TIM_Pulse = 1000;
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  TIM_OC1Init(TIM1, &TIM_OCInitStruct);
  TIM_OC1Init(TIM3, &TIM_OCInitStruct);
  TIM_OC2Init(TIM3, &TIM_OCInitStruct);
  TIM_OC3Init(TIM3, &TIM_OCInitStruct);
  TIM_OC4Init(TIM3, &TIM_OCInitStruct);
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM1, ENABLE);
  TIM_ARRPreloadConfig(TIM3, ENABLE);

  /************************** PWM Input **************************************/
  TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct.TIM_ICFilter = 0x0;
  TIM_PWMIConfig(TIM2, &TIM_ICInitStruct);

  TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);
  TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);

  TIM_Cmd(TIM1, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
  TIM_Cmd(TIM3, ENABLE);

  TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*/
