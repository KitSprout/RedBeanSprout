/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_flash.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define LED_B   PCO(13)
#define LED_G   PCO(14)
#define LED_R   PCO(15)

#define KEY_WU  PAI(0)
#define KEY_BO  PBI(2)
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void );
/*=====================================================================================================*/
/*=====================================================================================================*/
u8 CmpArr( u16 *Arr1, u16 *Arr2, u8 dataLen )
{
  u8 i = 0;
  u8 TempLen = dataLen;

  while(TempLen) {
    TempLen--;
    if(Arr1[i] == Arr2[i])
      i++;
  }

  return ((i==dataLen) ? SUCCESS : ERROR);
}

int main( void )
{
  u16 ReadData[64] = {0};
  u16 WriteData[64] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
                        1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
                        1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
                        1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

  SystemInit();
  GPIO_Config();

  LED_R = 0;
  if(KEY_WU == 1)
    Flash_ErasePage(FLASH_PAGE_ADDR(60));
  Delay_10ms(100);
  LED_R = 1;

  while(1) {
    LED_R = ~LED_R;
    Delay_10ms(10);
    if(KEY_BO == 1) { // Write Flash
      Flash_WritePage(FLASH_PAGE_ADDR(60), WriteData, 64);
      if(CmpArr(WriteData, ReadData, 64) == SUCCESS)
        LED_G = 0;
    }
    if(KEY_WU == 1) { // Read Flash
      Flash_ReadPage(FLASH_PAGE_ADDR(60), ReadData, 64);
      if(CmpArr(WriteData, ReadData, 64) == SUCCESS)
        LED_B = 0;
    }
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

  /* PC13 LED_B */	/* PC14 LED_G */	/* PC15 LED_R */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY_WU PA0 */	/* KEY_BO PB2 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  LED_R = 1;
  LED_G = 1;
  LED_B = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
