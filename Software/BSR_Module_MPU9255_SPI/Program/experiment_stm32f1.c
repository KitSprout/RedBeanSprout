/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "experiment_stm32f1.h"
#include "module_mpu9255.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
void IMU_Init( void )
{
  MPU_InitTypeDef MPU_InitStruct;

  MPU9255_Config();
  Delay_10ms(1);

  MPU_InitStruct.MPU_Gyr_FullScale     = MPU_GyrFS_2000dps;
  MPU_InitStruct.MPU_Gyr_LowPassFilter = MPU_GyrLPS_41Hz;
  MPU_InitStruct.MPU_Acc_FullScale     = MPU_AccFS_4g;
  MPU_InitStruct.MPU_Acc_LowPassFilter = MPU_AccLPS_42Hz;
  MPU9255_Init(&MPU_InitStruct);
}

int main( void )
{
  GPIO_Config();

  IMU_Init();

  while(1) {
    LED_R_Toggle;
    LED_G_Toggle;
    LED_B_Toggle;
    Delay_10ms(5);
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
