/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_usart.h"
#include "stm32f1_spi.h"
#include "module_rs232.h"
#include "module_adt7311.h"
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
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  u8 DeviceID = 0;

	SystemInit();
	GPIO_Config();
	RS232_Config();
  ADT7311_Config();

  RS232_SendStr(USART1, (u8*)"\r\nHello World!\r\n\r\n");

  while(1) {
    LED_G = !LED_G;
    Delay_10ms(20);
    
    DeviceID = ADT_ReadID();
    RS232_SendStr(USART1, (u8*)"Device ID = 0x");
    RS232_SendNum(USART1, Type_H, 2, DeviceID);
    RS232_SendStr(USART1, (u8*)"\r\n");
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
