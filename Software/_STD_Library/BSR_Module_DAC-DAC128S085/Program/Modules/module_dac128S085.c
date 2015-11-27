/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_spi.h"
#include "module_dac128S085.h"
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
**函數 : DAC128S085_Config
**功能 : 配置 IO
**輸入 : None
**輸出 : None
**使用 : DAC128S085_Config();
**====================================================================================================*/
/*====================================================================================================*/
void DAC128S085_Config( void )
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
**函數 : DAC128S085_Init
**功能 : 初始化, 設定所有通道輸出為零
**輸入 : None
**輸出 : None
**使用 : DAC128S085_Init();
**====================================================================================================*/
/*====================================================================================================*/
void DAC128S085_Init( void )
{
  DAC128S085_ChangeMode(DAC_MODE_WTM);

  DAC128S085_WriteDACData(DAC_CH1, 0);
  DAC128S085_WriteDACData(DAC_CH2, 0);
  DAC128S085_WriteDACData(DAC_CH3, 0);
  DAC128S085_WriteDACData(DAC_CH4, 0);
  DAC128S085_WriteDACData(DAC_CH5, 0);
  DAC128S085_WriteDACData(DAC_CH6, 0);
  DAC128S085_WriteDACData(DAC_CH7, 0);
  DAC128S085_WriteDACData(DAC_CH8, 0);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : DAC128S085_ChangeMode
**功能 : 設定工作模式
**輸入 : BroadcastData
**輸出 : None
**使用 : DAC128S085_ChangeMode(DAC_MODE_WTM);
**====================================================================================================*/
/*====================================================================================================*/
void DAC128S085_ChangeMode( uint16_t OpMode )
{
  DAC_SYN_L;
  SPI_RW(DAC_SPIx, OpMode);
  DAC_SYN_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : DAC128S085_BroadcastData
**功能 : 廣播所有 DAC 通道的資料
**輸入 : BroadcastData
**輸出 : None
**使用 : DAC128S085_BroadcastData(2048);
**====================================================================================================*/
/*====================================================================================================*/
void DAC128S085_BroadcastData( uint16_t BroadcastData )
{
  DAC_SYN_L;
  SPI_RW(DAC_SPIx, DAC_SpCMD_Broadcast | BroadcastData);
  DAC_SYN_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : DAC128S085_WriteDACData
**功能 : Write DAC Data
**輸入 : WriteCmd
**輸出 : None
**使用 : DAC128S085_WriteDACData(DAC_CH1, 1024);
**====================================================================================================*/
/*====================================================================================================*/
void DAC128S085_WriteDACData( uint16_t DAC_Ch, uint16_t WriteData )
{
  DAC_SYN_L;
  SPI_RW(DAC_SPIx, DAC_Ch | WriteData);
  DAC_SYN_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : DAC128S085_SetInitVal
**功能 : Set Init DAC Value
**輸入 : None
**輸出 : None
**使用 : DAC128S085_SetInitVal();
**====================================================================================================*/
/*====================================================================================================*/
void DAC128S085_SetInitVal( void )
{
  uint16_t initData[8] = {
     500, // Vout_A = ( 500 / 4096) * Vref_1
    1000, // Vout_B = (1000 / 4096) * Vref_1
    1500, // Vout_C = (1500 / 4096) * Vref_1
    2000, // Vout_D = (2000 / 4096) * Vref_1
    2500, // Vout_E = (2500 / 4096) * Vref_2
    3000, // Vout_G = (3000 / 4096) * Vref_2
    3500, // Vout_G = (3500 / 4096) * Vref_2
    4000  // Vout_H = (4000 / 4096) * Vref_2
  };

  DAC128S085_WriteDACData(DAC_CH1, initData[0]);
  DAC128S085_WriteDACData(DAC_CH2, initData[1]);
  DAC128S085_WriteDACData(DAC_CH3, initData[2]);
  DAC128S085_WriteDACData(DAC_CH4, initData[3]);
  DAC128S085_WriteDACData(DAC_CH5, initData[4]);
  DAC128S085_WriteDACData(DAC_CH6, initData[5]);
  DAC128S085_WriteDACData(DAC_CH7, initData[6]);
  DAC128S085_WriteDACData(DAC_CH8, initData[7]);
}
/*====================================================================================================*/
/*====================================================================================================*/
