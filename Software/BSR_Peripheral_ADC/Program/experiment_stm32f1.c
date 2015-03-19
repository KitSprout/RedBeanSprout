/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_adc.h"
#include "experiment_stm32f1.h"
#include "module_rs232.h"
/*====================================================================================================*/
/*====================================================================================================*/
uint16_t ADC_AveTr[ADC_Channel] = {0};
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  uint8_t state = 0;

  GPIO_Config();
  ADC_Config();
  RS232_Config();

  while(1) {
    LED_R = state;
    LED_G = !state;
    LED_B = !LED_B;
    Delay_100ms(1);

    ADC_Average(ADC_AveTr, 64);

    switch(state) {
      case 0:
        RS232_SendStr((int8_t*)"ADC_IN_1 = ");
        RS232_SendNum(Type_D, 4, ADC_AveTr[0]);
        RS232_SendStr((int8_t*)"\r\n");
        if(KEY_BO == 1) state = 1;
        break;
      case 1:
        RS232_SendStr((int8_t*)"ADC_IN_2 = ");
        RS232_SendNum(Type_D, 4, ADC_AveTr[1]);
        RS232_SendStr((int8_t*)"\r\n");
        if(KEY_WU == 1) state = 0;
        break;
    }
	}
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Clk Init *************************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

  /* LED_B PC13 */	/* LED_G PC14 */	/* LED_R PC15 */
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
/*====================================================================================================*/
/*====================================================================================================*/
