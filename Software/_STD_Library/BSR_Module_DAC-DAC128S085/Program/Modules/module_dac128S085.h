/* #include "module_dac128S085.h" */

#ifndef __MODULE_DAC128S085_H
#define __MODULE_DAC128S085_H

#include "stm32f10x.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define DAC_CH1 ((uint16_t)0x0000)
#define DAC_CH2 ((uint16_t)0x1000)
#define DAC_CH3 ((uint16_t)0x2000)
#define DAC_CH4 ((uint16_t)0x3000)
#define DAC_CH5 ((uint16_t)0x4000)
#define DAC_CH6 ((uint16_t)0x5000)
#define DAC_CH7 ((uint16_t)0x6000)
#define DAC_CH8 ((uint16_t)0x7000)

#define DAC_MODE_WRM  ((uint16_t)0x8000)
#define DAC_MODE_WTM  ((uint16_t)0x9000)

#define DAC_SpCMD_UpdateSel ((uint16_t)0xA000)
#define DAC_SpCMD_WriteChA  ((uint16_t)0xB000)
#define DAC_SpCMD_Broadcast ((uint16_t)0xC000)
/*====================================================================================================*/
/*====================================================================================================*/
void DAC128S085_Config( void );
void DAC128S085_Init( void );
void DAC128S085_ChangeMode( uint16_t OpMode );
void DAC128S085_BroadcastData( uint16_t WriteData );
void DAC128S085_WriteDACData( uint16_t DAC_Ch, uint16_t WriteData );
void DAC128S085_SetInitVal( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
