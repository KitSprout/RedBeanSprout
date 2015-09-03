/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"

#include "experiment_stm32f1.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  HAL_Init();
  GPIO_Config();
  GPIO_EX_Config();

  while(1) {
    LED_R_Toggle;
    LED_G_Toggle;
    LED_B_Toggle;
    GPIO_A_Toggle;
    GPIO_B_Toggle;
    Delay_100ms(1);
 
    while(KEY_WU_Read) {
      LED_R_Toggle;
      LED_G_Toggle;
      LED_B_Toggle;
      GPIO_A_Toggle;
      GPIO_B_Toggle;
      Delay_100ms(2);
    }
    while(KEY_BO_Read) {
      LED_R_Toggle;
      LED_G_Toggle;
      LED_B_Toggle;
      GPIO_A_Toggle;
      GPIO_B_Toggle;
      Delay_10ms(5);
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_AFIO_REMAP_SWJ_NOJTAG();

  /* LED_B PC13 */  /* LED_G PC14 */  /* LED_R PC15 */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin   = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY_WU PA0 */  /* KEY_BO PB2 */
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  
  GPIO_InitStruct.Pin   = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = GPIO_PIN_2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Init
  LED_R_Set;
  LED_G_Set;
  LED_B_Set;
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_EX_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* other pin */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin = GPIO_A_PINs;
  HAL_GPIO_Init(GPIO_A_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_B_PINs;
  HAL_GPIO_Init(GPIO_B_GPIO_PORT, &GPIO_InitStruct);

  // Init
  GPIO_A_Set;
  GPIO_B_Set;
}
/*====================================================================================================*/
/*====================================================================================================*/
