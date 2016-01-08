RedBeanSprout-M4 TFT2.2_WaveForm Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/03/28

Description
========
RedBeanSprout-M4 TFT2.2_WaveForm 的範例程式，透過 SPI 讀寫 [TFT_2.2-inch](https://github.com/KitSprout/TFT_2.2-inch) 模組，計算三角函數並將波形顯示出來。

Hardware
========
* LED  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* KEY  
PA0  - KEY_WU  
PB2  - KEY_BO  

* TFT2.2  
PA1  - LCD_LIG  
PB10 - LCD_DC  
PB11 - LCD_RST  
PB12 - LCD_CST  
PB13 - LCD_CLK  
PB14 - LCD_SDO  
PB15 - LCD_SDI  
> SPIx = SPI2  
> Dir = 2Lines_FullDuplex  
> Mode = Master  
> CPOL = High  
> CPHA = 2Edge  
> FirstBit = MSB  
> DataSize = 8 bits  
> Prescaler = Prescaler_2 
