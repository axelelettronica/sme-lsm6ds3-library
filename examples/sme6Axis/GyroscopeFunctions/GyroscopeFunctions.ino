 /*
 * GyroscopeFunctions.ino
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
	//Stop accelerometer if it's active
	accelerometer.powerOff();
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
	SerialUSB.println("Full Scale");
	SerialUSB.println("13 - Pass to 245dps (Default)");
	SerialUSB.println("14 - Pass to 500dps");
	SerialUSB.println("15 - Pass to 1000dps");
	SerialUSB.println("16 - Pass to 2000dps");
	SerialUSB.println("Operating Mode");
	SerialUSB.println("17 - Pass Normal");
	SerialUSB.println("18 - High Performance (Default)");
	SerialUSB.println("Choose a command");
	while(Serial.available() == 0){}
	String read=SerialUSB.readString();
	int value=read.toInt();
	switch(value){
		case 1:
			SerialUSB.println("Power On");
			gyroscope.powerOn();
			break;
		case 2:
			SerialUSB.println("Power Off");
			gyroscope.powerOff();
			break;
		case 3:
			if(gyroscope.isActive()){
				SerialUSB.println("Gyroscope is Active");
			}else{
				SerialUSB.println("Gyroscope is not Active");
			}
			break;
		case 4:
			for(int i=1;i<=10;i++){
				SerialUSB.println("*********************************************");
				SerialUSB.print("Raw  X = ");
				SerialUSB.print(gyroscope.getRawXAxis(), DEC);
				SerialUSB.print(" Y = ");
				SerialUSB.print(gyroscope.getRawYAxis(), DEC);
				SerialUSB.print(" Z = ");
				SerialUSB.println(gyroscope.getRawZAxis(), DEC);
				SerialUSB.print("X = ");
				SerialUSB.print(gyroscope.getRenderedXAxis(), DEC);
				SerialUSB.print("dps Y = ");
				SerialUSB.print(gyroscope.getRenderedYAxis(), DEC);
				SerialUSB.print("dps Z = ");
				SerialUSB.print(gyroscope.getRenderedZAxis(), DEC);
				SerialUSB.println("dps");
				SerialUSB.println("*********************************************");
				delay(1000);
			}
			break;
		case 5:
			gyroscope.changeOutputDataRate(POWER_12_5_HZ);
			break;
		case 6:
			gyroscope.changeOutputDataRate(POWER_26_HZ);
			break;
		case 7:
			gyroscope.changeOutputDataRate(POWER_52_HZ);
			break;		
		case 8:
			gyroscope.changeOutputDataRate(POWER_104_HZ);
			break;
		case 9:
			gyroscope.changeOutputDataRate(POWER_208_HZ);
			break;
		case 10:
			gyroscope.changeOutputDataRate(POWER_416_HZ);
			break;
		case 11:
			gyroscope.changeOutputDataRate(POWER_833_HZ);
			break;
		case 12:
			gyroscope.changeOutputDataRate(POWER_1_66_KHZ);
			break;
		case 13:
			gyroscope.changeFullScale(G_FS_245_DPS);
			break;
		case 14:
			gyroscope.changeFullScale(G_FS_500_DPS);
			break;
		case 15:
			gyroscope.changeFullScale(G_FS_1000_DPS);
			break;
		case 16:
			gyroscope.changeFullScale(G_FS_2000_DPS);
			break;
		case 17:
			gyroscope.changeOperatingMode(G_HM_Normal);
			break;
		case 18:
			gyroscope.changeOperatingMode(G_HM_High_Performance);
			break;
		default:
			SerialUSB.println("Unknown Command");
	}
}

void loop() {
	printMenu();
}

