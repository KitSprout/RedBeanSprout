/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "experiment_stm32f3.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  GPIO_Config();
  EXTI_Config();

  while(1) {
    LED_R_Toggle;
    Delay_100ms(1);
    if(KEY_BO_Read == 1) {
      LED_G_Toggle;
      Delay_100ms(1);
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
#define EXTI_GPIO_PIN         GPIO_Pin_0
#define EXTI_GPIO_PORT        GPIOA
#define EXTI_GPIO_CLK         RCC_AHBPeriph_GPIOA
#define EXTI_GPIO_PUPD        GPIO_PuPd_DOWN

#define EXTI_PIN_SOURCE       EXTI_PinSource0
#define EXTI_PORT_SOURCE      EXTI_PortSourceGPIOA
#define EXTI_LINE             EXTI_Line0
#define EXTI_TRIGGER          EXTI_Trigger_Rising

#define EXTI_NVIC_CHANNEL     EXTI0_IRQn
#define EXTI_NVIC_P_PRIORITY  0x0F  // NVIC Preemption Priority
#define EXTI_NVIC_S_PRIORITY  0x0F  // NVIC Sub Priority

void EXTI_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  EXTI_InitTypeDef EXTI_InitStruct;
  NVIC_InitTypeDef NVIC_InitStruct;

  RCC_AHBPeriphClockCmd(EXTI_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  GPIO_InitStruct.GPIO_Pin = EXTI_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = EXTI_GPIO_PUPD;
  GPIO_Init(EXTI_GPIO_PORT, &GPIO_InitStruct);

  SYSCFG_EXTILineConfig(EXTI_PORT_SOURCE, EXTI_PIN_SOURCE);

  EXTI_InitStruct.EXTI_Line = EXTI_Line0;
  EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct.EXTI_Trigger = EXTI_TRIGGER;
  EXTI_InitStruct.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStruct);

  NVIC_InitStruct.NVIC_IRQChannel = EXTI_NVIC_CHANNEL;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = EXTI_NVIC_P_PRIORITY;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = EXTI_NVIC_S_PRIORITY;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
}
/*====================================================================================================*/
/*====================================================================================================*/
