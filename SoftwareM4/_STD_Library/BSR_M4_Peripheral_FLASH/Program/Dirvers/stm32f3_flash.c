/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f3_system.h"
#include "stm32f3_flash.h"
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WritePageU8
**功能 : U8 寫入 FLASH
**輸入 : WritePage, *WriteData, DataLen
**輸出 : None
**使用 : Flash_WritePageU8(FLASH_SECTOR_6, WriteData, 1024);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePageU8( uint32_t WritePage, const uint8_t *WriteData, uint32_t DataLen )
{
  uint32_t Count = 0;
  FLASH_Status FLASHStatus;

  FLASH_Unlock();
  FLASH_OB_Unlock();
  while(Count < DataLen) {
    FLASHStatus = FLASH_ProgramHalfWord(WritePage + Count, (uint16_t)Byte16(WriteData[Count], WriteData[Count+1]));
    while(FLASHStatus != FLASH_COMPLETE);
    Count = Count + 2;
  }

  FLASH_Lock();
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WriteDataU16
**功能 : U16 寫入 FLASH
**輸入 : WritePage, *WriteData, DataLen
**輸出 : None
**使用 : Flash_WritePageU16(FLASH_PAGE_ADDR(12), WriteData, 512);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePageU16( uint32_t WritePage, const uint16_t *WriteData, uint32_t DataLen )
{
  uint32_t Count = 0;
  FLASH_Status FLASHStatus;

  FLASH_Unlock();

  while(Count < DataLen) {
    FLASHStatus = FLASH_ProgramHalfWord(WritePage + (Count << 1), WriteData[Count]);
    while(FLASHStatus != FLASH_COMPLETE);
    Count++;
  }

  FLASH_Lock();
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WritePageU32
**功能 : U32 寫入 FLASH
**輸入 : WritePage, *WriteData, DataLen
**輸出 : None
**使用 : Flash_WritePageU32(FLASH_PAGE_ADDR(12), WriteData, 256);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePageU32( uint32_t WritePage, const uint32_t *WriteData, uint32_t DataLen )
{
  uint32_t Count = 0;
  FLASH_Status FLASHStatus;

  FLASH_Unlock();

  while(Count < DataLen) {
    FLASHStatus = FLASH_ProgramWord(WritePage + (Count << 2), WriteData[Count]);
    while(FLASHStatus != FLASH_COMPLETE);
    Count++;
  }

  FLASH_Lock();
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ReadDataU8
**功能 : U8 讀取 FLASH
**輸入 : ReadPage, *ReadData, DataLen
**輸出 : None
**使用 : Flash_ReadPageU8(FLASH_PAGE_ADDR(12), ReadData, 512);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ReadPageU8( uint32_t ReadPage, uint8_t *ReadData, uint32_t DataLen )
{
  uint32_t Count = 0;
  uint16_t ReadBuf = 0;

  while(Count < DataLen) {
    ReadBuf = (uint16_t)(*(volatile uint32_t*)(ReadPage + Count));
    ReadData[Count++] = Byte8H(ReadBuf);
    ReadData[Count++] = Byte8L(ReadBuf);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ReadPageU16
**功能 : U16 讀取 FLASH
**輸入 : ReadPage, *ReadData, DataLen
**輸出 : None
**使用 : Flash_ReadPageU16(FLASH_PAGE_ADDR(12), ReadData, 512);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ReadPageU16( uint32_t ReadPage, uint16_t *ReadData, uint32_t DataLen )
{
  uint32_t Count = 0;

  while(Count < DataLen) {
    ReadData[Count] = (uint16_t)(*(volatile uint32_t*)(ReadPage + (Count << 1)));
    Count++;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ReadPageU32
**功能 : U32 讀取 FLASH
**輸入 : ReadPage, *ReadData, DataLen
**輸出 : None
**使用 : Flash_ReadPageU32(FLASH_PAGE_ADDR(12), ReadData, 256);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ReadPageU32( uint32_t ReadPage, uint32_t *ReadData, uint32_t DataLen )
{
  uint32_t Count = 0;

  while(Count < DataLen) {
    ReadData[Count] = (uint32_t)(*(volatile uint32_t*)(ReadPage + (Count << 2)));
    Count++;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ErasePage
**功能 : 擦除 FLASH
**輸入 : ErasePage
**輸出 : None
**使用 : Flash_ErasePage(FLASH_PAGE_ADDR(12));
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ErasePage( uint32_t ErasePage )
{
  FLASH_Status FLASHStatus;

  FLASH_Unlock();
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
  FLASHStatus = FLASH_ErasePage(ErasePage);
  while(FLASHStatus != FLASH_COMPLETE);
  FLASH_Lock();
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ErasePages
**功能 : 擦除多頁 FLASH
**輸入 : ErasePageStart, ErasePageEnd
**輸出 : None
**使用 : Flash_ErasePages(FLASH_PAGE_ADDR(12), FLASH_PAGE_ADDR(16));
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ErasePages( uint32_t ErasePageStart, uint32_t ErasePageEnd )
{
  FLASH_Status FLASHStatus;

  FLASH_Unlock();
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
  while(ErasePageStart <= ErasePageEnd) {
    FLASHStatus = FLASH_ErasePage(ErasePageStart);
    while(FLASHStatus != FLASH_COMPLETE);
    ErasePageStart = ErasePageStart + FLASH_PAGE_SIZE;
  }
  FLASH_Lock();
}
/*=====================================================================================================*/
/*=====================================================================================================*/
