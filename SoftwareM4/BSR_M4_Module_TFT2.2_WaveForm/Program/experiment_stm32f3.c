/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "experiment_stm32f3.h"
#include "app_waveForm.h"
#include "module_ili9341.h"
#include "algorithm_string.h"
#include "algorithm_mathUnit.h"
/*====================================================================================================*/
/*====================================================================================================*/
WaveForm_Struct WaveForm;

void WaveForm_Init( void )
{
	WaveForm.Channel = 3;
	WaveForm.WindowColor = WHITE;
	WaveForm.BackColor = BLACK;
	WaveForm.Data[0] = 0;
	WaveForm.Data[1] = 0;
  WaveForm.Data[2] = 0;
	WaveForm.Scale[0] = 100;
	WaveForm.Scale[1] = 100;
  WaveForm.Scale[2] = 100;
	WaveForm.PointColor[0] = RED;
	WaveForm.PointColor[1] = GREEN;
  WaveForm.PointColor[2] = BLUE;

  LCD_Clear(BLACK);
}

void WaveForm_DEMO( void )
{
  static int32_t theta = 0;

  theta++;
  if(theta == 360) theta = 0;
  WaveForm.Data[0] = arm_sin_f32(toRad(theta))*5000;
  WaveForm.Data[1] = arm_sin_f32(toRad(theta+120))*5000;
  WaveForm.Data[2] = arm_sin_f32(toRad(theta+240))*5000;

  WaveFormPrint(&WaveForm, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  GPIO_Config();
  ILI9341_Config();
  ILI9341_Init();

  LCD_TestColoBar();

  WaveForm_Init();

  while(1) {
    LED_R_Toggle;
    LED_G_Toggle;
    LED_B_Toggle;
    WaveForm_DEMO();
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC, ENABLE);

  /* LED_B PC13 */  /* LED_G PC14 */  /* LED_R PC15 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY_WU PA0 */  /* KEY_BO PB2 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  LED_R_Set;
  LED_G_Set;
  LED_B_Set;
}
/*====================================================================================================*/
/*====================================================================================================*/
