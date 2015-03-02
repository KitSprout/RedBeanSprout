[RedBeanSprout](https://github.com/KitSprout/RedBeanSprout)
========
* Author  : [Hom](https://github.com/Hom-Wang)
* Version : v2.0
* Update  : 2015/03/03

Description
========
RedBeanSprout 是一個 STM32F103C 的開發板，體積小、成本低、可以直接插在麵包板上，有外加 LDO，可以使用 5V 或 3V3 供電。

License
========
* 硬體(Hardware)採用 [CC BY-SA 4.0](http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW) 方式授權 
  
　　<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/80x15.png" /></a>  
　　<span xmlns:dct="http://purl.org/dc/terms/" property="dct:title"> RedBeanSprout v2.0 </span>由<a xmlns:cc="http://creativecommons.org/ns#" href="http://about.me/Hom" property="cc:attributionName" rel="cc:attributionURL"> Hom </a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"> 創用CC 姓名標示-相同方式分享 4.0 國際 授權條款 </a>釋出。  

* 軟體(Software)採用 [MIT License](http://opensource.org/licenses/MIT) 方式授權  

Hardware
========
* 控制器　 : [STM32F103C](http://www.st.com/web/catalog/mmc/FM141/SC1169/SS1031/LN1565/PF189782) 48Pin 72MHz
* PCB 尺寸 : 15.24 * 43.18mm
* 設計軟體 [Altium Designer 14](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v1.1](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v1.1) )

Software
========
* 開發環境 Keil uVision v5.13
* [BSR_TestADC](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestADC) ... ADC 讀取範例
* [BSR_TestEXTI](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestEXTI) ... 外部中斷範例
* [BSR_TestFLASH](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestFLASH) ... FLASH 讀寫範例
* [BSR_TestGPIO](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestGPIO) ... GPIO 輸入輸出範例
* [BSR_TestMPU6050](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestMPU6050) ... MPU6050 範例
* [BSR_TestPWM](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestPWM) ... PWM 輸出範例
* [BSR_TestPWR](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestPWR) ... Power Down 範例
* [BSR_TestSF138](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestSF138) ... 74HC138 範例
* [BSR_TestSF595](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestSF595) ... 74HC595 範例
* [BSR_TestSystick](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestSystick) ... Systick 範例
* [BSR_TestTIM](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestTIM) ... Timer 計時範例
* [BSR_TestUART](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestUART) ... USART 傳輸範例
* [BSR_TestUART-IntRecv](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestUART-IntRecv) ... USART 中斷接收範例
* [BSR_TestWDG](https://github.com/KitSprout/RedBeanSprout/tree/master/Software/BSR_TestWDG) ... Watch Dog 範例

Related Documents
========
* [Google Drive](http://goo.gl/fQwBCc)

View
========
<img src="https://lh6.googleusercontent.com/-KQ2tdPJ37YM/VG4jHq6hBMI/AAAAAAAALPA/V0kFBGK1DLo/s1600/DSC_2659.jpg" />

Config
========
<img src="https://lh6.googleusercontent.com/-h0BITqMqzWk/VPSuiPjBoOI/AAAAAAAALyY/mNXFsvkKN20/s800/Config_2.png" />

Schematic
========
<img src="https://lh3.googleusercontent.com/-OBktAGXUPyg/VGcwKB4T-0I/AAAAAAAALJM/_gpFlw8X97E/s1600/Sch_RedBeanSprout.png" />
