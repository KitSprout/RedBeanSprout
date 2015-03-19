/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_spi.h"
#include "module_w25qxx.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define W25Q_SPIx           SPI2
#define W25Q_SPIx_CLK       RCC_APB1Periph_SPI2

#define W25Q_WP_PIN         GPIO_Pin_10
#define W25Q_WP_GPIO_PORT   GPIOB
#define W25Q_WP_GPIO_CLK    RCC_APB2Periph_GPIOB
#define W25Q_WP_H           GPIO_SetBits(W25Q_WP_GPIO_PORT, W25Q_WP_PIN)
#define W25Q_WP_L           GPIO_ResetBits(W25Q_WP_GPIO_PORT, W25Q_WP_PIN)

#define W25Q_HOL_PIN        GPIO_Pin_11
#define W25Q_HOL_GPIO_PORT  GPIOB
#define W25Q_HOL_GPIO_CLK   RCC_APB2Periph_GPIOB
#define W25Q_HOL_H          GPIO_SetBits(W25Q_HOL_GPIO_PORT, W25Q_HOL_PIN)
#define W25Q_HOL_L          GPIO_ResetBits(W25Q_HOL_GPIO_PORT, W25Q_HOL_PIN)

#define W25Q_CS_PIN         GPIO_Pin_12
#define W25Q_CS_GPIO_PORT   GPIOB
#define W25Q_CS_GPIO_CLK    RCC_APB2Periph_GPIOB
#define W25Q_CS_H           GPIO_SetBits(W25Q_CS_GPIO_PORT, W25Q_CS_PIN)
#define W25Q_CS_L           GPIO_ResetBits(W25Q_CS_GPIO_PORT, W25Q_CS_PIN)

#define W25Q_SCK_PIN        GPIO_Pin_13
#define W25Q_SCK_GPIO_PORT  GPIOB
#define W25Q_SCK_GPIO_CLK   RCC_APB2Periph_GPIOB

#define W25Q_SDO_PIN        GPIO_Pin_14
#define W25Q_SDO_GPIO_PORT  GPIOB
#define W25Q_SDO_GPIO_CLK   RCC_APB2Periph_GPIOB

#define W25Q_SDI_PIN        GPIO_Pin_15
#define W25Q_SDI_GPIO_PORT  GPIOB
#define W25Q_SDI_GPIO_CLK   RCC_APB2Periph_GPIOB
/*====================================================================================================*/
/*====================================================================================================*
**函數 : W25Q_Config
**功能 : 配置 IO
**輸入 : None
**輸出 : None
**使用 : W25Q_Config();
**====================================================================================================*/
/*====================================================================================================*/
void W25Q_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  /* SPI Clk Init *************************************************************/
  RCC_APB1PeriphClockCmd(W25Q_SPIx_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(W25Q_CS_GPIO_CLK | W25Q_SCK_GPIO_CLK | W25Q_SDO_GPIO_CLK | W25Q_SDI_GPIO_CLK | 
                         W25Q_WP_GPIO_CLK | W25Q_HOL_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  /* CS  */
  GPIO_InitStruct.GPIO_Pin = W25Q_CS_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(W25Q_CS_GPIO_PORT, &GPIO_InitStruct);
  /* SCK */
  GPIO_InitStruct.GPIO_Pin = W25Q_SCK_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(W25Q_SCK_GPIO_PORT, &GPIO_InitStruct);
  /* SDO */
  GPIO_InitStruct.GPIO_Pin = W25Q_SDO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(W25Q_SDO_GPIO_PORT, &GPIO_InitStruct);
  /* SDI */
  GPIO_InitStruct.GPIO_Pin = W25Q_SDI_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(W25Q_SDI_GPIO_PORT, &GPIO_InitStruct);

  W25Q_CS_H;  // 低電位有效

  /* SPI Init ****************************************************************/
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // Full Duplex
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // Master Mode
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                    // Data Size 16 bit
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;                           // Transitioned On The Falling Edge
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;                         // Latched On the Rising Edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // Software NSS Signal
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;  // fsck = APB1 36MHz / 2 = 18MHz
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // MSB First
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(W25Q_SPIx, &SPI_InitStruct);

  SPI_Cmd(W25Q_SPIx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : W25Q_ReadDeviceID
**功能 : Read Device ID
**輸入 : None
**輸出 : DeviceID
**使用 : DeviceID = W25Q_ReadDeviceID();
**====================================================================================================*/
/*====================================================================================================*/
uint16_t W25Q_ReadDeviceID( void )
{
  uint16_t DeviceID = 0;

  W25Q_CS_L;
  SPI_RW(W25Q_SPIx, 0x90);
  SPI_RW(W25Q_SPIx, 0x00);
  SPI_RW(W25Q_SPIx, 0x00);
  SPI_RW(W25Q_SPIx, 0x00);
  DeviceID  = SPI_RW(W25Q_SPIx, 0xFF) << 8;
  DeviceID |= SPI_RW(W25Q_SPIx, 0xFF);
  W25Q_CS_H;

  return DeviceID;
}
/*====================================================================================================*/
/*====================================================================================================*/
