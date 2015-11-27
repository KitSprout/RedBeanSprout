/* #include "module_rs232.h" */

#ifndef __MODULE_RS232_H
#define __MODULE_RS232_H

#include <stdio.h>
#include "stm32f10x.h"
#include "algorithm_string.h"
/*====================================================================================================*/
/*====================================================================================================*/
void   RS232_Config( void );
void   RS232_SendByte( uint8_t SendByte );
void   RS232_SendData( uint8_t *SendData, uint16_t DataLen );
void   RS232_SendStr( uint8_t *pWord );
void   RS232_SendNum( StrType Type, uint8_t NumLen, int32_t SendData );
int8_t RS232_RecvByte( void );
void   RS232_RecvData( uint8_t *RecvData, uint16_t DataLen );
int8_t RS232_RecvDataWTO( uint8_t *RecvData, uint16_t DataLen, int32_t TimeoutMs );
void   RS232_RecvStr( uint8_t *pWord );
int8_t RS232_RecvStrWTO( uint8_t *pWord, int32_t TimeoutMs );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
