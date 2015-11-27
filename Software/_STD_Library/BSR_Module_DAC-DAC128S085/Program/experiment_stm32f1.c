/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "experiment_stm32f1.h"
#include "module_dac128S085.h"

#include <math.h>
/*=====================================================================================================*/
/*=====================================================================================================*/
#define DELAY Delay_100us(1)

void DAC128S085_TestFunction( void )
{
  uint16_t DAC_DATA[8] = {0};

  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]++);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]++);  // 1024 -> 2047
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]++);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]++);  // 2048 -> 3071
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]++);  // 1024 -> 2047
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]++);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]++);  // 3072 -> 4095
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]++);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]--);  // 4096 -> 3071
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]++);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]--);  // 3072 -> 4095
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]++);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH1, DAC_DATA[0]--);  // 3072 -> 4095
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]++);  //    0 -> 1023
    DELAY;
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
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH2, DAC_DATA[1]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]++);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH3, DAC_DATA[2]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]++);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]++);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH4, DAC_DATA[3]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]++);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH5, DAC_DATA[4]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]--);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH6, DAC_DATA[5]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]--);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH7, DAC_DATA[6]--);  //    0 -> 1023
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]--);  //    0 -> 1023
    DELAY;
  }
  for(uint16_t i = 1; i < 1024; i++) {
    DAC128S085_WriteDACData(DAC_CH8, DAC_DATA[7]--);  //    0 -> 1023
    DELAY;
  }
}

int main( void )
{
  GPIO_Config();
  DAC128S085_Config();
  Delay_100ms(1);
  DAC128S085_Init();

  while(1) {
    LED_R = !LED_R;
    LED_G = !LED_G;
    LED_B = !LED_B;
    DAC128S085_TestFunction();
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

  LED_R = 1;
  LED_G = 1;
  LED_B = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
