/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"

#include "experiment_stm32f1.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define PWM_MOTOR_MIN 0
#define PWM_MOTOR_MED 500
#define PWM_MOTOR_MAX 1000

#define PWMO      TIM3->CCR1  // PA6
#define PWMO_DIV  TIM3->PSC
#define PWMO_PERI TIM3->ARR

#define PWMF      TIM4->CCR1  // PB6
#define PWMF_DIV  TIM4->PSC
#define PWMF_PERI TIM4->ARR

#define TIM2_CC_PRESCALER 1
#define TIM2_CC_FREQ      36000000
#define TIM2_CC_PERIOD    0xFFFF

TIM_HandleTypeDef TIM_HandleStruct_TIM2;

__IO uint32_t Frequency;
/*====================================================================================================*/
/*====================================================================================================*/
void PWMO_SetDuty( uint8_t duty )
{
  PWMO = (PWMO_PERI + 1) * (duty / 100.0f);
}
void PWMO_SetFreq( uint32_t freq )
{
  uint32_t perFreq = 0;
  uint32_t tmpPeri = 0;

  perFreq = (72000000 / (PWMF_DIV + 1));
  tmpPeri = perFreq / freq;
  if(99 < tmpPeri < 59999) {
    PWMO_PERI = tmpPeri - 1;
    return;
  }
}
void PWMF_SetDuty( uint8_t duty )
{
  PWMF = (PWMF_PERI + 1) * (duty / 100.0f);
}
void PWMF_SetFreq( uint32_t freq )
{
  uint32_t perFreq = 0;
  uint32_t tmpPeri = 0;

  perFreq = (72000000 / (PWMF_DIV + 1));
  tmpPeri = perFreq / freq;
  if(99 < tmpPeri < 59999) {
    PWMF_PERI = tmpPeri - 1;
    return;
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  uint32_t i = 0, state = 0;

  HAL_Init();
  GPIO_Config();
  TIM_PWM_Out_Config();
  TIM_PWM_In_Config();

  while (1) {
    LED_R_Toggle;
    LED_G_Toggle;

    i = (state) ? (i-5) : (i+5);
    if(i == 5000) state = 1;
    if(i == 100)  state = 0;

    PWMO_SetFreq(i);
    PWMO_SetDuty(50);

    PWMF_SetFreq(Frequency);
    PWMF_SetDuty(50);

    Delay_1ms(4);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_AFIO_REMAP_SWJ_NOJTAG();

  /* LED_B PC13 */  /* LED_G PC14 */  /* LED_R PC15 */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin   = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY_WU PA0 */  /* KEY_BO PB2 */
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  
  GPIO_InitStruct.Pin   = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = GPIO_PIN_2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Init
  LED_R_Set;
  LED_G_Set;
  LED_B_Set;
}
/*====================================================================================================*/
/*====================================================================================================*/
void TIM_PWM_Out_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_HandleTypeDef TIM_HandleStruct;
  TIM_OC_InitTypeDef TIM_OC_InitStruct;

  /* TIM Clk ******************************************************************/
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_TIM3_CLK_ENABLE();
  __HAL_RCC_TIM4_CLK_ENABLE();

  /* TIM Pin ******************************************************************/
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin       = GPIO_PIN_6;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin       = GPIO_PIN_6;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* TIM Init 72MHz ***********************************************************/
  TIM_HandleStruct.Instance               = TIM3;
  TIM_HandleStruct.Init.Prescaler         = 72 - 1;
  TIM_HandleStruct.Init.Period            = 1000 - 1;
  TIM_HandleStruct.Init.ClockDivision     = 0;
  TIM_HandleStruct.Init.CounterMode       = TIM_COUNTERMODE_UP;
  TIM_HandleStruct.Init.RepetitionCounter = 0;
  HAL_TIM_PWM_Init(&TIM_HandleStruct);

  /* PWM Init *****************************************************************/
  TIM_OC_InitStruct.OCMode       = TIM_OCMODE_PWM2;
  TIM_OC_InitStruct.OCFastMode   = TIM_OCFAST_DISABLE;
  TIM_OC_InitStruct.OCPolarity   = TIM_OCPOLARITY_LOW;
  TIM_OC_InitStruct.OCNPolarity  = TIM_OCPOLARITY_LOW;
  TIM_OC_InitStruct.OCIdleState  = TIM_OCIDLESTATE_SET;
  TIM_OC_InitStruct.OCNIdleState = TIM_OCNIDLESTATE_RESET;

  TIM_OC_InitStruct.Pulse = PWM_MOTOR_MED;
  HAL_TIM_PWM_ConfigChannel(&TIM_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_1);

  /* PWM Start ****************************************************************/
  HAL_TIM_PWM_Start(&TIM_HandleStruct, TIM_CHANNEL_1);

  TIM_HandleStruct.Instance = TIM4;
  HAL_TIM_PWM_Init(&TIM_HandleStruct);
  HAL_TIM_PWM_ConfigChannel(&TIM_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&TIM_HandleStruct, TIM_CHANNEL_1);
}
/*====================================================================================================*/
/*====================================================================================================*/
void TIM_PWM_In_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_IC_InitTypeDef TIM_IC_InitStruct;

  /* TIM Clk ******************************************************************/
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_TIM2_CLK_ENABLE();

  /* TIM Pin ******************************************************************/
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin       = GPIO_PIN_3;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* TIM IT *******************************************************************/
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);

  /* TIM Init 72MHz ***********************************************************/
  TIM_HandleStruct_TIM2.Instance               = TIM2;
  TIM_HandleStruct_TIM2.Init.Prescaler         = TIM2_CC_PRESCALER;
  TIM_HandleStruct_TIM2.Init.Period            = TIM2_CC_PERIOD;
  TIM_HandleStruct_TIM2.Init.ClockDivision     = 0;
  TIM_HandleStruct_TIM2.Init.CounterMode       = TIM_COUNTERMODE_UP;
  TIM_HandleStruct_TIM2.Init.RepetitionCounter = 0;
  HAL_TIM_IC_Init(&TIM_HandleStruct_TIM2);

  /* PWM Init *****************************************************************/
  TIM_IC_InitStruct.ICPolarity  = TIM_ICPOLARITY_RISING;
  TIM_IC_InitStruct.ICSelection = TIM_ICSELECTION_DIRECTTI;
  TIM_IC_InitStruct.ICPrescaler = TIM_ICPSC_DIV1;
  TIM_IC_InitStruct.ICFilter    = 0;   
  HAL_TIM_IC_ConfigChannel(&TIM_HandleStruct_TIM2, &TIM_IC_InitStruct, TIM_CHANNEL_4);

  HAL_TIM_IC_Start_IT(&TIM_HandleStruct_TIM2, TIM_CHANNEL_4);
}

void TIM2_IC4_CallBack( TIM_HandleTypeDef *htim )
{
  static uint32_t ICValue[2] = {0};

  uint32_t ICValueDiff = 0;

  LED_B_Toggle;

  ICValue[0] = ICValue[1];
  ICValue[1] = htim->Instance->CCR4;

  if(ICValue[1] > ICValue[0])
    ICValueDiff = ICValue[1] - ICValue[0]; 
  else if(ICValue[1] < ICValue[0])
    ICValueDiff = (TIM2_CC_PERIOD - ICValue[0]) + ICValue[1]; 

  Frequency = TIM2_CC_FREQ / ICValueDiff;
}
/*====================================================================================================*/
/*====================================================================================================*/
