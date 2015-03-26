RedBeanSprout-M4 PWM Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/03/26

Description
========
RedBeanSprout-M4 PWM 的範例程式，按下按鍵 KEY_BO 時，會改變 PWM 的 Duty，按下按鍵 KEY_WU 時，會改變 PWM 的 Freq，並且透過 PWM 捕捉功能，將抓到的 PWM 以 1/2 的 Duty 輸出在 TIM1_CH1 上。

Hardware
========
* LED  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* KEY  
PA0  - KEY_WU  
PB2  - KEY_BO  

* PWM  
PA6  - TIM3 CH1 - PWM1  
PA7  - TIM3 CH2 - PWM2  
PB0  - TIM3 CH3 - PWM3  
PB1  - TIM3 CH4 - PWM4  
PA8  - TIM1 CH1 - PWM5  
PA1  - TIM2 CH2 - PWM In  

* UART  
PA9  - UART Tx  
PA10 - UART Rx  
> UARTx = USART1  
> BaudRate = 115200  
> ByteSize = 8  
> StopBits = 1  
> Parity = 'N'  
> HardwareFlowControl = None  
