RedBeanSprout UART Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/02/19

Description
========
RedBeanSprout UART 的範例程式，接收鍵盤輸入的資料，並回傳電腦顯示在 Putty 上，同時 LED_G 也會翻轉。

Hardware
========
* LED  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* UART  
PA9  - UART Tx  
PA10 - UART Rx  
> UARTx = USART1  
> BaudRate = 115200  
> ByteSize = 8  
> StopBits = 1  
> Parity = 'N'  
> HardwareFlowControl = None  
