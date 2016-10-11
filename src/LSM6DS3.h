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

Output data rate values.
By default operating mode is in High Performance
For the accelerometer all the values are valid.
For the gyroscope the only valid values are in the range 12.5Hz-1.66Khz

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

//Sensitivity Struct
struct Sensitivity{
	byte bits; //Registry value
	float sensitivity; //Sensitivity value
	int range;
};

//Bandwidth struct
struct Bandwidth{
	byte bits; //Registry value
	int value; //Bandwidth value
};

//Support struct for internal operations
struct Axis{
	int x;
	int y;
	int z;
};

//Base class with common operations for both accelerometer and gyroscope sensor
class LSM6DS3
{
	public:
		LSM6DS3();
		~LSM6DS3() 
		{
			if(isActive())
			{
				powerOff();	
			}
		};

		/** Concrete methods **/

		//Check if sensor is active
		boolean isActive(){return _isActive;};
		//Move the sensor to power on state
		boolean powerOn(PowerValues power_value=POWER_104_HZ);
		//Move the sensor to power down state
		void powerOff();
		//Change sensor power value. This command, if sensor previously was active, power off the sensor, and then reactivate it 
		boolean changePowerValue(PowerValues powerValue);
		//Change the sensor sensitivity
		boolean changeSensitivity(Sensitivity sensitivity_bits);
		//Return the float converted X-Axis value
		float getFloatXAxis();
		//Return the float converted Y-Axis value
		float getFloatYAxis();
		//Return the float converted Z-Axis value
		float getFloatZAxis();

		/** Virtual Methods **/

		//Return the raw X-Axis value
		virtual int getRawXAxis()=0;
		//Return the raw Y-Axis value
		virtual int getRawYAxis()=0;
		//Return the raw Z-Axis value
		virtual int getRawZAxis()=0;

		
	protected:
		//Variables
		Axis		_axisValues;
		PowerValues _powerValue; //Actual sensor power value
		boolean		_isActive; //True if specific sensor is active , False if is in power down
		Sensitivity _sensor_sensitivity;//Sensor sensitivity
		byte		_status_sensor_value; //Value of the Status Registry for the specific sensor
		byte		_sensor_control_registry; //Address of the Status Registry for the specific sensor

		//Methods
		//Virtual Methods
		//Check if power value is valid or not for the specific sensor
		virtual boolean isValidPowerValue(PowerValues power_value)=0;
		//Check if sensitivity is valid or not for the specific sensor
		virtual boolean isValidSensitivity(Sensitivity sensitivity)=0;
		//Convert raw value to sensor specific float value
		virtual float convertToFloatvalue(int value)=0;
		//execute specific sensor initialization
		virtual void customInit()=0;
		//Concrete methods
		//Activate sensor
		boolean activate();
		//Deactivate sensor
		boolean deactivate();
		//Read value from registry
		byte readRegister( byte regToRead);
		//Write value to registry
		boolean writeRegister(byte regToWrite, byte dataToWrite);
		//Read 16bits value from two 8 bits registry
		boolean readCombinedRegistry(unsigned char lsb_registry,unsigned char msb_registry,int* value);

};

//Accelerometer class with specific sensor implementation
class LSM6DS3_Accelerometer: public LSM6DS3{
	public:
		LSM6DS3_Accelerometer();
		int getRawXAxis();
		int getRawYAxis();
		int getRawZAxis();
		//Change the bandwidth value
		boolean changeBandwidth(Bandwidth bandwidth);
	protected:
		boolean isValidPowerValue(PowerValues power_value);
		boolean isValidSensitivity(Sensitivity sensitivity);
		boolean isValidBandwidth(Bandwidth bandwidth);
		float convertToFloatvalue(int value);
		void setManualBandwidthSelection();
		void customInit();
	private:
		Bandwidth _bandwidth;
};

//Gyroscope class with specific sensor implementation
class LSM6DS3_Gyroscope: public LSM6DS3{
	public:
		LSM6DS3_Gyroscope();
		int getRawXAxis();
		int getRawYAxis();
		int getRawZAxis();
	protected:
		boolean isValidPowerValue(PowerValues power_value);
		boolean isValidSensitivity(Sensitivity sensitivity);
		float convertToFloatvalue(int value);
		void customInit();
};

extern LSM6DS3_Accelerometer accelerometer;
extern LSM6DS3_Gyroscope gyroscope;
//Gyroscope values
extern const Sensitivity G_Sens_245_DPS;
extern const Sensitivity G_Sens_500_DPS;
extern const Sensitivity G_Sens_1000_DPS;
extern const Sensitivity G_Sens_2000_DPS;
//Accelerometer values
extern const Sensitivity XL_Sens_2G;
extern const Sensitivity XL_Sens_4G;
extern const Sensitivity XL_Sens_8G;
extern const Sensitivity XL_Sens_16G;
extern const Bandwidth XL_Band_400Hz;
extern const Bandwidth XL_Band_200Hz;
extern const Bandwidth XL_Band_100Hz;
extern const Bandwidth XL_Band_50Hz;

#endif /* LSM6DS3_H */
