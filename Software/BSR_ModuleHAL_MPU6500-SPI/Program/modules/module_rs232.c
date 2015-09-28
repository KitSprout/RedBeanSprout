/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"
#include "drivers\stm32f1_usart.h"

#include "algorithms\algorithm_string.h"

#include "module_rs232.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define UARTx                       USART1
#define UARTx_CLK_ENABLE()          __HAL_RCC_USART1_CLK_ENABLE()

#define UARTx_TX_PIN                GPIO_PIN_9
#define UARTx_TX_GPIO_PORT          GPIOA
#define UARTx_TX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()

#define UARTx_RX_PIN                GPIO_PIN_10
#define UARTx_RX_GPIO_PORT          GPIOA
#define UARTx_RX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()

#define UARTx_BAUDRATE              115200
#define UARTx_BYTESIZE              UART_WORDLENGTH_8B
#define UARTx_STOPBITS              UART_STOPBITS_1
#define UARTx_PARITY                UART_PARITY_NONE
#define UARTx_HARDWARECTRL          UART_HWCONTROL_NONE
#define UARTx_MODE                  UART_MODE_TX_RX
/*====================================================================================================*/
/*====================================================================================================*/
static UART_HandleTypeDef UART_HandleStruct;
/*====================================================================================================*/
/*====================================================================================================*
**函數 : RS232_Config
**功能 : RS232 Config
**輸入 : None
**輸出 : None
**使用 : RS232_Config();
**====================================================================================================*/
/*====================================================================================================*/
void RS232_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* UART Clk ******************************************************************/
  UARTx_TX_GPIO_CLK_ENABLE();
  UARTx_RX_GPIO_CLK_ENABLE();
  UARTx_CLK_ENABLE();

  /* UART Pin ******************************************************************/
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin       = UARTx_TX_PIN;
  HAL_GPIO_Init(UARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin       = UARTx_RX_PIN;
  HAL_GPIO_Init(UARTx_RX_GPIO_PORT, &GPIO_InitStruct);

  /* UART Init *****************************************************************/
  UART_HandleStruct.Instance          = UARTx;
  UART_HandleStruct.Init.BaudRate     = UARTx_BAUDRATE;
  UART_HandleStruct.Init.WordLength   = UARTx_BYTESIZE;
  UART_HandleStruct.Init.StopBits     = UARTx_STOPBITS;
  UART_HandleStruct.Init.Parity       = UARTx_PARITY;
  UART_HandleStruct.Init.HwFlowCtl    = UARTx_HARDWARECTRL;
  UART_HandleStruct.Init.Mode         = UARTx_MODE;
  HAL_UART_Init(&UART_HandleStruct);

  /* UART Enable ***************************************************************/
  __HAL_UART_ENABLE(&UART_HandleStruct);
  __HAL_UART_CLEAR_FLAG(&UART_HandleStruct, UART_FLAG_TC);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : RS232_SendByte
**功能 : Send Byte
**輸入 : sendByte
**輸出 : None
**使用 : RS232_SendByte('A');
**====================================================================================================*/
/*====================================================================================================*/
void RS232_SendByte( uint8_t sendByte )
{
  UART_SendByte(&UART_HandleStruct, &sendByte);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : RS232_RecvByte
**功能 : Recv Byte
**輸入 : None
**輸出 : recvByte
**使用 : RecvByte = RS232_RecvByte();
**====================================================================================================*/
/*====================================================================================================*/
uint8_t RS232_RecvByte( void )
{
  uint8_t recvByte = 0;
  UART_RecvByte(&UART_HandleStruct, &recvByte);
  return recvByte;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : RS232_SendData
**功能 : Send Bytes
**輸入 : *sendData, DataLen
**輸出 : None
**使用 : RS232_SendData(sendData, dataLen);
**====================================================================================================*/
/*====================================================================================================*/
void RS232_SendData( uint8_t *sendData, uint16_t dataLen )
{
  UART_SendData(&UART_HandleStruct, sendData, dataLen);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : RS232_RecvData
**功能 : Recv Bytes
**輸入 : *recvData, dataLen
**輸出 : None
**使用 : RS232_RecvData(recvByte, dataLen);
**====================================================================================================*/
/*====================================================================================================*/
void RS232_RecvData( uint8_t *recvData, uint16_t dataLen )
{
  UART_RecvData(&UART_HandleStruct, recvData, dataLen);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : RS232_RecvDataWTO
**功能 : Recv Bytes with Timeout
**輸入 : *recvData, dataLen, timeout
**輸出 : state
**使用 : RS232_RecvDataWTO(recvData, dataLen, 200);
**====================================================================================================*/
/*====================================================================================================*/
int8_t RS232_RecvDataWTO( uint8_t *recvData, uint16_t dataLen, uint32_t timeout )
{
  return UART_RecvDataWTO(&UART_HandleStruct, recvData, dataLen, timeout);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : RS232_SendStr
**功能 : Send String
**輸入 : *pWord
**輸出 : None
**使用 : RS232_SendStr("Hello World!");
**====================================================================================================*/
/*====================================================================================================*/
void RS232_SendStr( char *pWord )
{
  do {
    UART_SendByte(&UART_HandleStruct, (uint8_t*)pWord++);
  } while(*pWord != '\0');
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : RS232_RecvStr
**功能 : Recv String
**輸入 : *pWord
**輸出 : None
**使用 : RS232_RecvStr(recvStirng);
**====================================================================================================*/
/*====================================================================================================*/
void RS232_RecvStr( char *pWord )
{
  do {
    UART_RecvByte(&UART_HandleStruct, (uint8_t*)pWord++);
  } while(*(pWord-1) != '\0');
  *pWord = '\0';
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : RS232_RecvStrWTO
**功能 : Recv String with Timeout
**輸入 : *pWord, TimeoutMs
**輸出 : state
**使用 : RS232_RecvStrWTO(recvStirng, 200);
**====================================================================================================*/
/*====================================================================================================*/
int8_t RS232_RecvStrWTO( char *pWord, uint32_t timeout )
{
  int8_t state = ERROR;

  do {
    state = UART_RecvByteWTO(&UART_HandleStruct, (uint8_t*)pWord++, timeout);
    if(state == ERROR)
      return ERROR;
  } while(*(pWord-1) != '\0');
  *pWord = '\0';

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : RS232_SendNum
**功能 : 將數值轉字串發送
**輸入 : type, numLen, sendData
**輸出 : None
**使用 : RS232_SendNum(Type_O, 6, 1024);
**====================================================================================================*/
/*====================================================================================================*/
void RS232_SendNum( StrType type, uint8_t numLen, int32_t sendData )
{
  char TrData[32] = {0};
  char *pWord = TrData;

  Str_NumToChar(type, numLen, TrData, sendData);

  do {
    UART_SendByte(&UART_HandleStruct, (uint8_t*)pWord++);
  } while(*pWord != '\0');
}
/*====================================================================================================*/
/*====================================================================================================*/
int fputc( int ch, FILE *f )
{
  UART_HandleStruct.Instance->DR = (ch & (uint16_t)0x01FF);
  while(!__HAL_UART_GET_FLAG(&UART_HandleStruct, UART_FLAG_TXE));
  return (ch);
}
/*====================================================================================================*/
/*====================================================================================================*/
