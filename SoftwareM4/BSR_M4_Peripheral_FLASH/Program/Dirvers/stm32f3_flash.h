/* #include "stm32f3_flash.h" */

#ifndef __STM32F3_FLASH_H
#define __STM32F3_FLASH_H

#include "stm32f30x.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define FLASH_START_ADDR      ((uint32_t)0x08000000)
#define FLASH_PAGE_SIZE       ((uint32_t)0x00000800)  // 2 KBytes
#define FLASH_PAGE_ADDR(PAGE) ((uint32_t)(FLASH_START_ADDR + FLASH_PAGE_SIZE * (PAGE)))
/*=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePageU8( uint32_t WriteAddr, const uint8_t *WriteData, uint32_t DataLen );
void Flash_WritePageU16( uint32_t WritePage, const uint16_t *WriteData, uint32_t DataLen );
void Flash_WritePageU32( uint32_t WritePage, const uint32_t *WriteData, uint32_t DataLen );
void Flash_ReadPageU8( uint32_t ReadPage, uint8_t *ReadData, uint32_t DataLen );
void Flash_ReadPageU16( uint32_t ReadPage, uint16_t *ReadData, uint32_t DataLen );
void Flash_ReadPageU32( uint32_t ReadPage, uint32_t *ReadData, uint32_t DataLen );
void Flash_ErasePage( uint32_t ErasePage );
void Flash_ErasePages( uint32_t ErasePageStart, uint32_t ErasePageEnd );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif	 
