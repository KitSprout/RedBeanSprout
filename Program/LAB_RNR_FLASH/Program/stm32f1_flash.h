/* #include "stm32f1_flash.h" */

#ifndef __STM32F1_FLASH_H
#define __STM32F1_FLASH_H
/*=====================================================================================================*/
/*=====================================================================================================*/
// Medium Density ... STM32F103x8(64KB), STM32F103xB(128KB)
#define FLASH_START_ADDR        ((u32)0x08000000)
#define FLASH_PAGE_SIZE         ((u16)0x0400)   // 1KBytes
#define FLASH_PAGE_ADDR(PAGE)   ((u32)(FLASH_START_ADDR + FLASH_PAGE_SIZE*PAGE))

#define FLASH_BOOTLOAD_ADDR     ((u32)0x1FFFF000)   // 2KB, 0x1FFF_F000 - 0x1FFF_F7FF
/*=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePage( u32 WritePage, uc16 *WriteData, u16 DataLen );
void Flash_ReadPage( u32 ReadPage, u16 *ReadData, u16 DataLen );
void Flash_ErasePage( u32 ErasePage );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif	 
