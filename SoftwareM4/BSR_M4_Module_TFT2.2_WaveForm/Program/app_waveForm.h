/* #include "app_waveForm.h" */

#ifndef __APP_WAVEFORM_H
#define __APP_WAVEFORM_H

#include "stm32f30x.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define WaveChannelMax  3
#define WaveWindowX     90
#define WaveWindowY     60
#define WaveFormW       140
#define WaveFormH       60
#define WaveForm2H      120
/*=====================================================================================================*/
/*=====================================================================================================*/
typedef struct {
  uint8_t  Channel;
  int16_t  Data[WaveChannelMax];
  uint16_t Scale[WaveChannelMax];
  uint32_t PointColor[WaveChannelMax];
  uint32_t WindowColor;
  uint32_t BackColor;
} WaveForm_Struct;
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormInit( WaveForm_Struct *WaveForm );
void WaveFormPrint( WaveForm_Struct *WaveForm, uint8_t display );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
