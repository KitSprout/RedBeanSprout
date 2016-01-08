/*====================================================================================================*/
/*====================================================================================================*/
#include <stdio.h>

#include "stm32f3_system.h"
#include "experiment_stm32f3.h"
#include "module_rs232.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main(void)
{
  uint16_t tmpBaudRate = 0;
  static int8_t State = ERROR;
  static uint8_t RecvData = 0;

  GPIO_Config();
  RS232_Config();
  tmpBaudRate = RS232_AutoBaudRate();

  while(1) {
    LED_G_Toggle;

    State = RS232_RecvDataWTO((int8_t*)&RecvData, 1, 200);
    if(State == ERROR) {
      RS232_SendStr((int8_t*)"0x");
      RS232_SendNum(Type_H, 4, tmpBaudRate);
      RS232_SendStr((int8_t*)"\r\n");
      Delay_100ms(1);
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
