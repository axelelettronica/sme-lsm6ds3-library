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

int LSM6DS3::readCombinedRegistry(unsigned char lsb_registry,unsigned char msb_registry){
	//Final value is signed int
	int value=0;
	signed char readValue;
	//Do almost 10 tentatives
	for(int i=0;i<CHECK_STATUS_RETRIES;i++){
		//First read the status	
		readValue=readRegister(STATUS_REG_ADDRESS);
		//If data is available, read it
		if(readValue & _status_sensor_value){
			//Read the LSB
			readValue=readRegister(lsb_registry);
			value=readValue;
			//Then the MSB
			readValue=readRegister(msb_registry);
			//Join the value into a signed int
			value=readValue<<8;
			break;
		}else{
			delay(1);
		}
	}
	return value;
}

// Read a single byte from addressToRead and return it as a byte
byte LSM6DS3::readRegister(byte regToRead)
{
	Wire.beginTransmission(LSM6DS3_ADDRESS);
	Wire.write(regToRead);
	Wire.endTransmission(false); //endTransmission but keep the connection active

	Wire.requestFrom(LSM6DS3_ADDRESS, 1); //Ask for 1 byte, once done, bus is released by default

	while(!Wire.available()) ; //Wait for the data to come back
	return Wire.read(); //Return this one byte
}

// Writes a single byte (dataToWrite) into regToWrite
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

void LSM6DS3::powerDown(){
	if(isActive()){
		deactivate();
	}
}
