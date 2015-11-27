/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "experiment_stm32f1.h"
#include "module_mpu9255.h"
#include "module_rs232.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
uint8_t imu_init( void )
{
  uint8_t status = ERROR;

  MPU_InitTypeDef MPU_InitStruct;

  MPU9255_Config();
  Delay_100ms(1);

  MPU_InitStruct.MPU_Gyr_FullScale     = MPU_GyrFS_2000dps;
  MPU_InitStruct.MPU_Gyr_LowPassFilter = MPU_GyrLPS_41Hz;
  MPU_InitStruct.MPU_Acc_FullScale     = MPU_AccFS_4g;
  MPU_InitStruct.MPU_Acc_LowPassFilter = MPU_AccLPS_42Hz;
  MPU_InitStruct.MPU_Mag_FullScale     = MPU_MagFS_16b;
  status = MPU9255_Init(&MPU_InitStruct);
  if(status != SUCCESS)
    return ERROR;

  return SUCCESS;
}

void Serial_sendDataMATLAB( int16_t *sendData, uint8_t dataNum )
{
  uint8_t tmpData[16] = {0};
  uint8_t *ptrData = tmpData;
  uint8_t dataBytes = dataNum << 1;
  uint8_t dataLens = dataBytes + 4;
  uint8_t count = 0;
  uint16_t tmpSum = 0;

  tmpData[0] = 'S';
  while(count < dataBytes) {
    tmpData[count+1] = Byte8H(sendData[count >> 1]);
    tmpData[count+2] = Byte8L(sendData[count >> 1]);
    count = count + 2;
  }
  for(uint8_t i = 0; i < dataBytes; i++)
    tmpSum += tmpData[i+1];
  tmpData[dataLens - 3] = (uint8_t)(tmpSum & 0x00FF);
  tmpData[dataLens - 2] = '\r';
  tmpData[dataLens - 1] = '\n';

  do {
    RS232_SendByte(*ptrData++);
  } while(--dataLens);
}

int main( void )
{
  GPIO_Config();
  RS232_Config();
  while(imu_init() != SUCCESS) {
    LED_G_Toggle;
    Delay_100ms(1);
  }
  Delay_100ms(1);

  if(SysTick_Config(SystemCoreClock / 100)) // 100Hz
    while(1);

  while(1) {
    LED_B_Toggle;
    Delay_100ms(1);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Clk Init *************************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
  
  /* PC13 LED_B */	/* PC14 LED_G */	/* PC15 LED_R */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY_WU PA0 */	/* KEY_BO PB2 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  LED_R_Set;
  LED_G_Set;
  LED_B_Set;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
