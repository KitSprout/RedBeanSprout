/*====================================================================================================*/
/*====================================================================================================*/
#include <stdio.h>

#include "stm32f1_system.h"
#include "experiment_stm32f1.h"
#include "module_rs232.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  static uint8_t i = 0;
  static uint8_t RecvData = 0;
  static int8_t State = ERROR;

  GPIO_Config();
  RS232_Config();

  LED_R = 0;

  printf("\r\nHello World!\r\n\r\n");

  while(1) {
    LED_G = !LED_G;
    State = RS232_RecvDataWTO((int8_t*)&RecvData, 1, 200);
    if(State == ERROR) {
      printf("Timeout ... %d\r\n", i);
      i = (i == 255) ? 0 : i + 1;
    }
    else if(RecvData == 0x0D)  // if press enter
      RS232_SendStr((int8_t*)"\r\n");
    else
      RS232_SendData((int8_t*)&RecvData, 1);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Clk Init *************************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

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
