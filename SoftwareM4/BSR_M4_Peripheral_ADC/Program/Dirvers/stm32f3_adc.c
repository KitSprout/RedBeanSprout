/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "stm32f3_adc.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define ADCx ADC2
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
  volatile uint32_t calibration_value = 0;

  ADC_InitTypeDef ADC_InitStruct;
  ADC_CommonInitTypeDef ADC_CommonInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;

  RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div1);

  /* ADC Clk Init *************************************************************/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12 | RCC_AHBPeriph_GPIOA, ENABLE);

  /* ADC2_3 PA6 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* ADC Config ***************************************************************/
  ADC_StructInit(&ADC_InitStruct);
  ADC_VoltageRegulatorCmd(ADCx, ENABLE);
  Delay_10us(1);
  ADC_SelectCalibrationMode(ADCx, ADC_CalibrationMode_Single);
  ADC_StartCalibration(ADCx);
  while(ADC_GetCalibrationStatus(ADCx) != RESET );
  calibration_value = ADC_GetCalibrationValue(ADCx);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;                                                                    
  ADC_CommonInitStruct.ADC_Clock = ADC_Clock_AsynClkMode;                    
  ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;             
  ADC_CommonInitStruct.ADC_DMAMode = ADC_DMAMode_OneShot;                  
  ADC_CommonInitStruct.ADC_TwoSamplingDelay = 0;
  ADC_CommonInit(ADCx, &ADC_CommonInitStruct);

  /* ADC Init *****************************************************************/
  ADC_InitStruct.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
  ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b; 
  ADC_InitStruct.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;         
  ADC_InitStruct.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_OverrunMode = ADC_OverrunMode_Disable;   
  ADC_InitStruct.ADC_AutoInjMode = ADC_AutoInjec_Disable;  
  ADC_InitStruct.ADC_NbrOfRegChannel = 1;
  ADC_Init(ADCx, &ADC_InitStruct);

  /* ADC Regular Config *******************************************************/
  ADC_RegularChannelConfig(ADCx, ADC_Channel_3, 1, ADC_SampleTime_7Cycles5);

  ADC_Cmd(ADCx, ENABLE);
  while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_RDY));
  ADC_StartConversion(ADCx);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_ReadData
**功能 : 讀取 ADC 數值
**輸入 : None
**輸出 : ADC_Data
**使用 : ADC_Data = ADC_ReadData();
**====================================================================================================*/
/*====================================================================================================*/
uint16_t ADC_ReadData( void )
{
  while(ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET);
  return ADC_GetConversionValue(ADCx);
}
/*====================================================================================================*/
/*====================================================================================================*/
