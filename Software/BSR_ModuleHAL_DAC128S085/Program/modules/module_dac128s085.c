/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"
#include "drivers\stm32f1_spi.h"

#include "module_dac128S085.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define DAC_SPIx                    SPI2
#define DAC_SPIx_CLK()              __HAL_RCC_SPI2_CLK_ENABLE()

#define DAC_SYN_PIN                 GPIO_PIN_12
#define DAC_SYN_GPIO_PORT           GPIOB
#define DAC_SYN_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()
#define DAC_SYN_H                   __GPIO_SET(DAC_SYN_GPIO_PORT, DAC_SYN_PIN)
#define DAC_SYN_L                   __GPIO_RST(DAC_SYN_GPIO_PORT, DAC_SYN_PIN)

#define DAC_SCK_PIN                 GPIO_PIN_13
#define DAC_SCK_GPIO_PORT           GPIOB
#define DAC_SCK_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()

#define DAC_SDO_PIN                 GPIO_PIN_14
#define DAC_SDO_GPIO_PORT           GPIOB
#define DAC_SDO_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()

#define DAC_SDI_PIN                 GPIO_PIN_15
#define DAC_SDI_GPIO_PORT           GPIOB
#define DAC_SDI_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()
/*====================================================================================================*/
/*====================================================================================================*/
static SPI_HandleTypeDef SPI_HandleStruct;
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

  /* SPI Clk Init *************************************************************/
  DAC_SPIx_CLK();
  DAC_SYN_GPIO_CLK_ENABLE();
  DAC_SCK_GPIO_CLK_ENABLE();
  DAC_SDO_GPIO_CLK_ENABLE();
  DAC_SDI_GPIO_CLK_ENABLE();

  /* SPI Pin ******************************************************************/
  GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin       = DAC_SYN_PIN;
  HAL_GPIO_Init(DAC_SYN_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin       = DAC_SCK_PIN;
  HAL_GPIO_Init(DAC_SCK_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin       = DAC_SDO_PIN;
  HAL_GPIO_Init(DAC_SDO_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin       = DAC_SDI_PIN;
  HAL_GPIO_Init(DAC_SDI_GPIO_PORT, &GPIO_InitStruct);

  DAC_SYN_H;  // 低電位有效

  /* SPI Init ****************************************************************/
  SPI_HandleStruct.Instance               = DAC_SPIx;
  SPI_HandleStruct.Init.Mode              = SPI_MODE_MASTER;
  SPI_HandleStruct.Init.Direction         = SPI_DIRECTION_2LINES;
  SPI_HandleStruct.Init.DataSize          = SPI_DATASIZE_16BIT;
  SPI_HandleStruct.Init.CLKPolarity       = SPI_POLARITY_LOW;
  SPI_HandleStruct.Init.CLKPhase          = SPI_PHASE_2EDGE;
  SPI_HandleStruct.Init.NSS               = SPI_NSS_SOFT;
  SPI_HandleStruct.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  SPI_HandleStruct.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  SPI_HandleStruct.Init.TIMode            = SPI_TIMODE_DISABLE;
  SPI_HandleStruct.Init.CRCCalculation    = SPI_CRCCALCULATION_ENABLE;
  SPI_HandleStruct.Init.CRCPolynomial     = 7;
  HAL_SPI_Init(&SPI_HandleStruct);

  __HAL_SPI_ENABLE(&SPI_HandleStruct);
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
/*====================================================================================================*
**函數 : DAC128S085_TestFunction
**功能 : Test DAC128S085
**輸入 : None
**輸出 : None
**使用 : DAC128S085_TestFunction();
**====================================================================================================*/
/*====================================================================================================*/
#define DELAY() Delay_100us(1)

void DAC128S085_TestFunction( void )
{
  uint16_t DAC_DATA[8] = {0};

  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]++);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]++);  // 1024 -> 2047
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]++);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]++);  // 2048 -> 3071
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]++);  // 1024 -> 2047
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]++);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]++);  // 3072 -> 4095
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]++);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]--);  // 4096 -> 3071
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]++);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]--);  // 3072 -> 4095
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]++);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]--);  // 3072 -> 4095
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]++);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]--);  // 3072 -> 4095
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]++);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]++);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]++);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]++);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]--);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]--);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]--);  //    0 -> 1023
    DELAY();
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]--);  //    0 -> 1023
    DELAY();
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
