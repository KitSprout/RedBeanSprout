/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_flash.h"
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WritePageU8
**功能 : Write Flash uint8_t
**輸入 : writeAddr, *writeData, lens
**輸出 : None
**使用 : Flash_WritePageU8(FLASH_PAGE_ADDR(12), writeData, 1024);
**=====================================================================================================*/
/*=====================================================================================================*/
int8_t Flash_WritePageU8( uint32_t writeAddr, const uint8_t *writeData, uint32_t lens )
{
  int8_t status = ERROR;
  uint32_t count = 0;

  HAL_FLASH_Unlock();
  do {
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, writeAddr + count, Byte16(uint16_t, writeData[count], writeData[count + 1]));
    count += 2;
  } while((count < lens) && (status == HAL_OK));
  HAL_FLASH_Lock();

  return status;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WritePageU16
**功能 : Write Flash uint16_t
**輸入 : writeAddr, *writeData, lens
**輸出 : None
**使用 : Flash_WritePageU16(FLASH_PAGE_ADDR(12), writeData, 512);
**=====================================================================================================*/
/*=====================================================================================================*/
int8_t Flash_WritePageU16( uint32_t writeAddr, const uint16_t *writeData, uint32_t lens )
{
  int8_t status = ERROR;
  uint32_t count = 0;

  HAL_FLASH_Unlock();
  do {
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, writeAddr + (count << 1), writeData[count]);
  } while((++count < lens) && (status == HAL_OK));
  HAL_FLASH_Lock();

  return status;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WritePageU32
**功能 : Write Flash uint32_t
**輸入 : writeAddr, *writeData, lens
**輸出 : None
**使用 : Flash_WritePageU32(FLASH_PAGE_ADDR(12), writeData, 256);
**=====================================================================================================*/
/*=====================================================================================================*/
int8_t Flash_WritePageU32( uint32_t writeAddr, const uint32_t *writeData, uint32_t lens )
{
  int8_t status = ERROR;
  uint32_t count = 0;

  HAL_FLASH_Unlock();
  do {
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, writeAddr + (count << 2), writeData[count]);
  } while((++count < lens) && (status == HAL_OK));
  HAL_FLASH_Lock();

  return status;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WritePageU64
**功能 : Write Flash uint64_t
**輸入 : writeAddr, *writeData, lens
**輸出 : None
**使用 : Flash_WritePageU64(FLASH_PAGE_ADDR(12), writeData, 128);
**=====================================================================================================*/
/*=====================================================================================================*/
//int8_t Flash_WritePageU64( uint32_t writeAddr, const uint64_t *writeData, uint32_t lens )
//{
//  int8_t status = ERROR;
//  uint32_t count = 0;

//  HAL_FLASH_Unlock();
//  do {
//    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, writeAddr + (count << 3), writeData[count]);
//  } while((++count < lens) && (status == HAL_OK));
//  HAL_FLASH_Lock();

//  return status;
//}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ReadPageU8
**功能 : Read Flash uint8_t
**輸入 : readAddr, *readData, lens
**輸出 : None
**使用 : Flash_ReadPageU8(FLASH_PAGE_ADDR(12), readData, 1024);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ReadPageU8( uint32_t readAddr, uint8_t *readData, uint32_t lens )
{
  uint16_t readBuf = 0;
  uint32_t count = 0;

  do {
    readBuf = (uint16_t)(*(__IO uint32_t*)(readAddr + count));
    readData[count]     = Byte8H(readBuf);
    readData[count + 1] = Byte8L(readBuf);
    count += 2;
  } while(count < lens);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ReadPageU16
**功能 : Read Flash uint16_t
**輸入 : readAddr, *readData, lens
**輸出 : None
**使用 : Flash_ReadPageU16(FLASH_PAGE_ADDR(12), readData, 512);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ReadPageU16( uint32_t readAddr, uint16_t *readData, uint32_t lens )
{
  uint32_t count = 0;

  do {
    readData[count] = (uint16_t)(*(__IO uint32_t*)(readAddr + (count << 1)));
  } while(++count < lens);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ReadPageU32
**功能 : Read Flash uint32_t
**輸入 : readAddr, *readData, lens
**輸出 : None
**使用 : Flash_ReadPageU32(FLASH_PAGE_ADDR(12), readData, 256);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ReadPageU32( uint32_t readAddr, uint32_t *readData, uint32_t lens )
{
  uint32_t count = 0;

  do {
    readData[count] = (uint32_t)(*(__IO uint32_t*)(readAddr + (count << 2)));
  } while(++count < lens);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ReadPageU64
**功能 : Read Flash uint64_t
**輸入 : readAddr, *readData, lens
**輸出 : None
**使用 : Flash_ReadPageU64(FLASH_PAGE_ADDR(12), readData, 128);
**=====================================================================================================*/
/*=====================================================================================================*/
//void Flash_ReadPageU64( uint32_t readAddr, uint64_t *readData, uint32_t lens )
//{
//  uint32_t count = 0;

//  do {
//    readData[count] = (uint64_t)(*(__IO uint32_t*)(readAddr + (count << 3)));
//  } while(++count < lens);
//}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ErasePages
**功能 : Erase Flash Memory
**輸入 : ErasePageStart, NumPages
**輸出 : status
**使用 : Flash_ErasePages(FLASH_PAGE_ADDR(12), 8);
**=====================================================================================================*/
/*=====================================================================================================*/
int8_t Flash_ErasePages( uint32_t erasePageStart, uint32_t nbPages )
{
  FLASH_EraseInitTypeDef EraseInitStruct;

  int8_t status = ERROR;
  uint32_t SectorError = 0;

  HAL_FLASH_Unlock();
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.PageAddress = erasePageStart;
  EraseInitStruct.NbPages     = nbPages;
  status = HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError);

  HAL_FLASH_Lock();

  return status;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
