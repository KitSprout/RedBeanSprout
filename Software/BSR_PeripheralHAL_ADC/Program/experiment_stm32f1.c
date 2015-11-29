/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"
#include "modules\module_serial.h"

#include "experiment_stm32f1.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define BUFFER_SIZE 1
__IO uint16_t ADC_ConvVal[BUFFER_SIZE];
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  HAL_Init();
  GPIO_Config();
  Serial_Config();
  ADC_Config();

  Delay_100ms(1);
  printf("\r\nHello World!\r\n\r\n");
}

int main( void )
{
  System_Init();

  while(1) {
    LED_G_Toggle();
    Delay_100ms(1);
    printf("ADC = %d\r\n", ADC_ConvVal[0]);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void ADC_Config( void )
{
  ADC_HandleTypeDef ADC_InitStruct;
  ADC_ChannelConfTypeDef ADC_ChannelConfStruct;

  GPIO_InitTypeDef GPIO_InitStruct;
  DMA_HandleTypeDef DMA_HandleStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_ADC1_CLK_ENABLE();

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  __HAL_RCC_DMA1_CLK_ENABLE();

  ADC_InitStruct.Instance                   = ADC1;
  ADC_InitStruct.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  ADC_InitStruct.Init.ScanConvMode          = ADC_SCAN_ENABLE;
  ADC_InitStruct.Init.ContinuousConvMode    = ENABLE;
  ADC_InitStruct.Init.NbrOfConversion       = 1;
  ADC_InitStruct.Init.DiscontinuousConvMode = ENABLE;
  ADC_InitStruct.Init.NbrOfDiscConversion   = 1;
  ADC_InitStruct.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
  HAL_ADC_Init(&ADC_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  DMA_HandleStruct.Instance                 = DMA1_Channel1;
  DMA_HandleStruct.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  DMA_HandleStruct.Init.PeriphInc           = DMA_PINC_DISABLE;
  DMA_HandleStruct.Init.MemInc              = DMA_MINC_ENABLE;
  DMA_HandleStruct.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  DMA_HandleStruct.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
  DMA_HandleStruct.Init.Mode                = DMA_CIRCULAR;
  DMA_HandleStruct.Init.Priority            = DMA_PRIORITY_HIGH;
  HAL_DMA_DeInit(&DMA_HandleStruct);
  HAL_DMA_Init(&DMA_HandleStruct);
  __HAL_LINKDMA(&ADC_InitStruct, DMA_Handle, DMA_HandleStruct);

  ADC_ChannelConfStruct.Channel      = ADC_CHANNEL_4;
  ADC_ChannelConfStruct.Rank         = ADC_REGULAR_RANK_1;
  ADC_ChannelConfStruct.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
  HAL_ADC_ConfigChannel(&ADC_InitStruct, &ADC_ChannelConfStruct);

  HAL_ADCEx_Calibration_Start(&ADC_InitStruct);
  HAL_ADC_Start_DMA(&ADC_InitStruct, (uint32_t*)ADC_ConvVal, BUFFER_SIZE);
  HAL_ADC_Start(&ADC_InitStruct);
}
/*====================================================================================================*/
/*====================================================================================================*/
