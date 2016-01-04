/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"
#include "drivers\stm32f1_usb.h"

#include "experiment_stm32f1.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define GPIO_A_PINs       GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_15
#define GPIO_A_GPIO_PORT  GPIOA
#define GPIO_A_Set()      HAL_GPIO_WritePin(GPIO_A_GPIO_PORT, GPIO_A_PINs, GPIO_PIN_SET)
#define GPIO_A_Reset()    HAL_GPIO_WritePin(GPIO_A_GPIO_PORT, GPIO_A_PINs, GPIO_PIN_RESET)
#define GPIO_A_Toggle()   HAL_GPIO_TogglePin(GPIO_A_GPIO_PORT, GPIO_A_PINs)

#define GPIO_B_PINs       GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
#define GPIO_B_GPIO_PORT  GPIOB
#define GPIO_B_Set()      HAL_GPIO_WritePin(GPIO_B_GPIO_PORT, GPIO_B_PINs, GPIO_PIN_SET)
#define GPIO_B_Reset()    HAL_GPIO_WritePin(GPIO_B_GPIO_PORT, GPIO_B_PINs, GPIO_PIN_RESET)
#define GPIO_B_Toggle()   HAL_GPIO_TogglePin(GPIO_B_GPIO_PORT, GPIO_B_PINs)

void GPIO_EX_Set( void )    { GPIO_A_Set();     GPIO_B_Set();    }
void GPIO_EX_Reset( void )  { GPIO_A_Reset();   GPIO_B_Reset();  }
void GPIO_EX_Toggle( void ) { GPIO_A_Toggle();  GPIO_B_Toggle(); }

void GPIO_EX_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  HAL_Init();
  GPIO_Config();
  GPIO_EX_Config();
  USB_VCP_Init();
}

int main( void )
{
  static uint8_t i = 32;

  System_Init();

  USB_VCP_SendStr("Hello World!!\r\n");

  while(1) {

    LED_R_Toggle();
    LED_G_Toggle();
    LED_B_Toggle();
    GPIO_EX_Toggle();
    delay_ms(500);
 
    while(KEY_WU_Read()) {
      LED_G_Toggle();
      USB_VCP_SendByte(i++);
      if(i == 127) {
        USB_VCP_SendByte('\r');
        delay_ms(1);
        USB_VCP_SendByte('\n');
        i = 32;
      }
      delay_ms(100);
    }
    while(KEY_BO_Read()) {
      LED_R_Toggle();
      LED_G_Toggle();
      LED_B_Toggle();
      GPIO_EX_Reset();
      delay_ms(50);
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_EX_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk ******************************************************************/
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* GPIO Pin ******************************************************************/
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Pin   = GPIO_A_PINs;
  HAL_GPIO_Init(GPIO_A_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = GPIO_B_PINs;
  HAL_GPIO_Init(GPIO_B_GPIO_PORT, &GPIO_InitStruct);

  /* GPIO Pin ******************************************************************/
  GPIO_EX_Set();
}
/*====================================================================================================*/
/*====================================================================================================*/
