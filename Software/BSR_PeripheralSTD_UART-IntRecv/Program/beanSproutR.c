/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"
#include "modules\module_serial.h"

#include "beanSproutR.h"
/*====================================================================================================*/
/*====================================================================================================*/
void UART_RecvEven( void )
{
  uint8_t recvData = Serial_RecvByte();
  if(recvData == 0x0D)
    Serial_SendStr("\r\n");
  else
    Serial_SendByte(recvData);
}

void BSR_Init( void )
{
  SystemInit();
  HAL_InitTick();

  BSR_GPIO_Config();
  BSR_UART_Config(UART_RecvEven);
}
/*====================================================================================================*/
/*====================================================================================================*/
void BSR_Loop( void )
{
  while(1) {
    if(KEY_BO_Read()) {
      printf("\f");
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
