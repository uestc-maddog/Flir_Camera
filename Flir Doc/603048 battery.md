# Li-ion Polymer Battery 锂离子聚合物电池
08/10/2016

<div id='id-section1'/>
## 目录 Content
* [目录 Contents](#id-section1)	
* 1 [锂电池性能 Battery Performance](#id-section2)
  * 1.1 [电池参数 Specifications](#id-section3)	
  * 1.2 [充电曲线 Charging Characteristics](#id-section4)	
  * 1.3 [放电曲线 Discharge Characteristics](#id-section5)	
  * 1.4 [电池剩余电量标记阈值 Battery Level Display Threshold](#id-section6)
  * 1.5 [过充过放Overcharge and Overdischarge](#id-section7)
* 2 [故障情况 Trouble Shotting](#id-section8)
* 3 [参考 Reference](#id-section9)

<div id='id-section2'/>
## 1 锂电池性能 Battery Performance

<div id='id-section3'/>
### 1.1 电池参数 Specifications
|参数 Parameter|标准值 Typ|单位 Unit|
|---|---|---|
|电池型号 PN:|603048||
|电池容量 Capacity:|900|mAh|
|电芯重量 Weight:|17 |g|
|充电限制电压	Charge Limit Voltge:|4.2|V|
|工作温度 Temperature Limit:|Charging：0～45 Discharging：-20～60| °C|
|工作湿度 Humidity:|≤90%|RH|

<div id='id-section4'/>
### 1.2 充电曲线 Charging Characteristics
测试条件：完全放电后，连接micro-USB充电器给设备充电，直至LCD显示电量充满。
Test environment: Charge a battery from 3.7 volt till fully charged.

![](https://github.com/uestc-maddog/Flir_Camera/blob/master/Flir%20Doc/picture/charge.png)

<div id='id-section5'/>
### 1.3 放电曲线 Discharge Characteristics
测试条件：完全充电后，设备按照出厂配置开机运行，直至提示低电量自动关机。
Test Environment: Keep device functional till battery level too low and switch off automatically.

![](https://github.com/uestc-maddog/Flir_Camera/blob/master/Flir%20Doc/picture/discharge.png)

<div id='id-section6'/>
### 1.4 电池剩余电量标记阈值 Battery Level Display Threshold

电量状态 Battery Status |电池电压范围 Voltage Range (V)|电量显示 Battery Display|剩余使用时长 Remain Battery Life
------- |---------------|-------|---
Full	|  [4.20, +∞ )	| 三格 3 bar| 8.5H       
High	|  (3.89, 4.20)	| 三格 3 bar| 4.5~8.5H
Middle	|  (3.79, 3.89]	| 两格 2 bar| 2~4.5H
Low	    |  (3.69, 3.79]	| 一格 1 bar| 1~2.0H
Empty	|  (3.65, 3.69]	| 空格、闪烁 empty| 0~1.0H
Shutdown|   (-∞, 3.65]  | 自动关机 auto switch-off| -

<div id='id-section7'/>
### 1.5 过充过放 Overcharge and Overdischarge
* 电池包带有过放、过充保护电路，电池管理IC也具备过充保护功能。但在使用时仍需注意避免对电池过放、过充。 The battery pack includes over-discharge/over-charge protection circuit, battery management IC includes over charge protection features. However, user should avoid over-charge or over-discharge battery.

* 不要将设备长时间连接充电器。 Remove charging cable after charge finished. Remain charges may damage battery.

* 过度放电会对电池造成损失。电池低电量关机后请连接充电器充电后再开机操作。 Over discharge may cause damage to battery. Connect charging cable once the device battery level is too low and switch off automatically. 

* 长时间不使用设备时需要先将电池充满电后存储。如果是时间超过一个月的存储，需要充满电池并按on按键20秒开启低功耗存放模式后存放。Please fully charge battery before storage. If the devcie is not in use for more than one month, user needs to fully charge battery, then press on button for at leaset 20s to enable the storage mode.

<div id='id-section8'/>
## 2 故障情况 Trouble Shotting

故障表现 Problems |可能原因 Possible Explanation|解决办法 Solutions
------- |---------------|-------
设备无法开机，检测电池电压为0，屏幕不亮。Unable to turn on device, battery voltage meassured as 0 volt.|电池连接线断裂; 电池损坏。Broken battery cable; broken battery pack|电池连接线相对易坏。检查电池包连接线与电池在PCB上接头。若问题仍然存在，更换电池能够解决问题。The battery cable is relatively vulnerable. Check wires connected battery pack etc. If problem still exist, replace battery pack should solve the issue.
电池正常，无法充电，充电发热严重。Not able to charge battery, temperature raise dramatically while charging	|电源管理部分电路损坏。Battery management IC broke| 更换PCB。 Replace PCB.

<div id='id-section9'/>
## 3 参考 Reference 
 1. [充、放电测试原始数据 Charge/Discharge Test Raw Data](https://github.com/uestc-maddog/Flir_Camera/blob/master/Flir%20Doc/data/battery-test.xlsx)
 2. [电池数据手册 Battery Datasheet](https://github.com/uestc-maddog/Flir_Camera/blob/master/Flir%20Doc/data/603048%EF%BC%88900mAh%EF%BC%89%E6%99%AE%E9%80%9A%E7%89%88%E5%8A%A0%E7%BA%BF%E8%A7%84%E6%A0%BC%E4%B9%A6.pdf)
