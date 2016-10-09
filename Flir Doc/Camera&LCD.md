# 摄像头及底座 Flir Camera and Socket
08/10/2016

## 1 Flir摄像机 Flir Camera

### 1.1 基本规格 Basic Specification

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

### 1.2 电气特性 Electrical Specification
|Parameters|Detail|
|--------|--------|
|Input clock 	|25-MHz nominal, CMOS IO Voltage Levels|
|Video data interface |	Video over SPI|
|Control port 	|CCI (I2C-like), CMOS IO Voltage Levels|
|Input supply voltage (nominal) |	2.8 V, 1.2 V, 2.5 V to 3.1 V IO|
|Power dissipation |	Nominally 150 mW at room temperature (operating), 4 mW (standby)|


##	2 Camera Socket

### 2.1 基本规格 Basic Specification
| Parameters|Detail  |
|--------|--------|
|Circuits (Loaded) 	|	32|
|Color - Resin	|Black|
|Durability (mating cycles max) |			20|
|Entry Angle |	Vertical|
|Keying to Mating Part| 	Yes|
|Material - Metal |	Copper Alloy|
|Material - Plating Mating| 	Gold|
|Material - Plating Termination |	Gold|
|Material - Resin| 	Liquid Crystal Polymer|
|Net Weight |	0.355/g|
|PCB Retention	|N/A|
|PCB Thickness - Recommended |	1.00mm|
|Packaging Type|	Embossed Tape on Reel|
|Pitch - Mating Interface 	|0.90mm|
|Pitch - Termination Interface |	0.90mm|
|Temperature Range - Operating |	-55°C to +85°C|
|	Package dimensions		|	10.6 × 10.6 × 4.2 mm (w × l × h)|

### 2.2 电气特性 Electrical Specification
| Parameters|Detail  |
|--------|--------|
|Current - Maximum per Contact 	|0.5A|
|Voltage - Maximum 	|50V DC|
|Circuits (Loaded) 	|	32|
|Color - Resin	|Black|
|Durability (mating cycles max) |			20|
|Entry Angle |	Vertical|
|Keying to Mating Part| 	Yes|
|Material - Metal |	Copper Alloy|
|Material - Plating Mating| 	Gold|
|Material - Plating Termination |	Gold|
|Material - Resin| 	Liquid Crystal Polymer|
|Net Weight |	0.355/g|
|PCB Retention	|N/A|
|PCB Thickness - Recommended |	1.00mm|
|Packaging Type|	Embossed Tape on Reel|
|Pitch - Mating Interface 	|0.90mm|
|Pitch - Termination Interface |	0.90mm|
|Temperature Range - Operating |	-55°C to +85°C|
|	Package dimensions		|	10.6 × 10.6 × 4.2 mm (w × l × h)|


## 2.3 特殊情况 Trouble Shotting
### 接触问题 Contact
如果Flir摄像头模块与接口有接触问题，可能会导致下述情况。If it doesn't contact well, it may cause the following questions:
* 设备持续重启，无法正常开机。这是由于SPI通讯接口接触不良导致的。Device entry boot loop and not able to functional. It is caused by the SPI's pins contact fault or the power's pins or some other pins.
* 显示失真。这是由于I2C通讯接口接触不良导致的。Display distortion. It is caused by the I2C pins contact fault.

可以尝试将Flir摄像头模块拔出后重新插入来修复连接问题。但大多数情况下需要更换PCB上的摄像头接口。To fix the contact problem, user can pull out the camera from the socket and reinstall it. However, in most case, this problem needs to be fixed by replacing the socket on PCB.

# 3 屏幕 Screen
## 3.1 基本特性 Basic Specification
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

## 3.2 电气特性 Electrical Specification
| Parameters|Detail  |
|--------|--------|
|I/O Voltage (VDDI to DGND)	|1.65v~3.7v (VDDI ≤ VDD)|
|Analog Voltage (VDD to AGND)	|2.5V~4.8V|
|Operating current	(brightness lv1)|94 mA|
|Operating current	(brightness lv1)| 96 mA|
|Operating current	(brightness lv1)| 99 mA|
|Operating current	(brightness lv1)| 103 mA|

## 3.3 特殊情况 Trouble Shotting
### 排线接触问题 Cable contact problems
屏幕不亮或者屏幕闪烁。检查排线及连接软板完好以排除问题。Screen off or screen flicker and flash. Check screen cable and flex cable to solve this problem.

