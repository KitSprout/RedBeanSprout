RedBeanSprout DAC-DAC8311 Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/03/20

Description
========
RedBeanSprout [DAC-DAC8311](https://github.com/KitSprout/DAC-DAC8311) 的範例程式，不斷產生半弦波訊號。

Hardware
========
* LED  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* Module - DAC8311  
PB12 - DAC_SYN  
PB13 - DAC_SCK  
PB14 - DAC_SDO  
PB15 - DAC_SDI  
> SPIx = SPI2  
> Dir = 2Lines_FullDuplex  
> Mode = Master  
> CPOL = Low  
> CPHA = 2Edge  
> FirstBit = MSB  
> DataSize = 16 bits  
> Prescaler = SPI_BaudRatePrescaler_4  
