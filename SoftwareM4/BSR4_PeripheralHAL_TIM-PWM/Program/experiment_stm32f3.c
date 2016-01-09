/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"

#include "experiment_stm32f3.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define PWM_MIN 0
#define PWM_MED 500
#define PWM_MAX 1000

#define PWM TIM1->CCR1  // PA8
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  HAL_Init();
  GPIO_Config();
  TIM_PWM_Config();
}

int main( void )
{
  uint8_t state = 0;
  uint32_t i = PWM_MIN;

  System_Init();

  while(1) {
    i = (state) ? (i - 10) : (i + 10);
    PWM = i;
    if(i == PWM_MAX){ state = 1; delay_ms(1500); }
    if(i == PWM_MIN){ state = 0; delay_ms(1500); }

    LED_R_Toggle();
    LED_G_Toggle();
    LED_B_Toggle();
    delay_ms(10);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void TIM_PWM_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_HandleTypeDef TIM_InitStruct;
  TIM_OC_InitTypeDef TIM_OC_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_TIM1_CLK_ENABLE();

  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Alternate = GPIO_AF6_TIM1;
  GPIO_InitStruct.Pin       = GPIO_PIN_8;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* TIM1 use APB2 = 72 MHz */
  TIM_InitStruct.Instance               = TIM1;
  TIM_InitStruct.Init.Prescaler         = 72 - 1;       // 72 MHz / 72 = 1 MHz
  TIM_InitStruct.Init.Period            = PWM_MAX - 1;  // PWM Freq = 1 kHz
  TIM_InitStruct.Init.ClockDivision     = 0;
  TIM_InitStruct.Init.CounterMode       = TIM_COUNTERMODE_UP;
  TIM_InitStruct.Init.RepetitionCounter = 0;
  HAL_TIM_PWM_Init(&TIM_InitStruct);

  TIM_OC_InitStruct.OCMode      = TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCFastMode  = TIM_OCFAST_DISABLE;
  TIM_OC_InitStruct.OCPolarity  = TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  TIM_OC_InitStruct.OCIdleState = TIM_OCIDLESTATE_RESET;
  TIM_OC_InitStruct.OCNIdleState= TIM_OCNIDLESTATE_RESET;

  TIM_OC_InitStruct.Pulse = PWM_MED;
  HAL_TIM_PWM_ConfigChannel(&TIM_InitStruct, &TIM_OC_InitStruct, TIM_CHANNEL_1);

  HAL_TIM_PWM_Start(&TIM_InitStruct, TIM_CHANNEL_1);
}
/*====================================================================================================*/
/*====================================================================================================*/
