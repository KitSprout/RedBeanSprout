RedBeanSprout-M4 ADC Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/03/29

Description
========
RedBeanSprout-M4 ADC 的範例程式，連續讀取 ADC 資料，同時 LED 會一直閃爍。

Hardware
========
* LED  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* ADC  
PA6  - ADC2_3  

* UART  
PA9  - UART Tx  
PA10 - UART Rx  
> UARTx = USART1  
> BaudRate = 115200  
> ByteSize = 8  
> StopBits = 1  
> Parity = 'N'  
> HardwareFlowControl = None  
