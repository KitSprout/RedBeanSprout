/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_adc.h"
#include "stm32f1_usart.h"
#include "module_rs232.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define LED_B   PCO(13)
#define LED_G   PCO(14)
#define LED_R   PCO(15)

#define KEY_WU  PAI(0)
#define KEY_BO  PBI(2)

#define PWM_MOTOR_MIN 0
#define PWM_MOTOR_MAX 120

#define PWM1  TIM2->CCR2
#define PWM2  TIM2->CCR3
#define PWM3  TIM2->CCR4
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void );
void PWM_Config( void );
u16 ADC_AveTr[ADC_Channel] = {0};
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  u8 i = 0;
  u8 ReadData = 0;

	SystemInit();
	GPIO_Config();
	RS232_Config();
	ADC_Config();
  PWM_Config();

  while(1) {
    LED_G = ~LED_G;

		while(KEY_WU == 1) {
			PWM2 = i;
			PWM3 = i;
			i++;
			if(i>=PWM_MOTOR_MAX) {
				i = PWM_MOTOR_MIN;
				LED_R = ~LED_R;
			}
			Delay_1us(500);
		}
    ADC_Average(ADC_AveTr);
    ReadData = (u8)(ADC_AveTr[0]*0.029296875f);   // 0~120
    PWM1 = ReadData;
    Delay_10ms(10);
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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	/* TIM2 PWM1 PA1 */	/* TIM2 PWM2 PA2 */	/* TIM2 PWM3 PA3 */
	GPIO_Struct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_Struct);

	GPIOA->ODR |= (u16)(1<<1);  //PA1上拉
	GPIOA->ODR |= (u16)(1<<2);  //PA2上拉
	GPIOA->ODR |= (u16)(1<<3);  //PA3上拉

	TIM_DeInit(TIM2);

/************************** PWM Output **************************************/
	/* 設定 TIM2 TIM3 TIM4 Time Base */
	TIM_TimeBaseStruct.TIM_Period = (u16)(120-1);               // 週期 = 2.5ms, 400Hz
	TIM_TimeBaseStruct.TIM_Prescaler = (u16)(1-1);              // 除頻36 = 1M ( 1us )
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;    // 上數
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);

	/* 設定 TIM2 TIM3 TIM4 OC */
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;              // 配置為 PWM1 模式
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  // 致能 OC
	TIM_OCInitStruct.TIM_Pulse = 60;                            // 設置跳變值
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;      // 當計數值小於 PWM_MOTOR_MIN 時為高電平
	TIM_OC2Init(TIM2, &TIM_OCInitStruct);                       // 初始化 TIM2 OC2
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);                       // 初始化 TIM2 OC3
	TIM_OC4Init(TIM2, &TIM_OCInitStruct);                       // 初始化 TIM2 OC4
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);           // 致能 TIM2 OC2 預裝載
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);           // 致能 TIM2 OC3 預裝載
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);           // 致能 TIM2 OC4 預裝載

	/* 啟動 */
	TIM_ARRPreloadConfig(TIM2, ENABLE);                         // 致能 TIM2 重載寄存器ARR
	TIM_Cmd(TIM2, ENABLE);                                      // 致能 TIM2
}
/*=====================================================================================================*/
/*=====================================================================================================*/
