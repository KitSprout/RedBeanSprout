/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_spi.h"
#include "module_dac8311.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define DAC_SPIx            SPI2
#define DAC_SPIx_CLK        RCC_APB1Periph_SPI2

#define DAC_SYN_PIN         GPIO_Pin_12
#define DAC_SYN_GPIO_PORT   GPIOB
#define DAC_SYN_GPIO_CLK    RCC_APB2Periph_GPIOB
#define DAC_SYN_H           GPIO_SetBits(DAC_SYN_GPIO_PORT, DAC_SYN_PIN)
#define DAC_SYN_L           GPIO_ResetBits(DAC_SYN_GPIO_PORT, DAC_SYN_PIN)

#define DAC_SCK_PIN         GPIO_Pin_13
#define DAC_SCK_GPIO_PORT   GPIOB
#define DAC_SCK_GPIO_CLK    RCC_APB2Periph_GPIOB

#define DAC_SDO_PIN         GPIO_Pin_14
#define DAC_SDO_GPIO_PORT   GPIOB
#define DAC_SDO_GPIO_CLK    RCC_APB2Periph_GPIOB

#define DAC_SDI_PIN         GPIO_Pin_15
#define DAC_SDI_GPIO_PORT   GPIOB
#define DAC_SDI_GPIO_CLK    RCC_APB2Periph_GPIOB
/*====================================================================================================*/
/*====================================================================================================*
**函數 : DAC8311_Config
**功能 : 配置 IO
**輸入 : None
**輸出 : None
**使用 : DAC8311_Config();
**====================================================================================================*/
/*====================================================================================================*/
void DAC8311_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  /* SPI Clk Init *************************************************************/
  RCC_APB1PeriphClockCmd(DAC_SPIx_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(DAC_SYN_GPIO_CLK | DAC_SCK_GPIO_CLK | DAC_SDO_GPIO_CLK | DAC_SDI_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  /* CST PB12  */
  GPIO_InitStruct.GPIO_Pin = DAC_SYN_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(DAC_SYN_GPIO_PORT, &GPIO_InitStruct);
  /* SCK PB13 */
  GPIO_InitStruct.GPIO_Pin = DAC_SCK_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(DAC_SCK_GPIO_PORT, &GPIO_InitStruct);
  /* SDO PB14 */
  GPIO_InitStruct.GPIO_Pin = DAC_SDO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(DAC_SDO_GPIO_PORT, &GPIO_InitStruct);
  /* SDI PB15 */
  GPIO_InitStruct.GPIO_Pin = DAC_SDI_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(DAC_SDI_GPIO_PORT, &GPIO_InitStruct);

  DAC_SYN_H;  // 低電位有效

  /* SPI Init ****************************************************************/
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // Full Duplex
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // Master Mode
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;                   // Data Size 16 bit
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;                           // Transitioned On The Falling Edge
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                         // Latched On the Rising Edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // Software NSS Signal
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;   // fsck = APB1 36MHz / 2 = 18MHz
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // MSB First
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(DAC_SPIx, &SPI_InitStruct);

  SPI_Cmd(DAC_SPIx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : DAC8311_SetOutput
**功能 : Set DAC Output
**輸入 : WriteData
**輸出 : None
**使用 : DAC8311_SetOutput(4096);
**====================================================================================================*/
/*====================================================================================================*/
void DAC8311_SetOutput( uint16_t WriteData )
{
  DAC_SYN_L;
  SPI_RW(DAC_SPIx, DAC8311_MODE_NORMAL | (WriteData & 0x3FFF));
  DAC_SYN_H;
}
/*====================================================================================================*/
/*====================================================================================================*/
