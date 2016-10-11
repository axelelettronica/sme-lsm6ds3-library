 /*
 * LSM6DS3.cpp
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

#include "Wire.h"
#include "LSM6DS3.h"
#include "LSM6DS3Reg.h"

LSM6DS3::LSM6DS3() 
{
	_axisValues.x=0;
	_axisValues.y=0;
	_axisValues.z=0;
}

boolean LSM6DS3::activate(){
	uint8_t data=readRegister(_sensor_control_registry);
	data|=_powerValue;
	writeRegister(_sensor_control_registry,data);
	_isActive=true;
	return true;
}

boolean LSM6DS3::deactivate(){
	uint8_t data=readRegister(_sensor_control_registry);
	data&=~_powerValue;
	writeRegister(_sensor_control_registry,data);
	_isActive=false;
	return true;
}

boolean LSM6DS3::readCombinedRegistry(unsigned char lsb_registry,unsigned char msb_registry,int* value){
	 uint16_t data = 0;
	 unsigned char  read = 0;
	 int16_t signed_data = 0;

	 for (int i=0;i<CHECK_STATUS_RETRIES;i++) {
		 read = readRegister(STATUS_REG_ADDRESS);
		 if (read & _status_sensor_value) {
			 read = readRegister(lsb_registry);
			 data = read;      // LSB

			 read = readRegister(msb_registry);
			 data |= read << 8; // MSB
			 signed_data = data;
			 *value=  signed_data;
			 return true;
		} else {
			 delay (1);
		 }
	 }
	 return false;
}

byte LSM6DS3::readRegister(byte regToRead)
{
	Wire.beginTransmission(LSM6DS3_ADDRESS);
	Wire.write(regToRead);
	Wire.endTransmission(false); //endTransmission but keep the connection active

	Wire.requestFrom(LSM6DS3_ADDRESS, 1); //Ask for 1 byte, once done, bus is released by default

	while(!Wire.available()) ; //Wait for the data to come back
	return Wire.read(); //Return this one byte
}

boolean LSM6DS3::writeRegister(byte regToWrite, byte dataToWrite)
{
	uint8_t errorNo;
	Wire.beginTransmission(LSM6DS3_ADDRESS);

	if (!Wire.write(regToWrite)) {
		return false;
	}
	if (!Wire.write(dataToWrite)) {
		return false;
	}

	errorNo = Wire.endTransmission(); //Stop transmitting
	return (errorNo == 0);
}

boolean LSM6DS3::powerOn(PowerValues power_value){
	boolean result=false;
	if(!isActive() && isValidPowerValue(power_value)){
		uint8_t data=readRegister(WHO_AM_I_REG_ADDRESS);
		if(data==WHO_AM_I_VALUE){
			_powerValue=power_value;
			activate();
			result=true;
		}
	}
	return result;
}

boolean LSM6DS3::changePowerValue(PowerValues powerValue)
{
	bool result=false;
	if(isValidPowerValue(powerValue)){
		bool wasActive=isActive();
		if(wasActive){
			deactivate();
		}
		_powerValue=powerValue;
		if(wasActive){
			result=activate();
		}else{
			result=true;
		}
	}
	return result;
}

boolean LSM6DS3::changeSensitivity(Sensitivity sensitivity){
	if(isValidSensitivity(sensitivity))
	{
		uint8_t data=readRegister(_sensor_control_registry);
		//Reset Sensitivity bits
		data&=~_sensor_sensitivity.bits;
		_sensor_sensitivity=sensitivity;
		//Set the new value
		data|=_sensor_sensitivity.bits;
		writeRegister(_sensor_control_registry,data);
		return true;
	}
	return false;
}

void LSM6DS3::powerOff(){
	if(isActive()){
		deactivate();
	}
}

float LSM6DS3::getFloatXAxis(){
	int value=getRawXAxis();
	return convertToFloatvalue(value);
}

float LSM6DS3::getFloatYAxis(){
	int value=getRawYAxis();
	return convertToFloatvalue(value);
}

float LSM6DS3::getFloatZAxis(){
	int value=getRawZAxis();
	return convertToFloatvalue(value);
}
