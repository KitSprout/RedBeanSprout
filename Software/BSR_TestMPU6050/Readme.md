RedBeanSprout MPU6050 Example
========
* Author  : [Hom](http://about.me/Hom)
* Update  : 2015/02/19

Description
========
RedBeanSprout MPU6050 的範例程式，使用模擬 I2C 方式讀寫 MPU6050 ID 暫存器，確認是否讀取成功。

Hardware
========
* LED  [on, off] = [0, 1]  
PC13 - LED_B  
PC14 - LED_G  
PC15 - LED_R  

* KEY  [on, off] = [1, 0]  
PA0  - KEY_WU  
PB2  - KEY_BO  

* MPU6050  
PB5  - SCL  
PB6  - SDA  