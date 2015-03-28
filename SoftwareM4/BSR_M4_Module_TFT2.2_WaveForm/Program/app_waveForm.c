/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f3_system.h"
#include "module_ili9341.h"
#include "app_waveForm.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormInit( WaveForm_Struct *WaveForm )
{
  WaveForm->Channel = 3;
  WaveForm->WindowColor = WHITE;
  WaveForm->BackColor = BLACK;
  WaveForm->Data[0] = 0;
  WaveForm->Data[1] = 0;
  WaveForm->Data[2] = 0;
  WaveForm->Scale[0] = 100;
  WaveForm->Scale[1] = 100;
  WaveForm->Scale[2] = 100;
  WaveForm->PointColor[0] = RED;
  WaveForm->PointColor[1] = GREEN;
  WaveForm->PointColor[2] = BLUE;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormPrint( WaveForm_Struct *WaveForm, uint8_t display )
{
  int16_t i, j;
  int16_t TempY[WaveChannelMax] = {0};
  int16_t CoordiY[WaveChannelMax] = {0};

  static uint16_t WavePic[WaveChannelMax][WaveFormW] = {0};

  /* 更新顯示座標 */
  for(i = 0; i < WaveForm->Channel; i++) {
    for(j = 0; j < WaveFormW - 1; j++)
      WavePic[i][j] = WavePic[i][j+1];
    TempY[i] = (int16_t)((float)WaveForm->Data[i] / WaveForm->Scale[i] + 0.5f);
    CoordiY[i] = WaveFormH - TempY[i];
    if((CoordiY[i] > 0) && (CoordiY[i] < WaveForm2H))
      WavePic[i][WaveFormW-1] = CoordiY[i];
  }
  if(display == ENABLE) {
    /* 顯示 */
    for(i = 0; i < WaveFormW - 1; i++) {
      /* 清除上筆數據 */
      for(j = 0; j < WaveForm->Channel; j++)
        LCD_DrawPixel(WaveWindowX+i+1, WaveWindowY+WavePic[j][i], WaveForm->BackColor);
//      /* 畫輔助線 */
//      if((i % 10) < 3) {
//        for(j = 0; j <= WaveFormH; j += (WaveFormH / 10)) {
//          LCD_DrawPixel(WaveWindowX+i, WaveWindowY+WaveFormH+j, WaveForm->WindowColor);
//          LCD_DrawPixel(WaveWindowX+i, WaveWindowY+WaveFormH-j, WaveForm->WindowColor);
//        }
//      }
      /* 畫中線 */
      LCD_DrawPixel(WaveWindowX+i, WaveWindowY+WaveFormH, WaveForm->WindowColor);
      /* 更新顯示新數據 */
      for(j = 0; j < WaveForm->Channel; j++)
        LCD_DrawPixel(WaveWindowX+i, WaveWindowY+WavePic[j][i], WaveForm->PointColor[j]);
    }
    for(j = 0; j < WaveForm->Channel; j++)
      LCD_DrawPixel(WaveWindowX, WaveWindowY+WavePic[j][0], WaveForm->BackColor);
    /* 畫邊框 */
    LCD_DrawLineX(WaveWindowX,           WaveWindowY,            WaveFormW,	 WaveForm->WindowColor);
    LCD_DrawLineX(WaveWindowX,           WaveWindowY+WaveForm2H, WaveFormW,  WaveForm->WindowColor);
    LCD_DrawLineY(WaveWindowX,           WaveWindowY,            WaveForm2H, WaveForm->WindowColor);
    LCD_DrawLineY(WaveWindowX+WaveFormW, WaveWindowY,            WaveForm2H, WaveForm->WindowColor);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
