Rainbow NanoRed
========
* File Name   : Readme.md
* Author      : Hom19910422
* Version     : v1.0
* Update      : 2013/10/22
* Description : Rainbow NenoRed Information
* Wiki        : https://github.com/Hom19910422/RainbowNanoRed/wiki

Design
========
* 低成本 ... 約100元台幣
* 小體積 ...  約5*2.2cm
* 方便學習 ... 可以直接插在麵包板上, 擴充模組做開發

Layout
========
採用STM32F103C  
3V3電源輸入 (( 沒有加穩壓LDO  

將 PA0, PB2 接上 KEY (( KEY_WU, KEY_BO  
PC13, PC14, PC15 接上 LED(( LED_R, LED_G, LED_B  
引出 PA9, PA10 的 UART 和 SW燒錄  
其餘拉到排針上 (( PA9, PA10 也有拉至排針  

Hardware
========
* Use Altium Designer 13
* PCB Size : 49.53 * 21.59mm

Program
========
* LAB_RNR_ADC ... ADC 轉換, 並傳資料至 PC
* LAB_RNR_ADCtoPWM ... ADC 讀取, 並輸出至 PWM
* LAB_RNR_EXTI ... 外部中斷
* LAB_RNR_FLASH ... 內部 FLASH 讀寫
* LAB_RNR_IAP ... In-Application Programming 程式, 從 PC 將 .bin 檔更新至 MCU ( PC 端使用 Python )
* LAB_RNR_IAP_LED ... IAP LED 程式
* LAB_RNR_IAP_TestBoard ... IAP TestBoard 程式
* LAB_RNR_LED ... LED & KEY
* LAB_RNR_PWM ... PWM 輸出
* LAB_RNR_PWR ... 進入StandbyMode, 並用 KEY_WU 鍵喚醒
* LAB_RNR_Systick ... Systick 計時
* LAB_RNR_USART ... UART 發送資料至PC
* LAB_RNR_USART_IntRecv ... UART 中斷接收, 並發送接收到的資料至 PC ( PC 端使用 Python )
* LAB_RNR_WDG ... WWDG & IWDG
* TEST_RNR_TestBoard ... 板子測試 ( PC 端使用 Python )

Get it
========
* 下載 PCB 送廠製作 & 依照 BOM 表購買元件自行焊接
* 完成品可在以下賣場可購得 http://goods.ruten.com.tw/item/show?21308206227979
  
  
<br>  
<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">Rainbow NenoRed</span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://plus.google.com/u/0/112822505513154783828/posts" property="cc:attributionName" rel="cc:attributionURL">Hom</a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/tw/deed.zh_TW">創用CC 姓名標示-相同方式分享 3.0 台灣 授權條款</a>釋出。<br />此作品衍生自<a xmlns:dct="http://purl.org/dc/terms/" href="https://github.com/Hom19910422" rel="dct:source">github.com</a>
