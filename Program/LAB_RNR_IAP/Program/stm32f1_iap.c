/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_flash.h"
#include "stm32f1_iap.h"
#include "module_rs232.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define LED_B   PCO(13)
#define LED_G   PCO(14)
#define LED_R   PCO(15)

#define RecvCode 1024

u8 RecvBuf[RecvCode] = {0};
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : IAP_Init
**功能 : IAP 初始化
**輸入 : None
**輸出 : None
**使用 : IAP_Init();
**=====================================================================================================*/
/*=====================================================================================================*/
void IAP_Init( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

  /* USART1 Tx PA9 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  /* USART1 Rx PA10 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  USART_InitStruct.USART_BaudRate = 256000;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStruct);
  USART_Cmd(USART1, ENABLE);

  USART_ClearFlag(USART1, USART_FLAG_TC);
}/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : IAP_Download
**功能 : IAP Download Binary Code
**輸入 : None
**輸出 : None
**使用 : IAP_Download();
**=====================================================================================================*/
/*=====================================================================================================*/
void IAP_Download( void )
{
  u32 i = 0;
  u32 CodeSize = 0;
  u32 TempSize = 0;

  LED_G = 0;
  RS232_RecvData(USART1, (u8*)RecvBuf, 4);
  CodeSize = (RecvBuf[0]<<24) | (RecvBuf[1]<<16) | (RecvBuf[2]<<8) | (RecvBuf[3]);
  RS232_SendData(USART1, (uc8*)(RecvBuf), 4);
  RS232_RecvData(USART1, (u8*)RecvBuf, 1);
  TempSize = CodeSize;
  if(RecvBuf[0] == 0xF0) {
    while(TempSize) {
      LED_G = !LED_G;
      if(TempSize>=RecvCode) {
        RS232_RecvData(USART1, RecvBuf, RecvCode);
        Flash_WritePageU8(FLASH_PAGE_ADDR(IAP_FLASH_PAGE+i), RecvBuf, 1024);
        Flash_ReadPageU8(FLASH_PAGE_ADDR(IAP_FLASH_PAGE+i), RecvBuf, 1024);
        RS232_SendData(USART1, RecvBuf, RecvCode);
        i++;
        TempSize -= RecvCode;
      }
      else {
        RS232_RecvData(USART1, RecvBuf, TempSize);
        if(TempSize%2 != 0)
          RecvBuf[CodeSize-TempSize] = 0;
        Flash_WritePageU8(FLASH_PAGE_ADDR(IAP_FLASH_PAGE+i), RecvBuf, TempSize);
        Flash_ReadPageU8(FLASH_PAGE_ADDR(IAP_FLASH_PAGE+i), RecvBuf, TempSize);
        RS232_SendData(USART1, RecvBuf, TempSize);
        TempSize = 0;
      }
    }
  }
  else {
    LED_R = 0;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : IAP_JumpToApp
**功能 : 執行載入程式
**輸入 : None
**輸出 : None
**使用 : IAP_JumpToApp();
**=====================================================================================================*/
/*=====================================================================================================*/
void IAP_JumpToApp( void )
{
  u32 JumpAddr;
  void (*JumpToApp)(void);

  JumpAddr = *(vu32*)(IAP_APP_ADDR + 4);
  JumpToApp = (void (*)(void))JumpAddr;
  __set_MSP(*(vu32*)IAP_APP_ADDR);
  JumpToApp();
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : IAP_SetVectorTable
**功能 : 重新設定向量表
**輸入 : OffsetAPI
**輸出 : None
**使用 : IAP_SetVectorTable(IAP_FLASH_SIZE);
**=====================================================================================================*/
/*=====================================================================================================*/

/*=====================================================================================================*/
/*=====================================================================================================*/
