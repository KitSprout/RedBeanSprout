/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_flash.h"
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WritePageU8
**功能 : U8 寫入 FLASH
**輸入 : WritePage, *WriteData, DataLen
**輸出 : None
**使用 : Flash_WritePageU8(FLASH_PAGE_ADDR(12), WriteData, 1024);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePageU8( u32 WritePage, uc8 *WriteData, u16 DataLen )
{
  u16 Count = 0;
  FLASH_Status FLASHStatus;

  FLASH_UnlockBank1();

  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  FLASHStatus = FLASH_ErasePage(WritePage);
  while((Count < DataLen) && (FLASHStatus == FLASH_COMPLETE)) {
    FLASHStatus = FLASH_ProgramHalfWord(WritePage+Count, Byte16(WriteData[Count+1], WriteData[Count]));
    Count += 2;
  }
  FLASH_LockBank1();
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WritePageU16
**功能 : U16 寫入 FLASH
**輸入 : WritePage, *WriteData, DataLen
**輸出 : None
**使用 : Flash_WritePageU16(FLASH_PAGE_ADDR(12), WriteData, 512);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePageU16( u32 WritePage, uc16 *WriteData, u16 DataLen )
{
  u16 Count = 0;
  FLASH_Status FLASHStatus;

  FLASH_UnlockBank1();

  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  FLASHStatus = FLASH_ErasePage(WritePage);
  while((Count < DataLen) && (FLASHStatus == FLASH_COMPLETE)) {
    FLASHStatus = FLASH_ProgramHalfWord(WritePage+(Count<<1), WriteData[Count]);
    Count++;
  }
  FLASH_LockBank1();
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ReadPageU8
**功能 : U8 讀取 FLASH
**輸入 : ReadPage, *ReadData, DataLen
**輸出 : None
**使用 : Flash_ReadPageU8(FLASH_PAGE_ADDR(12), ReadData, 1024);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ReadPageU8( u32 ReadPage, u8 *ReadData, u16 DataLen )
{
  u16 Count = 0;
  u16 ReadBuf = 0;

  while(Count<DataLen) {
    ReadBuf = (u16)(*(vu32*)(ReadPage+Count));
    ReadData[Count++] = Byte8L(ReadBuf);
    ReadData[Count++] = Byte8H(ReadBuf);
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
void Flash_ReadPageU16( u32 ReadPage, u16 *ReadData, u16 DataLen )
{
  u16 Count = 0;

  while(Count<DataLen) {
    ReadData[Count] = (*(vu32*)(ReadPage+(Count<<1)));
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
void Flash_ErasePage( u32 ErasePage )
{
  FLASH_Status FLASHStatus;

  FLASH_UnlockBank1();
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  FLASHStatus = FLASH_ErasePage(ErasePage);
  while(FLASHStatus != FLASH_COMPLETE);
  FLASH_LockBank1();
}
/*=====================================================================================================*/
/*=====================================================================================================*/
