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

#define PWM_MOTOR_MIN 800
#define PWM_MOTOR_MAX 2000  // 32~80%

#define PWM1  TIM2->CCR2
#define PWM2  TIM2->CCR3
#define PWM3  TIM2->CCR4
#define PWM4  TIM3->CCR1
#define PWM5  TIM3->CCR2
#define PWM6  TIM3->CCR3
#define PWM7  TIM3->CCR4
#define PWM8  TIM4->CCR1
#define PWM9  TIM4->CCR2
#define PWM10 TIM4->CCR3
#define PWM11 TIM4->CCR4
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void );
void PWM_Config( void );
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  u32 i = PWM_MOTOR_MIN;

  SystemInit();
  GPIO_Config();
  PWM_Config();

  while(1) {
    LED_G = ~LED_G;

    while(KEY_WU == 1) {
      PWM1  = i;
      PWM2  = i;
      PWM3  = i;
      PWM4  = i;
      PWM5  = i;
      PWM6  = i;
      PWM7  = i;
      PWM8  = i;
      PWM9  = i;
      PWM10 = i;
      PWM11 = i;
      i++;
      if(i>=PWM_MOTOR_MAX) {
        i = PWM_MOTOR_MIN;
        LED_R = ~LED_R;
      }
      Delay_1us(500);
    }

    Delay_10ms(10);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1  |  GPIO_Pin_2  | GPIO_Pin_3  | GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_6  | GPIO_Pin_7  | 
                             GPIO_Pin_8  |  GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0  |  GPIO_Pin_1  | GPIO_Pin_3  | GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_6  | GPIO_Pin_7  | 
                             GPIO_Pin_8  |  GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  
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
void PWM_Config( void )
{
  GPIO_InitTypeDef GPIO_Struct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

  /* TIM2 PWM1 PA1 */	/* TIM2 PWM2 PA2 */	/* TIM2 PWM3 PA3 */	/* TIM3 PWM4 PA6 */	/* TIM3 PWM5 PA7 */
  GPIO_Struct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_Struct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Struct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_Struct);
  /* TIM3 PWM6 PB0 */	/* TIM3 PWM7 PB1 */	/* TIM4 PWM8 PB6 */	/* TIM4 PWM9 PB7 */	/* TIM4 PWM10 PB8 */	/* TIM4 PWM11 PB9 */
  GPIO_Struct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_Struct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Struct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_Struct);

  GPIOA->ODR |= (u16)(1<<1);	// PA1上拉
  GPIOA->ODR |= (u16)(1<<2);	// PA2上拉
  GPIOA->ODR |= (u16)(1<<3);	// PA3上拉
  GPIOA->ODR |= (u16)(1<<6);	// PA6上拉
  GPIOA->ODR |= (u16)(1<<7);	// PA7上拉
  GPIOB->ODR |= (u16)(1<<0);	// PB0上拉
  GPIOB->ODR |= (u16)(1<<1);	// PB1上拉
  GPIOB->ODR |= (u16)(1<<6);	// PB6上拉
  GPIOB->ODR |= (u16)(1<<7);	// PB7上拉
  GPIOB->ODR |= (u16)(1<<8);	// PB8上拉
  GPIOB->ODR |= (u16)(1<<9);	// PB9上拉

  TIM_DeInit(TIM2);
  TIM_DeInit(TIM3);
  TIM_DeInit(TIM4);

  /************************** PWM Output **************************************/
  /* 設定 TIM2 TIM3 TIM4 Time Base */
  TIM_TimeBaseStruct.TIM_Period = (u16)(2500-1);              // 週期 = 2.5ms, 400Hz
  TIM_TimeBaseStruct.TIM_Prescaler = (u16)(72-1);             // 除頻72 = 1M ( 1us )
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;    // 上數
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStruct);

  /* 設定 TIM2 TIM3 TIM4 OC */
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;              // 配置為 PWM1 模式
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  // 致能 OC
  TIM_OCInitStruct.TIM_Pulse = PWM_MOTOR_MIN;                 // 設置跳變值
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;      // 當計數值小於 PWM_MOTOR_MIN 時為高電平
  TIM_OC2Init(TIM2, &TIM_OCInitStruct);                       // 初始化 TIM2 OC2
  TIM_OC3Init(TIM2, &TIM_OCInitStruct);                       // 初始化 TIM2 OC3
  TIM_OC4Init(TIM2, &TIM_OCInitStruct);                       // 初始化 TIM2 OC4
  TIM_OC1Init(TIM3, &TIM_OCInitStruct);                       // 初始化 TIM3 OC1
  TIM_OC2Init(TIM3, &TIM_OCInitStruct);                       // 初始化 TIM3 OC2
  TIM_OC3Init(TIM3, &TIM_OCInitStruct);                       // 初始化 TIM3 OC3
  TIM_OC4Init(TIM3, &TIM_OCInitStruct);                       // 初始化 TIM3 OC4
  TIM_OC1Init(TIM4, &TIM_OCInitStruct);                       // 初始化 TIM4 OC1
  TIM_OC2Init(TIM4, &TIM_OCInitStruct);                       // 初始化 TIM4 OC2
  TIM_OC3Init(TIM4, &TIM_OCInitStruct);                       // 初始化 TIM4 OC3
  TIM_OC4Init(TIM4, &TIM_OCInitStruct);                       // 初始化 TIM4 OC4
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);           // 致能 TIM2 OC2 預裝載
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);           // 致能 TIM2 OC3 預裝載
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);           // 致能 TIM2 OC4 預裝載
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);           // 致能 TIM3 OC1 預裝載
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);           // 致能 TIM3 OC2 預裝載
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);           // 致能 TIM3 OC3 預裝載
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);           // 致能 TIM3 OC4 預裝載
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);           // 致能 TIM4 OC1 預裝載
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);           // 致能 TIM4 OC2 預裝載
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);           // 致能 TIM4 OC3 預裝載
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);           // 致能 TIM4 OC4 預裝載

  /* 啟動 */
  TIM_ARRPreloadConfig(TIM2, ENABLE);                         // 致能 TIM2 重載寄存器ARR
  TIM_ARRPreloadConfig(TIM3, ENABLE);                         // 致能 TIM3 重載寄存器ARR
  TIM_ARRPreloadConfig(TIM4, ENABLE);                         // 致能 TIM4 重載寄存器ARR
  TIM_Cmd(TIM2, ENABLE);                                      // 致能 TIM2
  TIM_Cmd(TIM3, ENABLE);                                      // 致能 TIM3
  TIM_Cmd(TIM4, ENABLE);                                      // 致能 TIM4
}
/*=====================================================================================================*/
/*=====================================================================================================*/
