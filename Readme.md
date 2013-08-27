Rainbow NenoRed
========
* File Name   : Readme.md
* Author      : Hom19910422
* Version     : v1.0
* Update      : 2013/08/28
* Description : Rainbow NenoRed Information
* Wiki        : https://github.com/Hom19910422/RainbowNanoRed/wiki

Layout
========
採用STM32F103C  
3V3電源輸入 (( 沒有加穩壓LDO  

將 PA0, PB2 接上 KEY  
PC13, PC14, PC15 接上 LED  
引出 PA9, PA10 的 UART 和 SW燒錄  
其餘拉到排針上 (( PA9, PA10 也有拉至排針  

設計的想法
========
* 低成本 ... 約100元台幣
* 小體積 ... 只有5*2.2cm
* 方便學習 ... 可以直接插在麵包板上, 擴充模組做開發

Program
========
* LAB_RainbowNR_ADC ... ADC轉換, 並傳資料至PC
* LAB_RainbowNR_ADCtoPWM ... ADC讀取, 並輸出至PWM
* LAB_RainbowNR_EXTI ... 外部中斷
* LAB_RainbowNR_LED ... LED & KEY
* LAB_RainbowNR_PWM ... PWM輸出
* LAB_RainbowNR_USART ... UART發送資料至PC
* LAB_RainbowNR_USART_IntRecv ... UART中斷接收, 並發送接收到資料至PC
* LAB_RainbowNR_Systick ... Systick計時
* TEST_RainbowNR_TestBoard ... 板子測試

<br>  
<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">Rainbow NenoRed</span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://plus.google.com/u/0/112822505513154783828/posts" property="cc:attributionName" rel="cc:attributionURL">Hom</a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW">創用CC 姓名標示-相同方式分享 3.0 台灣 授權條款</a>釋出。<br />此作品衍生自<a xmlns:dct="http://purl.org/dc/terms/" href="https://github.com/Hom19910422" rel="dct:source">github.com</a>
