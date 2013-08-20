/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_adc.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
vu16 ADC_DMA_Buf[ADC_Sample][ADC_Channel] = {0};
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : ADC_Average
**功能 : 將 ADC 轉換後的資料取平均
**輸入 : ADC_AveTr
**輸出 : None
**使用 : ADC_Average(ADC_AveTr);
**=====================================================================================================*/
/*=====================================================================================================*/
void ADC_Config( void )
{
	DMA_InitTypeDef DMA_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

	/* ADC_1 PA4 */	/* ADC_2 PA5 */	/* ADC_3 PA6 */	/* ADC_4 PA7 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* ADC DMA Init *************************************************************/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DR_ADDRESS;                    // Peripheral address
  DMA_InitStruct.DMA_MemoryBaseAddr = (u32)&ADC_DMA_Buf;                      // DMA內存地址
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                             // 內存作為數據傳輸的目的地
	DMA_InitStruct.DMA_BufferSize = ADC_Sample*ADC_Channel;                     // DMA通道的DMA緩存的大小
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;               // 外設地址寄存器不變
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                        // 內存地址寄存器遞增
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    // 數據寬度為16位
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;            // 數據寬度為16位
  DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;                                // 循環模式開啟，Buffer寫滿後，自動回到初始地址開始傳輸
  DMA_InitStruct.DMA_Priority = DMA_Priority_High;                            // DMA通道x擁有高優先級
  DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;                                   // DMA通道x沒有設置為內存到內存傳輸
  DMA_Init(DMA1_Channel1, &DMA_InitStruct);
  DMA_Cmd(DMA1_Channel1, ENABLE);

  /* ADC Init *****************************************************************/
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;                             // ADC1 和 ADC2 工作在獨立模式 
  ADC_InitStruct.ADC_ScanConvMode = ENABLE;                                   // 掃描模式 
  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                             // 連續轉換模式 
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;            // 外部觸發關閉
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;                         // ADC數據右對齊
  ADC_InitStruct.ADC_NbrOfChannel = ADC_Channel;                              // 轉換ADC通道數目
  ADC_Init(ADC1, &ADC_InitStruct);

  /* ADC Regular Config *******************************************************/
	// 設置指定ADC的規則組通道，設置它們的轉化順序和采樣時間
	// ADC1, ADC通道x, 規則采樣順序值為y, 采樣時間為239.5週期
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_55Cycles5);

  ADC_DMACmd(ADC1, ENABLE);
  ADC_Cmd(ADC1, ENABLE);
  ADC_ResetCalibration(ADC1);
  while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : ADC_Average
**功能 : 將 ADC 轉換後的資料取平均
**輸入 : ADC_AveTr
**輸出 : None
**使用 : ADC_Average(ADC_AveTr);
**=====================================================================================================*/
/*=====================================================================================================*/
void ADC_Average( u16* pADC_AveTr )
{
  u8 i, j;
  u32 ADC_DMA_Tmp[ADC_Channel] = {0};

  for(i=0; i<ADC_Channel; i++) {
    for(j=0; j<ADC_Sample; j++)
      ADC_DMA_Tmp[i] += ADC_DMA_Buf[j][i];
    pADC_AveTr[i] = (u16)(ADC_DMA_Tmp[i] / ADC_Sample);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
