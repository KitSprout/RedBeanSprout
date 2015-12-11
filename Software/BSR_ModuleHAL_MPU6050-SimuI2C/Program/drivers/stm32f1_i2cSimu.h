/* #include "stm32f1_i2cSimu.h" */

#ifndef __STM32F1_I2CSIMU_H
#define __STM32F1_I2CSIMU_H

#include "stm32f1xx_hal.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef struct {
  uint32_t PinSDA;
  uint32_t PinSCL;
  uint32_t Freguency;
  GPIO_TypeDef *PortSDA;
  GPIO_TypeDef *PortSCL;
} SimuI2C_InitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void    SimuI2C_Config( SimuI2C_InitTypeDef *SimuI2C_Init );
void    SimuI2C_SendByte( SimuI2C_InitTypeDef *SimuI2C_Init, uint8_t sendByte );
uint8_t SimuI2C_RecvByte( SimuI2C_InitTypeDef *SimuI2C_Init );
void    SimuI2C_WriteReg( SimuI2C_InitTypeDef *SimuI2C_Init, uint8_t slaveAddr, uint8_t registerAddr, uint8_t writeData );
void    SimuI2C_ReadReg( SimuI2C_InitTypeDef *SimuI2C_Init, uint8_t slaveAddr, uint8_t registerAddr, uint8_t *readData );
void    SimuI2C_WriteRegs( SimuI2C_InitTypeDef *SimuI2C_Init, uint8_t slaveAddr, uint8_t registerAddr, uint8_t *writeData, uint8_t lens );
void    SimuI2C_ReadRegs( SimuI2C_InitTypeDef *SimuI2C_Init, uint8_t slaveAddr, uint8_t registerAddr, uint8_t *readData, uint8_t lens );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
