 /*
 * LSM6DS3.h
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

#ifndef LSM6DS3_SENSOR_H_
#define LSM6DS3_SENSOR_H_

#include <Arduino.h>
#include <stdbool.h>
#include <stdint-gcc.h>

#define CHECK_STATUS_RETRIES 10

/*
+------------------------------+--------------------------------+
|		 A/XL_HM_MODE = 1      |	A/XL_HM_MODE = 0 (default)	|
+------------------------------+--------------------------------+
|  12.5 Hz (low power)         |   12.5 Hz (high performance)   |
|  26 Hz (low power)           |   26 Hz (high performance)     |
|  52 Hz (low power)		   |   52 Hz (high performance)     |
|  104 Hz (normal mode)		   |   104 Hz (high performance)    |
|  208 Hz (normal mode)		   |   208 Hz (high performance)    |
|  416 Hz (high performance)   |   416 Hz (high performance)    |
|  833 Hz (high performance)   |   833 Hz (high performance)    |
|  1.66 kHz (high performance) |   1.66 kHz (high performance)  |
|  3.33 kHz (high performance) |   3.33 kHz (high performance)  |
|  6.66 kHz (high performance) |   6.66 kHz (high performance)  |
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
enum PowerValues {
	POWER_12_5_HZ=0x10,
	POWER_26_HZ=0x20,
	POWER_52_HZ=0x30,
	POWER_104_HZ=0x40,
	POWER_208_HZ=0x50,
	POWER_416_HZ=0x60,
	POWER_833_HZ=0x70,
	POWER_1_66_KHZ=0x80,
	POWER_3_33_KHZ=0x90,
	POWER_6_66_KHZ=0xA0
};

struct Sensitivity{
	byte bits; //FS_XL [1:0] CTRL1_XL Registry
	float value;
};

class LSM6DS3
{
	public:
		LSM6DS3();
		~LSM6DS3() 
		{
			if(isActive())
			{
				powerDown();	
			}
		};
		//Check if sensor is active
		boolean isActive(){return _isActive;};
		//Initialize sensor
		boolean powerOn(PowerValues power_value=POWER_104_HZ);
		//Change current power value to the new value. 
		//Steps are: deactivate, change value and then activate.
		boolean changePowerValue(PowerValues powerValue);
		boolean changeSensitivity(Sensitivity sensitivity_bits);
		void powerDown();
		//Return X-Axis value
		virtual int getXAxis()=0;
		//Return Y-Axis value
		virtual int getYAxis()=0;
		//Return Z-Axis value
		virtual int getZAxis()=0;
		
	protected:
		//Variables
		PowerValues _powerValue; //Actual sensor power value
		boolean		_isActive; //True if specific sensor is active , False if is in power down
		Sensitivity _sensor_sensitivity;//Sensor sensitivity
		byte		_status_sensor_value; //Value of the Status Registry for the specific sensor
		byte		_sensor_control_registry; //Address of the Status Registry for the specific sensor
		//Methods
		virtual boolean isValidPowerValue(PowerValues power_value)=0;
		virtual boolean isValidSensitivity(Sensitivity sensitivity)=0;
		boolean activate();
		boolean deactivate();
		byte readRegister( byte regToRead);
		boolean writeRegister(byte regToWrite, byte dataToWrite);
		int readCombinedRegistry(unsigned char lsb_registry,unsigned char msb_registry);

		
};


class LSM6DS3_Accelerometer: public LSM6DS3{
	public:
		LSM6DS3_Accelerometer();
		int getXAxis();
		int getYAxis();
		int getZAxis();
	protected:
		boolean isValidPowerValue(PowerValues power_value);
		boolean isValidSensitivity(Sensitivity sensitivity);
};

class LSM6DS3_Gyroscope: public LSM6DS3{
	public:
		LSM6DS3_Gyroscope();
		int getXAxis();
		int getYAxis();
		int getZAxis();
	protected:
		boolean isValidPowerValue(PowerValues power_value);
		boolean isValidSensitivity(Sensitivity sensitivity);
};

extern LSM6DS3_Accelerometer accelerometer;
extern LSM6DS3_Gyroscope gyroscope;
//Sensitivity values for Gyroscope
extern const Sensitivity G_Sens_245_DPS;
extern const Sensitivity G_Sens_500_DPS;
extern const Sensitivity G_Sens_1000_DPS;
extern const Sensitivity G_Sens_2000_DPS;
//Sensitivity values for Accelerometer
extern const Sensitivity XL_Sens_2G;
extern const Sensitivity XL_Sens_4G;
extern const Sensitivity XL_Sens_8G;
extern const Sensitivity XL_Sens_16G;

#endif /* LSM6DS3_H */
