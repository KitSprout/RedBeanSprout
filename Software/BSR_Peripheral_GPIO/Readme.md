RedBeanSprout GPIO Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/02/19

Description
========
RedBeanSprout GPIO 的範例程式，除按鍵以外所有 GPIO 以 100ms 閃爍，當按下按鍵 KEY_BO 時，只有 RGB LED 以 200ms 閃爍，當按下按鍵 KEY_WU 時，RGB LED 以 100ms 速度依序閃爍。

Hardware
========
* LED  [on, off] = [0, 1]  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* KEY  [on, off] = [1, 0]  
PA0  - KEY_WU  
PB2  - KEY_BO  
