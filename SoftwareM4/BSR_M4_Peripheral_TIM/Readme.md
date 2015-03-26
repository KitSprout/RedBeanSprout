RedBeanSprout-M4 TIMER Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/03/26

Description
========
RedBeanSprout-M4 TIMER 的範例程式，LED_R, LED_G 透過 Delay 延遲，每 100ms 閃爍一次，LED_B 透過計時器，每 500ms 閃爍一次。

Hardware
========
* LED  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* TIMER  
> TIMx = TIM2  
> Period = 500ms  
> Prescaler = 7200  
