 /*
 * AccelerometerFunctions
 *
 *  Created on: 29/09/2016 23:02:00
 * by Zero-2 (Zero2sat@gmail.com)
 * 
 * License Information
 * -------------------
 *
 * Copyright (c) Axel Elettronica Srl. All right reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */
#include <Arduino.h>
#include "LSM6DS3.h"
#include "Wire.h"

void setup() {
	Wire.begin();
	SerialUSB.begin(115200);
	//Stop gyroscope if it's active
	gyroscope.powerOff();
}

void printMenu(){
	SerialUSB.println("Test Menu'");
	SerialUSB.println("Actions");
	SerialUSB.println("1 - PowerOn Sensor");
	SerialUSB.println("2 - PowerOff Sensor");
	SerialUSB.println("3 - Sensor Status");
	SerialUSB.println("4 - Print values");
	SerialUSB.println("Output Data Rate");
	SerialUSB.println("5 - Pass to 12,5Hz");
	SerialUSB.println("6 - Pass to 26Hz");
	SerialUSB.println("7 - Pass to 52Hz");
	SerialUSB.println("8 - Pass to 104Hz (Default)");
	SerialUSB.println("9 - Pass to 208Hz");
	SerialUSB.println("10 - Pass to 416Hz");
	SerialUSB.println("11 - Pass to 833Hz");
	SerialUSB.println("12 - Pass to 1,66KHz");
	SerialUSB.println("13 - Pass to 3,33Khz");
	SerialUSB.println("14 - Pass to 6,66Khz");
	SerialUSB.println("Full Scale");
	SerialUSB.println("15 - Pass to +/- 2G (Default)");
	SerialUSB.println("16 - Pass to +/- 4G");
	SerialUSB.println("17 - Pass to +/- 8G");
	SerialUSB.println("18 - Pass to +/- 16G");
	SerialUSB.println("Bandwidth");
	SerialUSB.println("19 - Pass to 50Hz");
	SerialUSB.println("20 - Pass to 100Hz");
	SerialUSB.println("21 - Pass to 200Hz");
	SerialUSB.println("22 - Pass to 400Hz (Default)");
	SerialUSB.println("Operating Mode");
	SerialUSB.println("23 - Pass Normal");
	SerialUSB.println("24 - High Performance (Default)");
	SerialUSB.println("Choose a command");
	while(Serial.available() == 0){}
	String read=SerialUSB.readString();
	int value=read.toInt();
	switch(value){
		case 1:
			SerialUSB.println("Power On");
			accelerometer.powerOn();
			break;
		case 2:
			SerialUSB.println("Power Off");
			accelerometer.powerOff();
			break;
		case 3:
			if(accelerometer.isActive()){
				SerialUSB.println("Accelerometer is Active");
			}else{
				SerialUSB.println("Accelerometer is not Active");
			}
			break;
		case 4:
			for(int i=1;i<=10;i++){
				SerialUSB.println("*********************************************");
				SerialUSB.print("Raw  X = ");
				SerialUSB.print(accelerometer.getRawXAxis(), DEC);
				SerialUSB.print("     Y = ");
				SerialUSB.print(accelerometer.getRawYAxis(), DEC);
				SerialUSB.print("     Z = ");
				SerialUSB.println(accelerometer.getRawZAxis(), DEC);
				SerialUSB.print(" X = ");
				SerialUSB.print(accelerometer.getRenderedXAxis(), DEC);
				SerialUSB.print("g Y = ");
				SerialUSB.print(accelerometer.getRenderedYAxis(), DEC);
				SerialUSB.print("g Z = ");
				SerialUSB.print(accelerometer.getRenderedZAxis(), DEC);
				SerialUSB.println("g");
				SerialUSB.println("*********************************************");
				delay(1000);
			}
			break;
		case 5:
			accelerometer.changeOutputDataRate(POWER_12_5_HZ);
			break;
		case 6:
			accelerometer.changeOutputDataRate(POWER_26_HZ);
			break;
		case 7:
			accelerometer.changeOutputDataRate(POWER_52_HZ);
			break;		
		case 8:
			accelerometer.changeOutputDataRate(POWER_104_HZ);
			break;
		case 9:
			accelerometer.changeOutputDataRate(POWER_208_HZ);
			break;
		case 10:
			accelerometer.changeOutputDataRate(POWER_416_HZ);
			break;
		case 11:
			accelerometer.changeOutputDataRate(POWER_833_HZ);
			break;
		case 12:
			accelerometer.changeOutputDataRate(POWER_1_66_KHZ);
			break;
		case 13:
			accelerometer.changeOutputDataRate(POWER_3_33_KHZ);
			break;
		case 14:
			accelerometer.changeOutputDataRate(POWER_6_66_KHZ);
			break;
		case 15:
			accelerometer.changeFullScale(XL_FS_2G);
			break;
		case 16:
			accelerometer.changeFullScale(XL_FS_4G);
			break;
		case 17:
			accelerometer.changeFullScale(XL_FS_8G);
			break;
		case 18:
			accelerometer.changeFullScale(XL_FS_16G);
			break;
		case 19:
			accelerometer.changeBandwidth(XL_Band_50Hz);
			break;
		case 20:
			accelerometer.changeBandwidth(XL_Band_100Hz);
			break;
		case 21:
			accelerometer.changeBandwidth(XL_Band_200Hz);
			break;
		case 22:
			accelerometer.changeBandwidth(XL_Band_400Hz);
			break;
		case 23:
			accelerometer.changeOperatingMode(XL_HM_Normal);
			break;
		case 24:
			accelerometer.changeOperatingMode(XL_HM_High_Performance);
			break;
		default:
			SerialUSB.println("Unknown Command");
	}
}

void loop() {
	printMenu();
}

