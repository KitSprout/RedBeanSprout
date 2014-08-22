/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_spi.h"
#include "module_adt7311.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define ADT_SPIx            SPI2
#define ADT_SPIx_CLK        RCC_APB1Periph_SPI2

#define ADT_CT_PIN          GPIO_Pin_10
#define ADT_CT_GPIO_PORT    GPIOB
#define ADT_CT_GPIO_CLK     RCC_APB2Periph_GPIOB

#define ADT_INT_PIN         GPIO_Pin_11
#define ADT_INT_GPIO_PORT   GPIOB
#define ADT_INT_GPIO_CLK    RCC_APB2Periph_GPIOB

#define ADT_CS_PIN          GPIO_Pin_12
#define ADT_CS_GPIO_PORT    GPIOB
#define ADT_CS_GPIO_CLK     RCC_APB2Periph_GPIOB

#define ADT_SCK_PIN         GPIO_Pin_13
#define ADT_SCK_GPIO_PORT   GPIOB
#define ADT_SCK_GPIO_CLK    RCC_APB2Periph_GPIOB

#define ADT_SDO_PIN         GPIO_Pin_14
#define ADT_SDO_GPIO_PORT   GPIOB
#define ADT_SDO_GPIO_CLK    RCC_APB2Periph_GPIOB

#define ADT_SDI_PIN         GPIO_Pin_15
#define ADT_SDI_GPIO_PORT   GPIOB
#define ADT_SDI_GPIO_CLK    RCC_APB2Periph_GPIOB
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : ADT7311_Config
**功能 : ADT7311 Config
**輸入 : None
**輸出 : None
**使用 : ADT7311_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
void ADT7311_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  /* SPI Clk Init *************************************************************/
  RCC_APB1PeriphClockCmd(ADT_SPIx_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(ADT_INT_GPIO_CLK | ADT_CS_GPIO_CLK  | ADT_CT_GPIO_CLK  | 
                         ADT_SCK_GPIO_CLK | ADT_SDO_GPIO_CLK | ADT_SDI_GPIO_CLK |
                         RCC_APB2Periph_AFIO, ENABLE);

  GPIO_InitStruct.GPIO_Pin = ADT_CT_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(ADT_CT_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = ADT_INT_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(ADT_INT_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = ADT_CS_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(ADT_CS_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = ADT_SCK_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(ADT_SCK_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = ADT_SDO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(ADT_SDO_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = ADT_SDI_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(ADT_SDI_GPIO_PORT, &GPIO_InitStruct);

  ADT_CS = 1;
/*
SPI_CPOL_Low
SPI_CPOL_High

SPI_CPHA_1Edge
SPI_CPHA_2Edge
*/
  /* SPI Init ****************************************************************/
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // Full Duplex
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // Master Mode
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                    // Data Size 8 bit
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;                          // Transitioned On The Falling Edge
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                         // Latched On the Rising Edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // Software NSS Signal
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;  // fsck = APB1 36MHz / 2 = 18MHz
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // MSB First
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(ADT_SPIx, &SPI_InitStruct);

  SPI_Cmd(ADT_SPIx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : 
**功能 : 
**輸入 : WriteCmd
**輸出 : None
**使用 : LCD_WriteCmd(0xCB);
**====================================================================================================*/
/*====================================================================================================*/
static void ADT_WriteByte( u8 WriteAddr, u8 WriteByte )
{
  ADT_CS = 0;
  SPI_RW(ADT_SPIx, WriteAddr);
  SPI_RW(ADT_SPIx, WriteByte);
  ADT_CS = 1;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_WriteCmd
**功能 : Write Command or Address
**輸入 : WriteCmd
**輸出 : None
**使用 : LCD_WriteCmd(0xCB);
**====================================================================================================*/
/*====================================================================================================*/
static void ADT_WriteBytes( u8 WriteAddr, u16 WriteByte )
{
  ADT_CS = 0;
  SPI_RW(ADT_SPIx, WriteAddr);
  SPI_RW(ADT_SPIx, (WriteByte&0xFF00)>>8);
  SPI_RW(ADT_SPIx, (WriteByte&0x00FF));
  ADT_CS = 1;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADT_ReadByte
**功能 : Read Byte
**輸入 : ReadAddr
**輸出 : ReadByte
**使用 : ReadByte = ADT_ReadByte(ADT7311_ID);
**====================================================================================================*/
/*====================================================================================================*/
static u8 ADT_ReadByte( u8 ReadAddr )
{
  u8 ReadByte = 0;

  ReadAddr = ReadAddr | 0x40;

  ADT_CS = 0;
  SPI_RW(ADT_SPIx, ReadAddr);
  ReadByte = SPI_RW(ADT_SPIx, 0xFF);
  ADT_CS = 1;

  return ReadByte;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADT_ReadBytes
**功能 :
**輸入 : ReadAddr, *ReadByte
**輸出 : None
**使用 : ADT_ReadBytes(0xCB);
**====================================================================================================*/
/*====================================================================================================*/
static u16 ADT_ReadBytes( u8 ReadAddr )
{
  u8 ReadByte[2] = {0};

  ReadAddr = ReadAddr | 0x40;

  ADT_CS = 0;
  SPI_RW(ADT_SPIx, ReadAddr);
  ReadByte[0] = SPI_RW(ADT_SPIx, 0xFF);
  ReadByte[1] = SPI_RW(ADT_SPIx, 0xFF);
  ADT_CS = 1;

  return (Byte16(ReadByte[0], ReadByte[1]));
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADT_ReadID
**功能 : Read Device ID
**輸入 : None
**輸出 : None
**使用 : DeviceID = ADT_ReadID();   // Device ID is 0xC3
**====================================================================================================*/
/*====================================================================================================*/
u8 ADT_ReadID( void )
{
  return ADT_ReadByte(ADT7311_ID);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADT_ReadStatus
**功能 : Read Status
**輸入 : None
**輸出 : None
**使用 : Status = ADT_ReadStatus();
**====================================================================================================*/
/*====================================================================================================*/
u8 ADT_ReadStatus( void )
{
  // Bit 7  Bit 6  Bit 5  Bit 4  Bit 3  Bit 2  Bit 1  Bit 0
  //  RDY   TCRIT  THIGH   TLOW    0      0      0      0   
  return ADT_ReadByte(ADT7311_STATUS); 
}
/*=====================================================================================================*/
/*=====================================================================================================*/
