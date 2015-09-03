[RedBeanSprout](https://github.com/KitSprout/RedBeanSprout)
========
* Author  : [Hom](https://github.com/Hom-Wang)
* Version : v2.2
* Update  : 2015/09/04

Description
========
RedBeanSprout 是一個 STM32F103C / STM32F303C 的開發板，有 CortexM3 與 CortexM4 兩種版本，皆工作於 72 MHz 時脈下，體積小、成本低、可以直接插在麵包板上，有外加 LDO，可以使用 5V 或 3V3 供電。

 > 預計結合 [STM32duino](https://github.com/rogerclarkmelbourne/Arduino_STM32) 實現在 arduino IDE 上開發和燒錄。

License
========
* 硬體(Hardware)採用 [CC BY-SA 4.0](http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW) 方式授權 
  
　　<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/80x15.png" /></a>  
　　<span xmlns:dct="http://purl.org/dc/terms/" property="dct:title"> RedBeanSprout v2.2 </span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/KitSprout" property="cc:attributionName" rel="cc:attributionURL"> KitSprout </a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"> 創用CC 姓名標示-相同方式分享 4.0 國際 授權條款 </a>釋出。  


* 軟體(Software)採用 [MIT License](http://opensource.org/licenses/MIT) 方式授權  

Hardware
========
* 控制器　 : [STM32F103C](http://www.st.com/web/catalog/mmc/FM141/SC1169/SS1031/LN1565/PF189782) / [STM32F303C](http://www.st.com/web/catalog/mmc/FM141/SC1169/SS1576/LN1531/PF253449) 48Pin 72MHz
* PCB 尺寸 : 15.24 * 43.18mm
* 設計軟體 [Altium Designer 15](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v1.2](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v1.2) )  
  
相關的應用  
MicroMultimeter：https://github.com/KitSprout/MicroMultimeter  
ReflowOven：https://github.com/KitSprout/ReflowOven  

Software
========
RedBeanSprout CortexM3 版本  
* [BSR_Peripheral_ADC](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Peripheral_ADC) ... ADC 讀取範例
* [BSR_Peripheral_EXTI](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Peripheral_EXTI) ... 外部中斷範例
* [BSR_Peripheral_FLASH](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Peripheral_FLASH) ... FLASH 讀寫範例
* [BSR_Peripheral_GPIO](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Peripheral_GPIO) ... GPIO 輸入輸出範例
* [BSR_Peripheral_PWM](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Peripheral_PWM) ... PWM 輸出範例
* [BSR_Peripheral_PWR](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Peripheral_PWR) ... Power Down 範例
* [BSR_Peripheral_Systick](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Peripheral_Systick) ... Systick 範例
* [BSR_Peripheral_TIM](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Peripheral_TIM) ... Timer 計時範例
* [BSR_Peripheral_UART](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Peripheral_UART) ... USART 傳輸範例
* [BSR_Peripheral_UART_IntRecv](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Peripheral_UART_IntRecv) ... USART 中斷接收範例
* [BSR_Peripheral_WDG](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Peripheral_WDG) ... Watch Dog 範例
* [BSR_PeripheralHAL_GPIO](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_PeripheraHAL_GPIO) ... GPIO 輸入輸出範例 (HAL Driver)
* [BSR_PeripheralHAL_TIM](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_PeripheraHAL_GPIO) ... TIM 計時中斷範例 (HAL Driver)
* [BSR_PeripheralHAL_TIM-InputCap](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_PeripheraHAL_GPIO) ... TIM 輸入捕捉範例 (HAL Driver)
* [BSR_PeripheralHAL_TIM-PWM](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_PeripheraHAL_GPIO) ... TIM PWM 輸出範例 (HAL Driver)
* [BSR_PeripheralHAL_UART](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_PeripheraHAL_GPIO) ... UART 傳輸範例 (HAL Driver)
* [BSR_PeripheralHAL_UART-IntRecv](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_PeripheraHAL_GPIO) ... UART 中斷接收範例 (HAL Driver)
* [BSR_Module_DAC-DAC128S085](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Module_DAC-DAC128S085) ... DAC128S085 範例
* [BSR_Module_DAC-DAC8311](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Module_DAC-DAC8311) ... [DAC8311](https://github.com/KitSprout/DAC-DAC8311) 範例
* [BSR_Module_DigiPot-AD5292](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Module_DigiPot-AD5292) ... [AD5292](https://github.com/KitSprout/DigiPot-AD5292) 範例
* [BSR_Module_Flash-W25Q](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Module_Flash-W25Q) ... [W25Qxx](https://github.com/KitSprout/Flash-W25Q) 範例
* [BSR_Module_MPU6050](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Module_MPU6050) ... MPU6050 範例
* [BSR_Module_MPU9255](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Module_MPU9255_SPI) ... MPU9255-SPI 範例
* [BSR_Module_SF138](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Module_SF138) ... [74HC138](https://github.com/KitSprout/74HC138) 範例
* [BSR_Module_SF595](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Module_SF595) ... [74HC595](https://github.com/KitSprout/74HC595) 範例
* [BSR_Module_TFT2.2](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_Module_TFT2.2) ... [TFT2.2-inch](https://github.com/KitSprout/TFT_2.2-inch) 範例
  
RedBeanSprout CortexM4 版本  
* [BSR_M4_Peripheral_ADC](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Peripheral_ADC) ... ADC 讀取範例
* [BSR_M4_Peripheral_EXTI](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Peripheral_EXTI) ... 外部中斷範例
* [BSR_M4_Peripheral_FLASH](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Peripheral_FLASH) ... FLASH 讀寫範例
* [BSR_M4_Peripheral_GPIO](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Peripheral_GPIO) ... GPIO 輸入輸出範例
* [BSR_M4_Peripheral_PWM](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Peripheral_PWM) ... PWM 輸出範例
* [BSR_M4_Peripheral_Systick](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Peripheral_Systick) ... Systick 範例
* [BSR_M4_Peripheral_TIM](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Peripheral_TIM) ... Timer 計時範例
* [BSR_M4_Peripheral_UART](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Peripheral_UART) ... USART 傳輸範例
* [BSR_M4_Peripheral_UART_AutoBaudRate](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Peripheral_UART_AutoBaudRate) ... USART 鮑率自動調整
* [BSR_M4_Peripheral_UART_IntRecv](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Peripheral_UART_IntRecv) ... USART 中斷接收範例
* [BSR_M4_Module_SF138](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Module_SF138) ... [74HC138](https://github.com/KitSprout/74HC138) 範例
* [BSR_M4_Module_SF595](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Module_SF595) ... [74HC595](https://github.com/KitSprout/74HC595) 範例
* [BSR_M4_Module_TFT2.2](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Module_TFT2.2) ... [TFT2.2-inch](https://github.com/KitSprout/TFT_2.2-inch) 範例
* [BSR_M4_Module_TFT2.2_WaveForm](https://github.com/KitSprout/RedBeanSprout/tree/master/SoftwareM4/BSR_M4_Module_TFT2.2_WaveForm) ... [TFT2.2-inch](https://github.com/KitSprout/TFT_2.2-inch) 示波器範例

Related Documents
========
* [Google Drive](http://goo.gl/fQwBCc)

View
========
<img src="https://lh6.googleusercontent.com/-J5awKviGcxs/VRBtkeZY8uI/AAAAAAAAL_M/XQagI8r_zH4/s1200/DSC_2731.jpg" />

Config
========
<img src="https://lh3.googleusercontent.com/-dYO0WGnJa1w/VQ5zEcizwII/AAAAAAAAL9o/bA5z3fE46Jw/s1600/Config_v2.2.png" />

Schematic
========
<img src="https://lh5.googleusercontent.com/-m0ccQtZ--AM/VQcaIvHzk0I/AAAAAAAAL10/y6l9HnhyKic/s1600/Sch_RedBeanSprout_v2.2.png" />

Get it
========
[露天拍賣 Ruten](http://goods.ruten.com.tw/item/show?21512671509234)
