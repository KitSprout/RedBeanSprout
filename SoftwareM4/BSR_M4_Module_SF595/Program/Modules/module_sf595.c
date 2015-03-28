/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "module_sf595.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define SF595_DI_PIN        GPIO_Pin_1
#define SF595_DI_GPIO_PORT  GPIOA
#define SF595_DI_GPIO_CLK   RCC_AHBPeriph_GPIOA
#define SF595_DI_H          GPIO_SetBits(SF595_DI_GPIO_PORT, SF595_DI_PIN)
#define SF595_DI_L          GPIO_ResetBits(SF595_DI_GPIO_PORT, SF595_DI_PIN)

#define SF595_OE_PIN        GPIO_Pin_2
#define SF595_OE_GPIO_PORT  GPIOA
#define SF595_OE_GPIO_CLK   RCC_AHBPeriph_GPIOA
#define SF595_OE_H          GPIO_SetBits(SF595_OE_GPIO_PORT, SF595_OE_PIN)
#define SF595_OE_L          GPIO_ResetBits(SF595_OE_GPIO_PORT, SF595_OE_PIN)

#define SF595_ST_PIN        GPIO_Pin_3
#define SF595_ST_GPIO_PORT  GPIOA
#define SF595_ST_GPIO_CLK   RCC_AHBPeriph_GPIOA
#define SF595_ST_H          GPIO_SetBits(SF595_ST_GPIO_PORT, SF595_ST_PIN)
#define SF595_ST_L          GPIO_ResetBits(SF595_ST_GPIO_PORT, SF595_ST_PIN)

#define SF595_SH_PIN        GPIO_Pin_4
#define SF595_SH_GPIO_PORT  GPIOA
#define SF595_SH_GPIO_CLK   RCC_AHBPeriph_GPIOA
#define SF595_SH_H          GPIO_SetBits(SF595_SH_GPIO_PORT, SF595_SH_PIN)
#define SF595_SH_L          GPIO_ResetBits(SF595_SH_GPIO_PORT, SF595_SH_PIN)

#define SF595_MR_PIN        GPIO_Pin_5
#define SF595_MR_GPIO_PORT  GPIOA
#define SF595_MR_GPIO_CLK   RCC_AHBPeriph_GPIOA
#define SF595_MR_H          GPIO_SetBits(SF595_MR_GPIO_PORT, SF595_MR_PIN)
#define SF595_MR_L          GPIO_ResetBits(SF595_MR_GPIO_PORT, SF595_MR_PIN)
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SF595_Config
**功能 : 74HC595 Config
**輸入 : None
**輸出 : None
**使用 : SF595_Config();
**====================================================================================================*/
/*====================================================================================================*/
void SF595_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  RCC_AHBPeriphClockCmd(SF595_DI_GPIO_CLK, ENABLE);
  RCC_AHBPeriphClockCmd(SF595_OE_GPIO_CLK, ENABLE);
  RCC_AHBPeriphClockCmd(SF595_ST_GPIO_CLK, ENABLE);
  RCC_AHBPeriphClockCmd(SF595_SH_GPIO_CLK, ENABLE);
  RCC_AHBPeriphClockCmd(SF595_MR_GPIO_CLK, ENABLE);

  GPIO_InitStruct.GPIO_Pin = SF595_DI_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(SF595_DI_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = SF595_OE_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(SF595_OE_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = SF595_ST_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(SF595_ST_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = SF595_SH_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(SF595_SH_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = SF595_MR_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(SF595_MR_GPIO_PORT, &GPIO_InitStruct);

  SF595_DI_L;
  SF595_OE_L;
  SF595_ST_L;
  SF595_SH_L;
  SF595_MR_H;

  SF595_Reset();
  SF595_Cmd(ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SF595_Cmd
**功能 : 74HC595 Enable / Disable
**輸入 : None
**輸出 : None
**使用 : SF595_Cmd(ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void SF595_Cmd( FunctionalState NewState )
{
  if(NewState == ENABLE)
    SF595_OE_L;   // active LOW
  else
    SF595_OE_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SF595_Reset
**功能 : Reset 74HC595
**輸入 : None
**輸出 : None
**使用 : SF595_Reset();
**====================================================================================================*/
/*====================================================================================================*/
void SF595_Reset( void )
{
  SF595_MR_L;
  Delay_1ms(1);
  SF595_MR_H;
  Delay_1ms(1);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SF595_Shift
**功能 : Shift bit
**輸入 : SendData
**輸出 : None
**使用 : SF595_Shift(1);
**====================================================================================================*/
/*====================================================================================================*/
void SF595_Shift( uint8_t SendData )
{
  SF595_SH_L;
  SF595_ST_L;
  if(SendData & 0x01)
    SF595_DI_H;
  else
    SF595_DI_L;
  SF595_SH_H;
  SF595_ST_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SF595_SendByte
**功能 : Shift 8 bits
**輸入 : SendData
**輸出 : None
**使用 : SF595_SendByte(SendData);
**====================================================================================================*/
/*====================================================================================================*/
void SF595_SendByte( uint8_t SendData )
{
  uint8_t i = 0;

  for(i = 0; i < 8; i++) {
    SF595_SH_L;
    SF595_ST_L;
    if(SendData & (0x80 >> i))
      SF595_DI_H;
    else
      SF595_DI_L;
    SF595_SH_H;
    SF595_ST_H;
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
