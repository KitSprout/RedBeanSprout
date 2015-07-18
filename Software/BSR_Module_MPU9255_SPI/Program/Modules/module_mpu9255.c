/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_spi.h"
#include "module_mpu9255.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define SPIx                SPI2
#define SPIx_CLK            RCC_APB1Periph_SPI2
#define SPIx_SPEED_HIGH     SPI_BaudRatePrescaler_4
#define SPIx_SPEED_LOW      SPI_BaudRatePrescaler_256

#define SPIx_CS_PIN         GPIO_Pin_12
#define SPIx_CS_GPIO_PORT   GPIOB
#define SPIx_CS_GPIO_CLK    RCC_APB2Periph_GPIOB
#define SPIx_CS_H           GPIO_SetBits(SPIx_CS_GPIO_PORT, SPIx_CS_PIN)
#define SPIx_CS_L           GPIO_ResetBits(SPIx_CS_GPIO_PORT, SPIx_CS_PIN)

#define SPIx_SCK_PIN        GPIO_Pin_13
#define SPIx_SCK_GPIO_PORT  GPIOB
#define SPIx_SCK_GPIO_CLK   RCC_APB2Periph_GPIOB

#define SPIx_SDO_PIN        GPIO_Pin_14
#define SPIx_SDO_GPIO_PORT  GPIOB
#define SPIx_SDO_GPIO_CLK   RCC_APB2Periph_GPIOB

#define SPIx_SDI_PIN        GPIO_Pin_15
#define SPIx_SDI_GPIO_PORT  GPIOB
#define SPIx_SDI_GPIO_CLK   RCC_APB2Periph_GPIOB

#define _USE_MAG_AK8963
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_WriteReg
**功能 : Write Reg
**輸入 : WriteAddr, WriteData
**輸出 : None
**使用 : MPU9255_WriteReg(WriteAddr, WriteData);
**====================================================================================================*/
/*====================================================================================================*/
static void MPU9255_WriteReg( uint8_t WriteAddr, uint8_t WriteData )
{
  SPIx_CS_L;
  SPI_RW(SPIx, WriteAddr);
  SPI_RW(SPIx, WriteData);
  SPIx_CS_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_ReadReg
**功能 : Read Reg
**輸入 : ReadAddr
**輸出 : ReadData
**使用 : ReadData = MPU9255_ReadReg(ReadAddr);
**====================================================================================================*/
/*====================================================================================================*/
static uint8_t MPU9255_ReadReg( uint8_t ReadAddr )
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
**函數 : MPU9255_ReadRegs
**功能 : Read Regs
**輸入 : ReadAddr, *ReadBuf, Bytes
**輸出 : None
**使用 : MPU9255_ReadRegs(MPU6555_ACCEL_XOUT_H, ReadBuf, 14);
**=====================================================================================================*/
/*=====================================================================================================*/
static void MPU9255_ReadRegs( uint8_t ReadAddr, uint8_t *ReadBuf, uint8_t Bytes )
{
  SPIx_CS_L;
  SPI_RW(SPIx, 0x80 | ReadAddr);
  for(uint8_t i = 0; i < Bytes; i++)
    ReadBuf[i] = SPI_RW(SPIx, 0xFF);
  SPIx_CS_H;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MPU9255_Mag_WriteReg
**功能 : AK8963 Write Reg
**輸入 : WriteAddr, WriteData
**輸出 : None
**使用 : MPU9255_Mag_WriteReg(AK8963_CNTL2, 0x01);
**=====================================================================================================*/
/*=====================================================================================================*/
static void MPU9255_Mag_WriteReg( uint8_t WriteAddr, uint8_t WriteData )
{
  uint8_t timeout = 0;
  uint8_t status = 0;

  MPU9255_WriteReg(MPU6555_I2C_SLV4_REG, WriteAddr);
  MPU9255_WriteReg(MPU6555_I2C_SLV4_ADDR, AK8963_I2C_ADDR);
  MPU9255_WriteReg(MPU6555_I2C_SLV4_DO, WriteData);
  MPU9255_WriteReg(MPU6555_I2C_SLV4_CTRL, 0x80);

  do {
    status = MPU9255_ReadReg(MPU6555_I2C_MST_STATUS);
  } while(((status & 0x40) == 0) && (timeout++ < 50));
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MPU9255_Mag_ReadReg
**功能 : AK8963 Read Reg
**輸入 : ReadAddr
**輸出 : ReadData
**使用 : DeviceID = MPU9255_Mag_ReadReg(AK8963_WIA);
**=====================================================================================================*/
/*=====================================================================================================*/
static uint8_t MPU9255_Mag_ReadReg( uint8_t ReadAddr )
{
	uint8_t timeout = 0;
  uint8_t status = 0;
  uint8_t ReadData = 0;

	MPU9255_WriteReg(MPU6555_I2C_SLV4_REG, ReadAddr);
	MPU9255_WriteReg(MPU6555_I2C_SLV4_ADDR, AK8963_I2C_ADDR | 0x80);
	MPU9255_WriteReg(MPU6555_I2C_SLV4_CTRL, 0x80);

  do {
    status = MPU9255_ReadReg(MPU6555_I2C_MST_STATUS);
  } while(((status & 0x40) == 0) && (timeout++ < 50));

	ReadData = MPU9255_ReadReg(MPU6555_I2C_SLV4_DI);

  return ReadData;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_SetSpeed
**功能 : 設置 SPI 速度
**輸入 : SpeedSel
**輸出 : None
**使用 : MPU9255_SetSpeed(SPIx_SPEED_LOW);
**====================================================================================================*/
/*====================================================================================================*/
static void MPU9255_SetSpeed( uint8_t SpeedSel )
{
  SPI_InitTypeDef SPI_InitStruct;

  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // Full Duplex
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // Master Mode
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                    // Data Size 16 bit
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;                          // Transitioned On The Falling Edge
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                         // Latched On the Rising Edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // Software NSS Signal
  SPI_InitStruct.SPI_BaudRatePrescaler = SpeedSel;                  // SpeedSel
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // MSB First
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(SPIx, &SPI_InitStruct);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_Config
**功能 : 初始化 MPU9255
**輸入 : None
**輸出 : None
**使用 : MPU9255_Config();
**====================================================================================================*/
/*====================================================================================================*/
void MPU9255_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  /* SPI Clk Init ************************************************************/
  RCC_APB1PeriphClockCmd(SPIx_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(SPIx_CS_GPIO_CLK  | SPIx_SCK_GPIO_CLK |
                         SPIx_SDO_GPIO_CLK | SPIx_SDI_GPIO_CLK, ENABLE);

  /* CS  */
  GPIO_InitStruct.GPIO_Pin = SPIx_CS_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SPIx_CS_GPIO_PORT, &GPIO_InitStruct);
  /* SCK */
  GPIO_InitStruct.GPIO_Pin = SPIx_SCK_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);
  /* SDO */
  GPIO_InitStruct.GPIO_Pin = SPIx_SDO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SPIx_SDO_GPIO_PORT, &GPIO_InitStruct);
  /* SDI */
  GPIO_InitStruct.GPIO_Pin = SPIx_SDI_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SPIx_SDI_GPIO_PORT, &GPIO_InitStruct);

  SPIx_CS_H;  // 低電位有效

  /* SPI Init ****************************************************************/
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // Full Duplex
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // Master Mode
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                    // Data Size 8 bit
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;                          // Transitioned On The Falling Edge
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                         // Latched On the Rising Edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // Software NSS Signal
  SPI_InitStruct.SPI_BaudRatePrescaler = SPIx_SPEED_LOW;            // fsck = APB1 36MHz / 2 = 18MHz
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // MSB First
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(SPIx, &SPI_InitStruct);

  SPI_Cmd(SPIx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_Init
**功能 : 初始化 MPU9255
**輸入 : None
**輸出 : status
**使用 : status = MPU9255_Init(&MPU_InitStruct);
**====================================================================================================*/
/*====================================================================================================*/
#define MPU6555_InitRegNum 11
#define AK8963_InitRegNum  2
uint8_t MPU9255_Init( MPU_InitTypeDef *MPUx )
{
  uint8_t status = ERROR;
  uint8_t MPU6555_InitData[MPU6555_InitRegNum][2] = {
    {0x80, MPU6555_PWR_MGMT_1},     // Reset Device
    {0x01, MPU6555_PWR_MGMT_1},     // Clock Source
    {0x30, MPU6555_USER_CTRL},      // Set I2C_MST_EN, I2C_IF_DIS
    {0x00, MPU6555_PWR_MGMT_2},     // Enable Acc & Gyro
    {0x07, MPU6555_CONFIG},         // DLPF_CFG[2:0] = 111;
    {0x18, MPU6555_GYRO_CONFIG},    // +-2000dps
    {0x08, MPU6555_ACCEL_CONFIG},   // +-4G
    {0x48, MPU6555_ACCEL_CONFIG_2}, // Set Acc Data Rates
    {0x10, MPU6555_INT_PIN_CFG},    // Set INT_ANYRD_2CLEAR
    {0x10, MPU6555_INT_ENABLE},     // 
    {0x4D, MPU6555_I2C_MST_CTRL},   // I2C Speed 400 kHz
  };
  uint8_t AK8963_InitData[AK8963_InitRegNum][2] = {
    {0x01, AK8963_CNTL2},           // Reset Device
    {0x06, AK8963_CNTL1},           // Continuous measurement mode 2
  };

  MPU6555_InitData[5][0] = MPUx->MPU_Gyr_FullScale;       // MPU6555_GYRO_CONFIG
  MPU6555_InitData[4][0] = MPUx->MPU_Gyr_LowPassFilter;   // MPU6555_CONFIG
  MPU6555_InitData[6][0] = MPUx->MPU_Acc_FullScale;       // MPU6555_ACCEL_CONFIG
  MPU6555_InitData[7][0] = MPUx->MPU_Acc_LowPassFilter;   // MPU6555_ACCEL_CONFIG_2
  AK8963_InitData[1][0] |= MPUx->MPU_Mag_FullScale;

  for(uint8_t i = 0; i < MPU6555_InitRegNum; i++) {
    MPU9255_WriteReg(MPU6555_InitData[i][1], MPU6555_InitData[i][0]);
    Delay_1ms(1);
  }

  status = MPU9255_Check();
  if(status != SUCCESS)
    return ERROR;

  Delay_10ms(1);

#ifdef _USE_MAG_AK8963
  for(uint8_t i = 0; i < AK8963_InitRegNum; i++) {
    MPU9255_Mag_WriteReg(AK8963_InitData[i][1], AK8963_InitData[i][0]);
    Delay_10ms(1);
  }

	MPU9255_WriteReg(MPU6555_I2C_SLV0_REG, AK8963_ST1);
	MPU9255_WriteReg(MPU6555_I2C_SLV0_ADDR, AK8963_I2C_ADDR | 0x80);
	MPU9255_WriteReg(MPU6555_I2C_SLV0_CTRL, 0x80 | 8);
#endif

  MPU9255_SetSpeed(SPIx_SPEED_HIGH);
  Delay_10ms(1);

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_Check
**功能 : check Device ID
**輸入 : None
**輸出 : Status
**使用 : Status = MPU9255_Check();
**====================================================================================================*/
/*====================================================================================================*/
uint8_t MPU9255_Check( void )
{
  uint8_t DeviceID = ERROR;

  DeviceID = MPU9255_ReadReg(MPU6555_WHO_AM_I);
  if(DeviceID != MPU6555_Device_ID)
     return ERROR;

#ifdef _USE_MAG_AK8963
  DeviceID = MPU9255_Mag_ReadReg(AK8963_WIA);
  if(DeviceID != AK8963_Device_ID)
     return ERROR;
#endif

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_getData
**功能 : read IMU data
**輸入 : *dataIMU
**輸出 : None
**使用 : MPU9255_getData(dataIMU);
**====================================================================================================*/
/*====================================================================================================*/
void MPU9255_getData( int16_t *dataIMU )
{
  uint8_t tmpRead[22] = {0};

#ifdef _USE_MAG_AK8963
  MPU9255_ReadRegs(MPU6555_ACCEL_XOUT_H, tmpRead, 22);
#else
  MPU9255_ReadRegs(MPU6555_ACCEL_XOUT_H, tmpRead, 14);
#endif

  dataIMU[0] = (Byte16(int16_t, tmpRead[6],  tmpRead[7]));    // Temp
  dataIMU[1] = (Byte16(int16_t, tmpRead[0],  tmpRead[1]));    // Acc.X
  dataIMU[2] = (Byte16(int16_t, tmpRead[2],  tmpRead[3]));    // Acc.Y
  dataIMU[3] = (Byte16(int16_t, tmpRead[4],  tmpRead[5]));    // Acc.Z
  dataIMU[4] = (Byte16(int16_t, tmpRead[8],  tmpRead[9]));    // Gyr.X
  dataIMU[5] = (Byte16(int16_t, tmpRead[10], tmpRead[11]));   // Gyr.Y
  dataIMU[6] = (Byte16(int16_t, tmpRead[12], tmpRead[13]));   // Gyr.Z
#ifdef _USE_MAG_AK8963
  dataIMU[7] = (Byte16(int16_t, tmpRead[16], tmpRead[15]));   // Mag.X
  dataIMU[8] = (Byte16(int16_t, tmpRead[18], tmpRead[17]));   // Mag.Y
  dataIMU[9] = (Byte16(int16_t, tmpRead[20], tmpRead[19]));   // Mag.Z
#endif  
}
/*==============================================================================================*/
/*==============================================================================================*/
