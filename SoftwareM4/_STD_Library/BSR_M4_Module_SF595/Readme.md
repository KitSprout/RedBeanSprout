RedBeanSprout-M4 SF595 Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/03/28

Description
========
RedBeanSprout-M4 74HC595 的範例程式， 輸出在 0xFE - 0x7F 來回移動，當按下 KEY_WU 關閉輸出，按下 KEY_BO 開啟輸出。

Hardware
========
* LED  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* KEY  
PA0  - KEY_WU  
PB2  - KEY_BO  

* Module - SF595  
PA1  - SF595_DI  
PA2  - SF595_OE  
PA3  - SF595_ST  
PA4  - SF595_SH  
PA5  - SF595_MR  
