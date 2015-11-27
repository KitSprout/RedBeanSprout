/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "module_sf138.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define SF138_A0_PIN        GPIO_Pin_1
#define SF138_A0_GPIO_PORT  GPIOA
#define SF138_A0_GPIO_CLK   RCC_APB2Periph_GPIOA
#define SF138_A0_H          GPIO_SetBits(SF138_A0_GPIO_PORT, SF138_A0_PIN)
#define SF138_A0_L          GPIO_ResetBits(SF138_A0_GPIO_PORT, SF138_A0_PIN)

#define SF138_A1_PIN        GPIO_Pin_2
#define SF138_A1_GPIO_PORT  GPIOA
#define SF138_A1_GPIO_CLK   RCC_APB2Periph_GPIOA
#define SF138_A1_H          GPIO_SetBits(SF138_A1_GPIO_PORT, SF138_A1_PIN)
#define SF138_A1_L          GPIO_ResetBits(SF138_A1_GPIO_PORT, SF138_A1_PIN)

#define SF138_A2_PIN        GPIO_Pin_3
#define SF138_A2_GPIO_PORT  GPIOA
#define SF138_A2_GPIO_CLK   RCC_APB2Periph_GPIOA
#define SF138_A2_H          GPIO_SetBits(SF138_A2_GPIO_PORT, SF138_A2_PIN)
#define SF138_A2_L          GPIO_ResetBits(SF138_A2_GPIO_PORT, SF138_A2_PIN)

#define SF138_EN_PIN        GPIO_Pin_4
#define SF138_EN_GPIO_PORT  GPIOA
#define SF138_EN_GPIO_CLK   RCC_APB2Periph_GPIOA
#define SF138_EN_H          GPIO_SetBits(SF138_EN_GPIO_PORT, SF138_EN_PIN)
#define SF138_EN_L          GPIO_ResetBits(SF138_EN_GPIO_PORT, SF138_EN_PIN)
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SF138_Config
**功能 : 74HC138 Config
**輸入 : None
**輸出 : None
**使用 : SF138_Config();
**====================================================================================================*/
/*====================================================================================================*/
void SF138_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  RCC_APB2PeriphClockCmd(SF138_A0_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(SF138_A1_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(SF138_A2_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(SF138_EN_GPIO_CLK, ENABLE);

  GPIO_InitStruct.GPIO_Pin = SF138_A0_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SF138_A0_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = SF138_A1_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SF138_A1_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = SF138_A2_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SF138_A2_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = SF138_EN_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SF138_EN_GPIO_PORT, &GPIO_InitStruct);

  SF138_A0_L;
  SF138_A1_L;
  SF138_A2_L;

  SF138_Cmd(ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SF138_Cmd
**功能 : 74HC138 Enable / Disable
**輸入 : None
**輸出 : None
**使用 : SF138_Cmd(ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void SF138_Cmd( FunctionalState NewState )
{
  if(NewState == ENABLE)
    SF138_EN_H;
  else
    SF138_EN_L;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SF138_WriteData
**功能 : 74HC138 Write Data
**輸入 : writeData
**輸出 : None
**使用 : SF138_WriteData(writeData);
**====================================================================================================*/
/*====================================================================================================*/
void SF138_WriteData( uint8_t writeData )
{
  if((writeData & 0x01) == 0x01)  SF138_A0_H;
  else                            SF138_A0_L;
  if((writeData & 0x02) == 0x02)  SF138_A1_H;
  else                            SF138_A1_L;
  if((writeData & 0x04) == 0x04)  SF138_A2_H;
  else                            SF138_A2_L;
}
/*====================================================================================================*/
/*====================================================================================================*/
