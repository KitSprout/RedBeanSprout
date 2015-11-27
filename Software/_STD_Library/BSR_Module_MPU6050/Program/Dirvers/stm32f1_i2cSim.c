/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_i2cSim.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define I2Cx_SCL_PIN        GPIO_Pin_5
#define I2Cx_SCL_GPIO_PORT  GPIOB
#define I2Cx_SCL_GPIO_CLK   RCC_APB2Periph_GPIOB
#define I2Cx_SCL_L          GPIO_ResetBits(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_PIN)
#define I2Cx_SCL_H          GPIO_SetBits(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_PIN)

#define I2Cx_SDA_PIN        GPIO_Pin_6
#define I2Cx_SDA_GPIO_PORT  GPIOB
#define I2Cx_SDA_GPIO_CLK   RCC_APB2Periph_GPIOB
#define I2Cx_SDA_L          GPIO_ResetBits(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_PIN)
#define I2Cx_SDA_H          GPIO_SetBits(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_PIN)
#define I2Cx_SDA_READ       GPIO_ReadInputDataBit(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_PIN)
/*====================================================================================================*/
/*====================================================================================================*/
static void SimI2C_Delay( void );
static void SimI2C_Start( void );
static void SimI2C_Stop( void );
static void SimI2C_SendACK( uint8_t SendACK );
static uint8_t SimI2C_RecvACK( void );
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SimI2C_Config
**功能 : Wait Signal Write/Read
**輸入 : None
**輸出 : None
**使用 : SimI2C_Config();
**====================================================================================================*/
/*====================================================================================================*/
void SimI2C_Config( void )
{
  GPIO_InitTypeDef  GPIO_InitStruct; 

  /* GPIO Clk Init *************************************************************/
  RCC_APB2PeriphClockCmd(I2Cx_SCL_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(I2Cx_SDA_GPIO_CLK, ENABLE);

  GPIO_InitStruct.GPIO_Pin =  I2Cx_SCL_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin =  I2Cx_SDA_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SimI2C_Delay
**功能 : Wait Signal Write/Read
**輸入 : None
**輸出 : None
**使用 : SimI2C_Delay();
**====================================================================================================*/
/*====================================================================================================*/
static void SimI2C_Delay( void )
{
  uint8_t i = 20;

  while(i)  i--;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SimI2C_Start
**功能 : I2C Start Signal
**輸入 : None
**輸出 : None
**使用 : SimI2C_Start();
**====================================================================================================*/
/*====================================================================================================*/
static void SimI2C_Start( void )
{
  I2Cx_SDA_H;
  I2Cx_SCL_H;
  SimI2C_Delay();
  I2Cx_SDA_L;
  SimI2C_Delay();
}

/*====================================================================================================*/
/*====================================================================================================*
**函數 : I2C_Stop
**功能 : I2C Stop Signal
**輸入 : None
**輸出 : None
**使用 : I2C_Stop();
**====================================================================================================*/
/*====================================================================================================*/
static void SimI2C_Stop( void )
{
  I2Cx_SDA_L;
  I2Cx_SCL_H;
  SimI2C_Delay();
  I2Cx_SDA_H;
  SimI2C_Delay();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SimI2C_SendACK
**功能 : I2C Send Acknowledge Signal
**輸入 : Ack
**輸出 : None
**使用 : SimI2C_SendACK(1);
**====================================================================================================*/
/*====================================================================================================*/
static void SimI2C_SendACK( uint8_t SendACK )
{
  I2Cx_SCL_L;
  if(SendACK)
    I2Cx_SDA_H;
  else
    I2Cx_SDA_L;
  SimI2C_Delay();
  I2Cx_SCL_H;
  SimI2C_Delay();
  I2Cx_SCL_L;
  SimI2C_Delay();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SimI2C_RecvACK
**功能 : I2C Recv Acknowledge Signal
**輸入 : None
**輸出 : RecvACK
**使用 : RecvACK = SimI2C_RecvACK();
**====================================================================================================*/
/*====================================================================================================*/
static uint8_t SimI2C_RecvACK( void )
{
  uint8_t RecvACK = 0;

  I2Cx_SCL_L;
  I2Cx_SDA_H;
  SimI2C_Delay();
	I2Cx_SCL_H;
	SimI2C_Delay();
  RecvACK = I2Cx_SDA_READ;
	I2Cx_SCL_L;
	SimI2C_Delay();

  return RecvACK;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SimI2C_SendByte
**功能 : I2C Send Byte
**輸入 : SendByte
**輸出 : None
**使用 : SimI2C_SendByte(SendByte);
**====================================================================================================*/
/*====================================================================================================*/
void SimI2C_SendByte( uint8_t SendByte )
{
  uint8_t i = 8;

  while(i--) {
    I2Cx_SCL_L;
    SimI2C_Delay();
    if(SendByte & 0x80) // MSB First
      I2Cx_SDA_H;
    else 
      I2Cx_SDA_L;
    SendByte = SendByte << 1;
    SimI2C_Delay();
    I2Cx_SCL_H;
    SimI2C_Delay();
  }
  I2Cx_SCL_L;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SimI2C_RecvByte
**功能 : I2C Recv Byte
**輸入 : None
**輸出 : RecvByte
**使用 : RecvByte = SimI2C_RecvByte();
**====================================================================================================*/
/*====================================================================================================*/
uint8_t SimI2C_RecvByte( void )
{
  uint8_t i = 8;
  uint8_t RecvByte = 0;

  I2Cx_SDA_H;
  while(i--) {
    RecvByte = RecvByte << 1;
    I2Cx_SCL_L;
    SimI2C_Delay();
    I2Cx_SCL_H;
    SimI2C_Delay();
    if(I2Cx_SDA_READ) {
      RecvByte |= 0x01;
    }
  }
  I2Cx_SCL_L;

  return RecvByte;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SimI2C_WriteReg
**功能 : I2C Write Register
**輸入 : SlaveAddr, RegisterAddr, WriteData
**輸出 : None
**使用 : SimI2C_WriteReg(SlaveAddr, RegisterAddr, WriteData);
**====================================================================================================*/
/*====================================================================================================*/
void SimI2C_WriteReg( uint8_t SlaveAddr, uint8_t RegisterAddr, uint8_t WriteData )
{
  SimI2C_Start();
  SimI2C_SendByte(SlaveAddr);
  SimI2C_RecvACK();
  SimI2C_SendByte(RegisterAddr);
  SimI2C_RecvACK();
  SimI2C_SendByte(WriteData);
  SimI2C_RecvACK();
  SimI2C_Stop();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SimI2C_ReadReg
**功能 : I2C Read Register
**輸入 : SlaveAddr, RegisterAddr, *ReadData
**輸出 : None
**使用 : SimI2C_ReadReg(SlaveAddr, RegisterAddr, &ReadData);
**====================================================================================================*/
/*====================================================================================================*/
void SimI2C_ReadReg( uint8_t SlaveAddr, uint8_t RegisterAddr, uint8_t *ReadData )
{
  SimI2C_Start();
  SimI2C_SendByte(SlaveAddr);
  SimI2C_RecvACK();
  SimI2C_SendByte(RegisterAddr);
  SimI2C_RecvACK();
  SimI2C_Start();
  SimI2C_SendByte(SlaveAddr | 0x01);
  SimI2C_RecvACK();
  *ReadData = SimI2C_RecvByte();
  SimI2C_SendACK(1);
  SimI2C_Stop();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SimI2C_ReadRegs
**功能 : I2C Read Multiple Register
**輸入 : SlaveAddr, RegisterAddr, *ReadData, NumByte
**輸出 : None
**使用 : SimI2C_ReadRegs(SlaveAddr, RegisterAddr, ReadData, NumByte);
**====================================================================================================*/
/*====================================================================================================*/
void SimI2C_ReadRegs( uint8_t SlaveAddr, uint8_t RegisterAddr, uint8_t *ReadData, uint8_t NumByte )
{
  uint8_t i = 0;

  SimI2C_Start();
  SimI2C_SendByte(SlaveAddr);
  SimI2C_RecvACK();
  SimI2C_SendByte(RegisterAddr);
  SimI2C_RecvACK();
  SimI2C_Start();
  SimI2C_SendByte(SlaveAddr | 0x01);
  SimI2C_RecvACK();
  for(i = 0; i < NumByte; i++) {
    ReadData[i] = SimI2C_RecvByte();
    if(i == NumByte-1)
      SimI2C_SendACK(1);
    else
      SimI2C_SendACK(0);
  }
  SimI2C_Stop();
}
/*====================================================================================================*/
/*====================================================================================================*/
