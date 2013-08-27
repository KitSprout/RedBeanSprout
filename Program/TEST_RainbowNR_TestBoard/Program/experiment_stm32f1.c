/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
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
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  s16 i = 0;
  u8 TrData[4][16] = {0};

	SystemInit();
	GPIO_Config();
	RS232_Config();

  while(1) {
    PAO(1)  = LED_R;
    PAO(2)  = LED_R;
    PAO(3)  = LED_R;
    PAO(4)  = LED_R;
    PAO(5)  = LED_R;
    PAO(6)  = LED_R;
    PAO(7)  = LED_R;
    PAO(8)  = LED_R;
    PAO(11) = LED_R;
    PAO(12) = LED_R;
    PAO(15) = LED_R;
    PBO(0)  = LED_R;
    PBO(1)  = LED_R;
    PBO(3)  = LED_R;
    PBO(4)  = LED_R;
    PBO(5)  = LED_R;
    PBO(6)  = LED_R;
    PBO(7)  = LED_R;
    PBO(8)  = LED_R;
    PBO(9)  = LED_R;
    PBO(10) = LED_R;
    PBO(11) = LED_R;
    PBO(12) = LED_R;
    PBO(13) = LED_R;
    PBO(14) = LED_R;
    PBO(15) = LED_R;

    LED_R = ~LED_R;
    Delay_10ms(10);
    if(KEY_BO == 1) {
      LED_G = ~LED_G;
      Delay_10ms(10);
    }
    if(KEY_WU == 1) {
      LED_B = ~LED_B;
      Delay_10ms(10);
    }

    i++;
    if(i == 1024)  i = -1024;

    NumToChar(Type_I, 5, TrData[0], i);
    RS232_Print(USART1, (u8*)"CH1,");
    RS232_Print(USART1, TrData[0]);
    RS232_Print(USART1, (u8*)"\r\n");
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
