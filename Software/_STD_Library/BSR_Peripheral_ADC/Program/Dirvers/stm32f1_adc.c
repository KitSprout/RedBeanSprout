/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_adc.h"
/*====================================================================================================*/
/*====================================================================================================*/
static volatile uint16_t ADC_DMA_Buf[ADC_Sample][ADC_Channel] = {0};
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_Config
**功能 : ADC 配置
**輸入 : None
**輸出 : None
**使用 : ADC_Config();
**====================================================================================================*/
/*====================================================================================================*/
void ADC_Config( void )
{
  DMA_InitTypeDef DMA_InitStruct;
  ADC_InitTypeDef ADC_InitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;

  /* ADC Clk Init *************************************************************/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

  /* ADC1_4 PA4 */	/* ADC1_5 PA5 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* ADC1 DMA Stream0 Channel_0 Init ******************************************/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DR_ADDRESS;                    // Peripheral address
  DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&ADC_DMA_Buf;                 // Memory address
  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                             // 內存作為數據傳輸的目的地
  DMA_InitStruct.DMA_BufferSize = ADC_Channel*ADC_Sample;                     // Memory Buffer Size
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;               // Peripheral address 遞增 Disable
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                        // Memory address 遞增 Enable
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    // Peripheral Data Size 16bit
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;            // Memory Data Size 16bit
  DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;                                // 循環模式 Enable
  DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;                          // ADC DMA通道 普通優先級
  DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;                                   // DMA通道x沒有設置為內存到內存傳輸
  DMA_Init(DMA1_Channel1, &DMA_InitStruct);
  DMA_Cmd(DMA1_Channel1, ENABLE);

  /* ADC Init *****************************************************************/
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;                             // ADC1 和 ADC2 工作在獨立模式 
  ADC_InitStruct.ADC_ScanConvMode = ENABLE;                                   // 掃描模式 
  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                             // 連續轉換模式 
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;            // 外部觸發 Disable
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;                         // ADC數據右對齊
  ADC_InitStruct.ADC_NbrOfChannel = ADC_Channel;                              // 轉換ADC通道數目
  ADC_Init(ADC1, &ADC_InitStruct);

  /* ADC Regular Config *******************************************************/
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_28Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_28Cycles5);

  ADC_DMACmd(ADC1, ENABLE);
  ADC_Cmd(ADC1, ENABLE);
//  ADC_ResetCalibration(ADC1);
//  while(ADC_GetResetCalibrationStatus(ADC1));
//  ADC_StartCalibration(ADC1);
//  while(ADC_GetCalibrationStatus(ADC1));
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_Average
**功能 : 將 ADC 轉換後的資料取平均
**輸入 : *pADC_AveTr, AveSample
**輸出 : None
**使用 : ADC_Average(ADC_AveData, 64);
**====================================================================================================*/
/*====================================================================================================*/
void ADC_Average( uint16_t *pADC_AveTr, uint8_t AveSample )
{
  uint8_t i = 0, j = 0;
  uint32_t ADC_DMA_Temp = 0;

  for(i = 0; i < ADC_Channel; i++) {
    for(j = 0; j < AveSample; j++)
      ADC_DMA_Temp += ADC_DMA_Buf[ADC_Sample-1-j][i];
    pADC_AveTr[i] = (uint16_t)(ADC_DMA_Temp / AveSample);
    ADC_DMA_Temp = 0;
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
