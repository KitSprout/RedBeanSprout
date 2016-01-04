/* #include "stm32f1_usb.h" */

#ifndef __STM32F1_USB_H
#define __STM32F1_USB_H

#include "stm32f1xx_hal.h"

#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define CDC_POLLING_INTERVAL 5

extern USBD_HandleTypeDef USBD_Device;
extern USBD_CDC_ItfTypeDef USBD_CDC_fops;
/*=====================================================================================================*/
/*=====================================================================================================*/
void    USB_VCP_Init( void );

void    USB_VCP_SendByte( uint8_t sendByte );
void    USB_VCP_SendData( uint8_t *sendData, uint16_t lens );
void    USB_VCP_SendStr( char *pWord );

uint8_t USB_VCP_RecvByte( void );
void    USB_VCP_RecvData( uint8_t *recvData, uint16_t lens );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
