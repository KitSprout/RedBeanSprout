RedBeanSprout EXTI Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/02/19

Description
========
RedBeanSprout EXTI 的範例程式，按下 KEY_WU 觸發外部中斷，使 LED_B 閃爍。

Hardware
========
* LED  [on, off] = [0, 1]  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* KEY  [on, off] = [1, 0]  
PA0  - KEY_WU  
PB2  - KEY_BO  

* EXTI  
> Line - Line0  
> Trigger - Rising  
