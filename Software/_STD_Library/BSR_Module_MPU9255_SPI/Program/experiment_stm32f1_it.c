/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "experiment_stm32f1.h"
#include "module_rs232.h"
#include "module_mpu9255.h"
/*====================================================================================================*/
/*====================================================================================================*/
void NMI_Handler( void ) { while(1); }
void HardFault_Handler( void ) { while(1); }
void MemManage_Handler( void ) { while(1); }
void BusFault_Handler( void ) { while(1); }
void UsageFault_Handler( void ) { while(1); }
void SVC_Handler( void ) { while(1); }
void DebugMon_Handler( void ) { while(1); }
void PendSV_Handler( void ) { while(1); }
/*====================================================================================================*/
/*====================================================================================================*/

void Serial_sendDataMATLAB( int16_t *sendData, uint8_t dataLens );

#define Sxx 0.121956687799872f
#define Sxy -0.0009120812247561210f
#define Sxz -0.001026088893085f
#define Syx 0.0009742633571104469f
#define Syy 0.122326485587814f
#define Syz 0.0005673922448578565f
#define Szx 0.002720699615581f
#define Szy 0.002498151546225f
#define Szz 0.121355342358200f
#define Bx  71
#define By  115
#define Bz  -219

void SysTick_Handler( void )
{
  int16_t IMU_Buf[12] = {0};
  int16_t readData[12] = {0};

  LED_R_Toggle;
  MPU9255_getData(readData);
  readData[1] = readData[1] - Bx;    // Acc.X
  readData[2] = readData[2] - By;    // Acc.Y
  readData[3] = readData[3] - Bz;    // Acc.Z

  IMU_Buf[0] = (int16_t)(readData[1] * Sxx + readData[2] * Sxy + readData[3] * Sxz);  // Acc.X
  IMU_Buf[1] = (int16_t)(readData[1] * Syx + readData[2] * Syy + readData[3] * Syz);  // Acc.Y
  IMU_Buf[2] = (int16_t)(readData[1] * Szx + readData[2] * Szy + readData[3] * Szz);  // Acc.Z
  IMU_Buf[3] = readData[4] * MPU9255G_2000dps;                                        // Gyr.X
  IMU_Buf[4] = readData[5] * MPU9255G_2000dps;                                        // Gyr.Y
  IMU_Buf[5] = readData[6] * MPU9255G_2000dps;                                        // Gyr.Z
  IMU_Buf[6] = readData[7] * MPU9255M_4800uT;                                         // Mag.X
  IMU_Buf[7] = readData[8] * MPU9255M_4800uT;                                         // Mag.Y
  IMU_Buf[8] = readData[9] * MPU9255M_4800uT;                                         // Mag.Z
  IMU_Buf[9] = readData[0] * MPU9255T_85degC;                                         // temp

  Serial_sendDataMATLAB(IMU_Buf, 10);
}
/*====================================================================================================*/
/*====================================================================================================*/
//void SysTick_Handler( void );
//void WWDG_IRQHandler( void );
//void PVD_IRQHandler( void );
//void TAMPER_IRQHandler( void );
//void RTC_IRQHandler( void );
//void FLASH_IRQHandler( void );
//void RCC_IRQHandler( void );
//void EXTI0_IRQHandler( void );
//void EXTI1_IRQHandler( void );
//void EXTI2_IRQHandler( void );
//void EXTI3_IRQHandler( void );
//void EXTI4_IRQHandler( void );
//void DMA1_Channel1_IRQHandler( void );
//void DMA1_Channel2_IRQHandler( void );
//void DMA1_Channel3_IRQHandler( void );
//void DMA1_Channel4_IRQHandler( void );
//void DMA1_Channel5_IRQHandler( void );
//void DMA1_Channel6_IRQHandler( void );
//void DMA1_Channel7_IRQHandler( void );
//void ADC1_2_IRQHandler( void );
//void USB_HP_CAN1_TX_IRQHandler( void );
//void USB_LP_CAN1_RX0_IRQHandler( void );
//void CAN1_RX1_IRQHandler( void );
//void CAN1_SCE_IRQHandler( void );
//void EXTI9_5_IRQHandler( void );
//void TIM1_BRK_IRQHandler( void );
//void TIM1_UP_IRQHandler( void );
//void TIM1_TRG_COM_IRQHandler( void );
//void TIM1_CC_IRQHandler( void );
//void TIM2_IRQHandler( void );
//void TIM3_IRQHandler( void );
//void TIM4_IRQHandler( void );
//void I2C1_EV_IRQHandler( void );
//void I2C1_ER_IRQHandler( void );
//void I2C2_EV_IRQHandler( void );
//void I2C2_ER_IRQHandler( void );
//void SPI1_IRQHandler( void );
//void SPI2_IRQHandler( void );
//void USART1_IRQHandler( void );
//void USART2_IRQHandler( void );
//void USART3_IRQHandler( void );
//void EXTI15_10_IRQHandler( void );
//void RTCAlarm_IRQHandler( void );
//void USBWakeUp_IRQHandler( void );
/*====================================================================================================*/
/*====================================================================================================*/
