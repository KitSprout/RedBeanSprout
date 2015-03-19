RedBeanSprout DigiPot-AD5292 Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/03/20

Description
========
RedBeanSprout [DigiPot-AD5292](https://github.com/KitSprout/DigiPot-AD5292) 的範例程式，預設輸出 256/1024 的阻值。

Hardware
========
* LED  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* Module - AD5292  
PB12 - AD5292_CS  
PB13 - AD5292_SCK  
PB14 - AD5292_SDO  
PB15 - AD5292_SDI  
> SPIx = SPI2  
> Dir = 2Lines_FullDuplex  
> Mode = Master  
> CPOL = Low  
> CPHA = 2Edge  
> FirstBit = MSB  
> DataSize = 16 bits  
> Prescaler = SPI_BaudRatePrescaler_64  
