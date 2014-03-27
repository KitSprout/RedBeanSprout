[Rainbow NanoRed](https://github.com/Hom-Wang/RainbowNanoRed)
========
* Author  : [Hom](https://github.com/Hom-Wang)
* Version : v1.2
* Update  : 2014/03/27

Description
========
Rainbow NanoRed 是一個 STM32F103C 的開發板，體積小、成本低、可以直接插在麵包板上，有外加 LDO，可以使用 5V 或 3V3 供電。

License
========
* 硬體(Hardware)採用 [CC BY-SA 3.0 TW](http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW) 方式授權 
  
　　<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/80x15.png" /></a>  
　　<span xmlns:dct="http://purl.org/dc/terms/" property="dct:title"> Rainbow NanoRed </span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://plus.google.com/u/0/112822505513154783828/posts" property="cc:attributionName" rel="cc:attributionURL"> Hom </a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW"> 創用CC 姓名標示-相同方式分享 3.0 台灣 授權條款 </a>釋出。  

* 軟體(Software)採用 [Unlicense](http://unlicense.org) 方式授權  

Hardware
========
* 控制器　 : [STM32F103C](http://www.st.com/web/catalog/mmc/FM141/SC1169/SS1031/LN1565/PF189782) 48Pin 72MHz
* 其他外接 : 2 個按鍵 ( PA0, PB2 )、3 個 LED ( PC13, PC14, PC15 )、 1 個 UART ( PA9, PA10 )
* PCB 尺寸 : 48.77 * 18.29mm
* 設計軟體 [Altium Designer 13](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v0.3](https://github.com/OpenPCB/AltiumDesigner_PcbLibrary/releases/tag/v0.3) )

Software
========
* LAB_RNR_ADC ... ADC 轉換, 並傳資料至 PC
* LAB_RNR_ADCtoPWM ... ADC 讀取, 並輸出至 PWM
* LAB_RNR_EXTI ... 外部中斷
* LAB_RNR_FLASH ... 內部 FLASH 讀寫
* LAB_RNR_IAP ... [In-Application Programming](http://blog.csdn.net/ysdaniel/article/details/6631482), 從 PC 將 .bin 檔更新至 MCU ( PC 端使用 Python )
* LAB_RNR_IAP_LED ... IAP LED 程式
* LAB_RNR_IAP_TestBoard ... IAP TestBoard 程式
* LAB_RNR_LED ... LED & KEY
* LAB_RNR_PWM ... PWM 輸出
* LAB_RNR_PWR ... 進入StandbyMode, 並用 KEY_WU 鍵喚醒
* LAB_RNR_Systick ... Systick 計時
* LAB_RNR_TFT2.2 ... SPI 2.2" 240*320 TFT LCD ( use [TFT_2.2-inch](https://github.com/OpenPCB/TFT_2.2-inch) )
* LAB_RNR_USART ... UART 發送資料至PC
* LAB_RNR_USART_IntRecv ... UART 中斷接收, 並發送接收到的資料至 PC ( PC 端使用 Python )
* LAB_RNR_WDG ... WWDG & IWDG
* TEST_RNR_TestBoard ... 板子測試 ( PC 端使用 Python )

Get it
========
* 下載 PCB 送廠製作 & 依照 BOM 表購買元件自行焊接
* 完成品可在以下賣場可購得 http://goods.ruten.com.tw/item/show?21308206227979

Related Documents
========
* [Google Drive](https://drive.google.com/folderview?id=0BzL2wwAot6oPemVlLTlMNkNzMDg&usp=sharing)

View
========
<img src="https://lh6.googleusercontent.com/-ejRshG_OBsQ/UtSHfTKIrEI/AAAAAAAAGO8/OwQ3M8ICMQ4/s1200/DSC_1945.jpg" />
<img src="https://lh5.googleusercontent.com/-JvIIr9zmsnQ/UtSHfnHSBII/AAAAAAAAGPY/6r7Qt-2j7jU/s1200/DSC_1953.jpg" />

<br />
更多圖片 [Google+ albums](https://plus.google.com/u/0/photos/112822505513154783828/albums/5891276253041236273)

Config
========
<img src="https://lh3.googleusercontent.com/-pO4Zn3CdW7Q/UtSHe5-LtEI/AAAAAAAAGOw/_tGj59N4i9I/s1200/Config.png" />
<img src="https://lh6.googleusercontent.com/-apIzuv-Nw0Q/UgUywlum8MI/AAAAAAAADEI/myUMY4F1qbo/s1200/Config.png" />

Schematic
========
<img src="https://lh5.googleusercontent.com/-72_bda1eDbU/UtSKSSGvUSI/AAAAAAAAGQM/E8ccDzY4F04/s1200/RNR_Sch%2520v1.2.png" />
