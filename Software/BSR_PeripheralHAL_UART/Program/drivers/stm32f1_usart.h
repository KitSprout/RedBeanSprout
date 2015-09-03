/* #include "stm32f1_usart.h" */

#ifndef __STM32F1_USART_H
#define __STM32F1_USART_H

#include "stm32f1xx_hal.h"
/*====================================================================================================*/
/*====================================================================================================*/
void   UART_SendByte( UART_HandleTypeDef *huart, uint8_t *sendData );
void   UART_RecvByte( UART_HandleTypeDef *huart, uint8_t *recvData );
int8_t UART_RecvByteWTO( UART_HandleTypeDef *huart, uint8_t *recvData, uint32_t timeout );
void   UART_SendData( UART_HandleTypeDef *huart, uint8_t *sendData, uint16_t dataLen );
void   UART_RecvData( UART_HandleTypeDef *huart, uint8_t *recvData, uint16_t dataLen );
int8_t UART_RecvDataWTO( UART_HandleTypeDef *huart, uint8_t *recvData, uint16_t dataLen, uint32_t timeout );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
