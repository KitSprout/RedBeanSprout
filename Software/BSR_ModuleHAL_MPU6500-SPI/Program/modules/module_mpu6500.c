/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"
#include "drivers\stm32f1_spi.h"

#include "module_mpu6500.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define SPIx                        SPI2
#define SPIx_CLK_ENABLE()           __HAL_RCC_SPI2_CLK_ENABLE()
#define SPIx_SPEED_HIGH             SPI_BAUDRATEPRESCALER_2
#define SPIx_SPEED_LOW              SPI_BAUDRATEPRESCALER_256

#define SPIx_CS_PIN                 GPIO_PIN_12
#define SPIx_CS_GPIO_PORT           GPIOB
#define SPIx_CS_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_CS_AF                  GPIO_AF5_SPI2
#define SPIx_CS_H                   __GPIO_SET(SPIx_CS_GPIO_PORT, SPIx_CS_PIN)
#define SPIx_CS_L                   __GPIO_RST(SPIx_CS_GPIO_PORT, SPIx_CS_PIN)

#define SPIx_SCK_PIN                GPIO_PIN_13
#define SPIx_SCK_GPIO_PORT          GPIOB
#define SPIx_SCK_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_SCK_AF                 GPIO_AF5_SPI2

#define SPIx_SDO_PIN                GPIO_PIN_14
#define SPIx_SDO_GPIO_PORT          GPIOB
#define SPIx_SDO_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_SDO_AF                 GPIO_AF5_SPI2

#define SPIx_SDI_PIN                GPIO_PIN_15
#define SPIx_SDI_GPIO_PORT          GPIOB
#define SPIx_SDI_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_SDI_AF                 GPIO_AF5_SPI2
/*====================================================================================================*/
/*====================================================================================================*/
static SPI_HandleTypeDef SPI_HandleStruct;
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_WriteReg
**功能 : Write Reg
**輸入 : WriteAddr, WriteData
**輸出 : None
**使用 : MPU6500_WriteReg(WriteAddr, WriteData);
**====================================================================================================*/
/*====================================================================================================*/
static void MPU6500_WriteReg( uint8_t WriteAddr, uint8_t WriteData )
{
  SPIx_CS_L;
  SPI_RW(SPIx, WriteAddr);
  SPI_RW(SPIx, WriteData);
  SPIx_CS_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_ReadReg
**功能 : Read Reg
**輸入 : ReadAddr
**輸出 : ReadData
**使用 : ReadData = MPU6500_ReadReg(ReadAddr);
**====================================================================================================*/
/*====================================================================================================*/
static uint8_t MPU6500_ReadReg( uint8_t ReadAddr )
{
  uint8_t ReadData = 0;

  SPIx_CS_L;
  SPI_RW(SPIx, 0x80 | ReadAddr);
  ReadData = SPI_RW(SPIx, 0xFF);
  SPIx_CS_H;

  return ReadData;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MPU6500_ReadRegs
**功能 : Read Regs
**輸入 : ReadAddr, *ReadBuf, Bytes
**輸出 : None
**使用 : MPU6500_ReadRegs(MPU6500_ACCEL_XOUT_H, ReadBuf, 14);
**=====================================================================================================*/
/*=====================================================================================================*/
static void MPU6500_ReadRegs( uint8_t ReadAddr, uint8_t *ReadBuf, uint8_t Bytes )
{
  SPIx_CS_L;
  SPI_RW(SPIx, 0x80 | ReadAddr);
  for(uint8_t i = 0; i < Bytes; i++)
    ReadBuf[i] = SPI_RW(SPIx, 0xFF);
  SPIx_CS_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_SetSpeed
**功能 : 設置 SPI 速度
**輸入 : SpeedSel
**輸出 : None
**使用 : MPU6500_SetSpeed(SPIx_SPEED_LOW);
**====================================================================================================*/
/*====================================================================================================*/
static void MPU6500_SetSpeed( uint8_t SpeedSel )
{
  __HAL_SPI_DISABLE(&SPI_HandleStruct);
  SPI_HandleStruct.Init.BaudRatePrescaler = SpeedSel;
  HAL_SPI_Init(&SPI_HandleStruct);
  __HAL_SPI_ENABLE(&SPI_HandleStruct);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_Config
**功能 : 初始化 MPU6500
**輸入 : None
**輸出 : None
**使用 : MPU6500_Config();
**====================================================================================================*/
/*====================================================================================================*/
void MPU6500_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* SPI Clk ******************************************************************/
  SPIx_CS_GPIO_CLK_ENABLE();
  SPIx_SCK_GPIO_CLK_ENABLE();
  SPIx_SDO_GPIO_CLK_ENABLE();
  SPIx_SDI_GPIO_CLK_ENABLE();
  SPIx_CLK_ENABLE();

  /* SPI Pin ******************************************************************/
  GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin       = SPIx_CS_PIN;
  HAL_GPIO_Init(SPIx_CS_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin       = SPIx_SCK_PIN;
  HAL_GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin       = SPIx_SDO_PIN;
  HAL_GPIO_Init(SPIx_SDO_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin       = SPIx_SDI_PIN;
  HAL_GPIO_Init(SPIx_SDI_GPIO_PORT, &GPIO_InitStruct);

  SPIx_CS_H;  // 低電位有效

  /* SPI Init ****************************************************************/
  SPI_HandleStruct.Instance               = SPIx;
  SPI_HandleStruct.Init.Mode              = SPI_MODE_MASTER;
  SPI_HandleStruct.Init.Direction         = SPI_DIRECTION_2LINES;
  SPI_HandleStruct.Init.DataSize          = SPI_DATASIZE_8BIT;
  SPI_HandleStruct.Init.CLKPolarity       = SPI_POLARITY_HIGH;
  SPI_HandleStruct.Init.CLKPhase          = SPI_PHASE_2EDGE;
  SPI_HandleStruct.Init.NSS               = SPI_NSS_SOFT;
  SPI_HandleStruct.Init.BaudRatePrescaler = SPIx_SPEED_LOW;
  SPI_HandleStruct.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  SPI_HandleStruct.Init.TIMode            = SPI_TIMODE_DISABLE;
  SPI_HandleStruct.Init.CRCCalculation    = SPI_CRCCALCULATION_ENABLE;
  SPI_HandleStruct.Init.CRCPolynomial     = 7;
  HAL_SPI_Init(&SPI_HandleStruct);

  __HAL_SPI_ENABLE(&SPI_HandleStruct);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_Init
**功能 : 初始化 MPU6500
**輸入 : None
**輸出 : status
**使用 : status = MPU6500_Init(&MPU_InitStruct);
**====================================================================================================*/
/*====================================================================================================*/
#define MPU6500_InitRegNum 11
uint8_t MPU6500_Init( MPU_InitTypeDef *MPUx )
{
  uint8_t status = ERROR;
  uint8_t MPU6500_InitData[MPU6500_InitRegNum][2] = {
    {0x80, MPU6500_PWR_MGMT_1},     // Reset Device
    {0x01, MPU6500_PWR_MGMT_1},     // Clock Source
    {0x30, MPU6500_USER_CTRL},      // Set I2C_MST_EN, I2C_IF_DIS
    {0x00, MPU6500_PWR_MGMT_2},     // Enable Acc & Gyro
    {0x07, MPU6500_CONFIG},         // DLPF_CFG[2:0] = 111;
    {0x18, MPU6500_GYRO_CONFIG},    // +-2000dps
    {0x08, MPU6500_ACCEL_CONFIG},   // +-4G
    {0x48, MPU6500_ACCEL_CONFIG_2}, // Set Acc Data Rates
    {0x10, MPU6500_INT_PIN_CFG},    // Set INT_ANYRD_2CLEAR
    {0x10, MPU6500_INT_ENABLE},     // 
    {0x4D, MPU6500_I2C_MST_CTRL},   // I2C Speed 400 kHz
  };

  MPU6500_InitData[5][0] = MPUx->MPU_Gyr_FullScale;       // MPU6500_GYRO_CONFIG
  MPU6500_InitData[4][0] = MPUx->MPU_Gyr_LowPassFilter;   // MPU6500_CONFIG
  MPU6500_InitData[6][0] = MPUx->MPU_Acc_FullScale;       // MPU6500_ACCEL_CONFIG
  MPU6500_InitData[7][0] = MPUx->MPU_Acc_LowPassFilter;   // MPU6500_ACCEL_CONFIG_2

  for(uint8_t i = 0; i < MPU6500_InitRegNum; i++) {
    MPU6500_WriteReg(MPU6500_InitData[i][1], MPU6500_InitData[i][0]);
    Delay_1ms(1);
  }

  status = MPU6500_Check();
  if(status != SUCCESS)
    return ERROR;

  Delay_10ms(1);

  MPU6500_SetSpeed(SPIx_SPEED_HIGH);
  Delay_10ms(1);

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_Check
**功能 : check Device ID
**輸入 : None
**輸出 : Status
**使用 : Status = MPU6500_Check();
**====================================================================================================*/
/*====================================================================================================*/
uint8_t MPU6500_Check( void )
{
  uint8_t DeviceID = ERROR;

  DeviceID = MPU6500_ReadReg(MPU6500_WHO_AM_I);
  if(DeviceID != MPU6500_Device_ID)
     return ERROR;

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_getData
**功能 : read IMU data
**輸入 : *dataIMU
**輸出 : None
**使用 : MPU6500_getData(dataIMU);
**====================================================================================================*/
/*====================================================================================================*/
void MPU6500_getData( int16_t *dataIMU )
{
  uint8_t tmpRead[22] = {0};

  MPU6500_ReadRegs(MPU6500_ACCEL_XOUT_H, tmpRead, 14);

  dataIMU[0] = (Byte16(int16_t, tmpRead[6],  tmpRead[7]));    // Temp
  dataIMU[1] = (Byte16(int16_t, tmpRead[0],  tmpRead[1]));    // Acc.X
  dataIMU[2] = (Byte16(int16_t, tmpRead[2],  tmpRead[3]));    // Acc.Y
  dataIMU[3] = (Byte16(int16_t, tmpRead[4],  tmpRead[5]));    // Acc.Z
  dataIMU[4] = (Byte16(int16_t, tmpRead[8],  tmpRead[9]));    // Gyr.X
  dataIMU[5] = (Byte16(int16_t, tmpRead[10], tmpRead[11]));   // Gyr.Y
  dataIMU[6] = (Byte16(int16_t, tmpRead[12], tmpRead[13]));   // Gyr.Z
}
/*==============================================================================================*/
/*==============================================================================================*/
