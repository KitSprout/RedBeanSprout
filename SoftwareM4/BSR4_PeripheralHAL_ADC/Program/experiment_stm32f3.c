/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"
#include "drivers\stm32f3_adc.h"
#include "modules\module_serial.h"

#include "experiment_stm32f3.h"
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  HAL_Init();
  GPIO_Config();
  Serial_Config();
  ADC_Config();

  delay_ms(100);
  printf("\fHello World!\r\n\r\n");
}

int main( void )
{
  uint16_t ADC_ConvVal[ADC_BUF_CHENNAL] = {0};

  System_Init();

  while(1) {
    LED_G_Toggle();
    delay_ms(100);
    ADC_getAverage(ADC_ConvVal, 32);
    printf("ADC = %d, %d, %d\r\n", ADC_ConvVal[0], ADC_ConvVal[1], ADC_ConvVal[2]);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
#ifdef USE_FULL_ASSERT
void assert_failed( uint8_t *file, uint32_t line )
{
  printf("[HAL_ERROR] %s on line %d\r\n", file, line);
  while(1) {
    LED_R_Toggle();
    delay_ms(100);
  }
}

void ERROR_FUNC( HAL_StatusTypeDef state, uint8_t *file, uint32_t line )
{
  switch(state) {
    case HAL_OK:      printf("[HAL_OK] %s on line %d\r\n",      file, line);  break;
    case HAL_ERROR:   printf("[HAL_ERROR] %s on line %d\r\n",   file, line);  break;
    case HAL_BUSY:    printf("[HAL_BUSY] %s on line %d\r\n",    file, line);  break;
    case HAL_TIMEOUT: printf("[HAL_TIMEOUT] %s on line %d\r\n", file, line);  break;
  }
  while(1) {
    LED_R_Toggle();
    delay_ms(100);
  }
}
#endif
/*====================================================================================================*/
/*====================================================================================================*/
