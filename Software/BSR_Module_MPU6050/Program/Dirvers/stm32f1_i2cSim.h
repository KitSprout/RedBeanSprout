/* #include "stm32f1_i2cSim.h" */

#ifndef __STM32F1_I2CSIM_H
#define __STM32F1_I2CSIM_H

#include "stm32f10x.h"
/*====================================================================================================*/
/*====================================================================================================*/
void    SimI2C_Config( void );
void    SimI2C_SendByte( uint8_t SendByte );
uint8_t SimI2C_RecvByte( void );
void    SimI2C_WriteReg( uint8_t SlaveAddr, uint8_t RegisterAddr, uint8_t WriteData );
void    SimI2C_ReadReg( uint8_t SlaveAddr, uint8_t RegisterAddr, uint8_t *ReadData );
void    SimI2C_ReadRegs( uint8_t SlaveAddr, uint8_t RegisterAddr, uint8_t *ReadData, uint8_t NumByte );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
