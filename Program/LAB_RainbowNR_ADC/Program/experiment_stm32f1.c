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
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void );

u16 ADC_AveTr[ADC_Channel] = {0};
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  u8 TrData[8] = {0};

	SystemInit();
	GPIO_Config();
	ADC_Config();
	RS232_Config();

  while(1) {
    LED_G = ~LED_G;
    ADC_Average(ADC_AveTr);

    TrData[0] = (u8)(ADC_AveTr[0]);
    TrData[1] = (u8)(ADC_AveTr[0]>>8);
    TrData[2] = (u8)(ADC_AveTr[1]);
    TrData[3] = (u8)(ADC_AveTr[1]>>8);
    TrData[4] = (u8)(ADC_AveTr[2]);
    TrData[5] = (u8)(ADC_AveTr[2]>>8);
    TrData[6] = (u8)(ADC_AveTr[3]);
    TrData[7] = (u8)(ADC_AveTr[3]>>8);
    RS232_VisualScope(USART3, TrData, 8);
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
