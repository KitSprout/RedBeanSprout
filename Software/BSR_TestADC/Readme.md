RedBeanSprout ADC Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/02/19

Description
========
RedBeanSprout ADC 的範例程式，連續讀取 ADC 資料，同時 LED_G 會一直閃爍。

Hardware
========
* LED  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* KEY  
PA0  - KEY_WU  
PB2  - KEY_BO  

* ADC  
PA4  - ADC1_4  
PA5  - ADC1_5  

* UART  
PA9  - UART Tx  
PA10 - UART Rx  
> UARTx = USART1  
> BaudRate = 115200  
> ByteSize = 8  
> StopBits = 1  
> Parity = 'N'  
> HardwareFlowControl = None  
