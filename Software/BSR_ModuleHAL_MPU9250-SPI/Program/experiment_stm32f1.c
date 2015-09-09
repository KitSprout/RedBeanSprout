/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"
#include "modules\module_rs232.h"
#include "modules\module_mpu9250.h"

#include "experiment_stm32f1.h"
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  MPU_InitTypeDef MPU_InitStruct;

  HAL_Init();
  GPIO_Config();
  RS232_Config();
  MPU9250_Config();

  Delay_100ms(1);

  LED_R_Reset;
  printf("\r\nHello World!\r\n\r\n");

  MPU_InitStruct.MPU_Gyr_FullScale     = MPU_GyrFS_2000dps;
  MPU_InitStruct.MPU_Gyr_LowPassFilter = MPU_GyrLPS_41Hz;
  MPU_InitStruct.MPU_Acc_FullScale     = MPU_AccFS_4g;
  MPU_InitStruct.MPU_Acc_LowPassFilter = MPU_AccLPS_42Hz;
  MPU_InitStruct.MPU_Mag_FullScale     = MPU_MagFS_16b;
  while(MPU9250_Init(&MPU_InitStruct) != SUCCESS) {
    LED_G_Toggle;
    Delay_100ms(1);
  }
  Delay_100ms(1);
}

int main( void )
{
  int16_t IMU_Buf[10] = {0};

  System_Init();

  while(1) {
    LED_G_Toggle;
    LED_B_Toggle;
    Delay_100ms(5);

    MPU9250_getData(IMU_Buf);
    printf("Acc.X = %d\tAcc.Y = %d\tAcc.Z = %d\tGyr.X = %d\tGyr.Y = %d\tGyr.Z = %d\tMag.X = %d\tMag.Y = %d\tMag.Z = %d\tTemp = %d\r\n", IMU_Buf[1], IMU_Buf[2], IMU_Buf[3], IMU_Buf[4], IMU_Buf[5], IMU_Buf[6], IMU_Buf[7], IMU_Buf[8], IMU_Buf[9], IMU_Buf[0]);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_AFIO_REMAP_SWJ_NOJTAG();

  /* LED_B PC13 */  /* LED_G PC14 */  /* LED_R PC15 */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin   = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY_WU PA0 */  /* KEY_BO PB2 */
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  
  GPIO_InitStruct.Pin   = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = GPIO_PIN_2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Init
  LED_R_Set;
  LED_G_Set;
  LED_B_Set;
}
/*====================================================================================================*/
/*====================================================================================================*/
