/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"

#include "experiment_stm32f1.h"
/*====================================================================================================*/
/*====================================================================================================*/
/*
System Clock source            = PLL (HSE)
SYSCLK(Hz)                     = 72000000
HCLK(Hz)                       = 72000000
AHB Prescaler                  = 1
APB1 Prescaler                 = 2
APB2 Prescaler                 = 1
HSE Frequency(Hz)              = 8000000
PLLMUL                         = 9
Flash Latency(WS)              = 2
*/
void HAL_MspInit( void )
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef state = HAL_OK;

  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState            = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue      = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState            = RCC_LSE_OFF;
  RCC_OscInitStruct.HSIState            = RCC_HSI_OFF;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL9;
  state = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(state != HAL_OK)
    while(1) { ; }

  RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  state = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
  if(state != HAL_OK)
    while(1) { ; }
}
/*====================================================================================================*/
/*====================================================================================================*/
