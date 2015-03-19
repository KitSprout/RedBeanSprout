RedBeanSprout Flash-W25Q Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/03/20

Description
========
RedBeanSprout [Flash-W25Q](https://github.com/KitSprout/Flash-W25Q) 的範例程式，目前僅讀取出 ID。

Hardware
========
* LED  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* Module - W25Qxx  
PB10 - W25Q_WP  
PB11 - W25Q_HOL  
PB12 - W25Q_CS  
PB13 - W25Q_SCK  
PB14 - W25Q_SDO  
PB15 - W25Q_SDI  
> SPIx = SPI2  
> Dir = 2Lines_FullDuplex  
> Mode = Master  
> CPOL = Low  
> CPHA = 1Edge  
> FirstBit = MSB  
> DataSize = 8 bits  
> Prescaler = SPI_BaudRatePrescaler_64  
