# FLIR TECHNICAL MANUAL
09/10/2016
ver 1.0


## Contents
* [1 INTRODUCTION](#id-section1)
* [2 USER MANUAL]()
	* [2.1 POWER ON/OFF]()
	* [2.2 CHARGING]()
	* [2.3 COLOR MODE]()
	* [2.4 CONFIGURE DEVICE]()
		* [2.4.1 Brightness]()
		* [2.4.2 Sleep Mode]()
		* [2.4.3 Reticle]()
		* [2.4.4 Version]()
		* [2.4.5 Reset]()
	* [2.5 STORAGE]()
* [3 SPECIFICATIONS]()
* [4 TROUBLE SHOTTING]()

<div id='id-section1'/>
## 1 INTRODUCTION

## 2 USER MANUAL
The `product` is designed to be easy to use and friendly to user. All the configurations is saved and will remain after power cycle. 

### 2.1 POWER ON/OFF
**Power on**
When device power is off, simply press ON button for at least 4 second to power on the device. Booting animation will display while system initialize and then everything is ready to go.

**Power off**
User can easily power off device by press ON button for 4 second. And the device can be automatically power down under following conditions:
* Battery is below critical level
* Sleep is enabled and power on configuring sleep time achieved

### 2.2 CHARGING
Plug-in the micro-USB charging cable with power adaptor to charge the device, and charging status will display on screen. Charging takes 2-3 hours and the battery can supprot up to 9 hours work.

To keep the battery under best performance, un-plug charging cable after charging, do not charge for a long time. Do not power up device when it's battery level is too low and automatically power off.



### 2.3 COLOR MODE
`product` supports two color mode. Gray Scale mode and Colored mode. User can toggle between two display mode under image view by press MODE button. Pictures below demostrate two different color modes.

![](https://github.com/uestc-maddog/Flir_Camera/blob/master/Flir%20Doc/picture/scale.bmp)

![](https://github.com/uestc-maddog/Flir_Camera/blob/master/Flir%20Doc/picture/color.bmp)

### 2.4 CONFIGURE DEVICE
Press MODE button under image view to enter configuration menu. User can use MODE button to navigate through different configurations. Use short press to switch options and long press to select. `product` will exist to image view 30s after user's last operation on MODE button.

![](https://github.com/uestc-maddog/Flir_Camera/blob/master/Flir%20Doc/picture/content.bmp)


#### 2.4.1 Brightness
`product` provides 4 brightness level. User can easily switch from different level by short press MODE button to move cursor and long press MODE button to select.

![](https://github.com/uestc-maddog/Flir_Camera/blob/master/Flir%20Doc/picture/content_brightness.bmp)

|Options|Desc|
|---|---|
|Level-1|25% of full brightness|
|Level-2|50% of full brightness|
|Level-3|75% of full brightness|
|Level-4|full brightness|
|back|back to previous menu|


#### 2.4.2 Sleep Mode
User can enable Sleep features to allow device sleep after inactivate for a period of time. Sleep is disabled by default. User can select different sleep count down time under this menu. By selecting N/A, this feature is disabled.

![](https://github.com/uestc-maddog/Flir_Camera/blob/master/Flir%20Doc/picture/content_sleep.bmp)

|Options|Desc|
|---|---|
|3 min|Sleep after 3 minutes inactivate|
|5 min|Sleep after 5 minutes inactivate|
|10 min|Sleep after 10 minutes inactivate|
|15 min|Sleep after 15 minutes inactivate|
|N/A|disabled|
|back|back to previous menu|


#### 2.4.3 Reticle
Reticle can be configured under this sub-menu. Four options was listed in this menu, which is Enable/Disable, Hor, Ver, back. To navigate through this menu, user need to use long press MODE button to move cursor and short press MODE button to select. Be aware that this operation is different from other menus.

![](https://github.com/uestc-maddog/Flir_Camera/blob/master/Flir%20Doc/picture/oumu.jpg)

|Options|Desc|
|---|---|
|Enable/Disable|Toggle to enable the reticle display|
|Hor|Adjust the horizon location of the reticle|
|Ver|Adjust the vertical location of the reticle|
|back|back to previous menu|

#### 2.4.4 Version
Version information will displayed by selecting this options. 

![](https://github.com/uestc-maddog/Flir_Camera/blob/master/Flir%20Doc/picture/version.png)

#### 2.4.5 Reset
User can reset all configurations to factory mode by selecting this option.

### 2.5 STORAGE
To keep battery in best performance, `product` needs to be full charge bofore storage. If the storage is longer than one month, user needs to pree ON button for at least 15s to enable HARD RESET mode which allow the system goes into deeper sleep mode.

## 3 SPECIFICATIONS

### 3.1 Camera Specifications

#### 3.1.1 Basic Specifications
|Parameters|Detail|
|--------|--------|
|Sensor technology 	|Uncooled VOx microbolometer|
|Spectral range 	|Longwave infrared, 8 μm to 14 μm|
|Array format 	|80 × 60, progressive scan|
|Pixel size |	17 μm|
|Effective frame rate 	|	8.6 Hz (exportable)	|
|Thermal sensitivity | <50 mK (0.050° C)|
|Temperature compensation |Automatic. Output image independent of camera temperature.|
|Non-uniformity corrections |	Shutterless, automatic (with scene motion); also compatible with external shutter|
|Image optimization |	Factory configured and fully automated|
|FOV - horizontal 	|25°|
|FOV - diagonal 		|	31°|
|Output format |	User-selectable 14-bit, 8-bit (AGC applied), or 24-bit RGB (AGC and colorization applied)|
|Solar protection	|			Integral|
|Package dimensions–socket version	|		8.5 × 8.5 × 8.6 mm (w × l × h)|
|Weight 	|	0.55 grams (typ)|
|Optimum |operating|
|temperature range	 |-10 °C to +65 °C|
|Non-operating temperature range|	-40 °C to +80 °C|
|Shock 	|1500 G @ 0.4 ms|

#### 3.1.2 Electrical Specifications
|Parameters|Detail|
|--------|--------|
|Input clock 	|25-MHz nominal, CMOS IO Voltage Levels|
|Video data interface |	Video over SPI|
|Control port 	|CCI (I2C-like), CMOS IO Voltage Levels|
|Input supply voltage (nominal) |	2.8 V, 1.2 V, 2.5 V to 3.1 V IO|
|Power dissipation |	Nominally 150 mW at room temperature (operating), 4 mW (standby)|

### 3.2 TFT Screen Specifications

#### 3.2.1 Basic Specifications
| Parameters|Detail  |
|--------|--------|
|Type|	TFT-type LCD screen|
|Screen size| 	1.77(inch)|
|Color| 	262k, colour|
|Brightness 	|100-250|
|Contrast ratio 	|300 : 1|
|Resolution 		|128*RGB*160|
|Pixel 	|128*160|
|Pitch		|0.18*0.18（mm）|
|Response time	|10(ms)|

#### 3.2.2 Electrical Specifications
| Parameters|Detail  |
|--------|--------|
|I/O Voltage (VDDI to DGND)	|1.65v~3.7v (VDDI ≤ VDD)|
|Analog Voltage (VDD to AGND)	|2.5V~4.8V|
|Operating current	(brightness lv1)|94 mA|
|Operating current	(brightness lv1)| 96 mA|
|Operating current	(brightness lv1)| 99 mA|
|Operating current	(brightness lv1)| 103 mA|


### 3.3 Battery

| Parameter| Typ| Unit|
|---|---|---|
| PN|603048||
| Capacity|900|mAh|
| Charge Current|400|mA|
|Charging time|2-3| hour|
|Battery life|8.5|hour	|
| Weight|17 |g|
|Charge Limit Voltge|4.2|V|
| Temperature Limit|Charging：0～45 Discharging：-20～60| °C|
| Humidity|≤90%|RH|

## 4 TROUBLE SHOTTING

