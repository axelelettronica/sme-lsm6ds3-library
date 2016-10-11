 /*
 * LSM6DS3_Accelerometer.h
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
#include "../core/LSM6DS3Reg.h"

//Accelerometer class
LSM6DS3_Accelerometer::LSM6DS3_Accelerometer()
{
	_status_sensor_value=XL_ENABLED;
	_sensor_sensitivity=XL_Sens_2G;
	_sensor_control_registry=CTRL1_XL_REG_ADDRESS;
	_bandwidth=XL_Band_400Hz;
}

boolean LSM6DS3_Accelerometer::changeBandwidth(Bandwidth bandwidth){
	if(isValidBandwidth(bandwidth))
	{
		uint8_t data=readRegister(CTRL4_C_REG_ADDRESS);
		//Reset Sensitivity bits
		data&=~bandwidth.bits;
		_bandwidth=bandwidth;
		//Set the new value
		data|=bandwidth.bits;
		writeRegister(CTRL4_C_REG_ADDRESS,data);
		return true;
	}
	return false;
}

int LSM6DS3_Accelerometer::getRawXAxis()
{
	 int data=0;
	 if(readCombinedRegistry(OUTX_L_XL,OUTX_H_XL,&data)){
		 _axisValues.x=data;
	 }
	 return _axisValues.x;
}
int LSM6DS3_Accelerometer::getRawYAxis()
{
	 int data=0;
	 if(readCombinedRegistry(OUTY_L_XL,OUTY_H_XL,&data)){
		 _axisValues.y=data;
	 }
	 return _axisValues.y;
}
int LSM6DS3_Accelerometer::getRawZAxis()
{
	 int data=0;
	 if(readCombinedRegistry(OUTZ_L_XL,OUTZ_H_XL,&data)){
		 _axisValues.z=data;
	 }
	 return _axisValues.z;
}

void LSM6DS3_Accelerometer::setManualBandwidthSelection(){
	uint8_t data=readRegister(CTRL4_C_REG_ADDRESS);
	data|=XL_BW_SCAL_ODR_MANUAL;
	writeRegister(CTRL4_C_REG_ADDRESS,data);
}

boolean LSM6DS3_Accelerometer::isValidSensitivity(Sensitivity sensitivity)
{
	return sensitivity.range>=XL_Sens_2G.range && sensitivity.range<=XL_Sens_16G.range;
}

boolean LSM6DS3_Accelerometer::isValidBandwidth(Bandwidth bandwidth){
	return bandwidth.value==XL_Band_400Hz.value || bandwidth.value==XL_Band_200Hz.value || bandwidth.value==XL_Band_100Hz.value || bandwidth.value==XL_Band_50Hz.value;
}

//Accelerometer supports all the power mode values
boolean LSM6DS3_Accelerometer::isValidPowerValue(PowerValues power_value){
	return true;
}

void LSM6DS3_Accelerometer::customInit(){
	//Bandwidth determined by setting BW_XL[1:0] in CTRL1_XL (10h) register.)
	setManualBandwidthSelection();
}

float LSM6DS3_Accelerometer::convertToFloatvalue(int value){
	return (float)value*_sensor_sensitivity.sensitivity*(_sensor_sensitivity.range >> 1)/1000;
}

LSM6DS3_Accelerometer accelerometer;
Sensitivity const XL_Sens_2G={0x00,0.061f,2};
Sensitivity const XL_Sens_4G={0x08,0.122f,4};
Sensitivity const XL_Sens_8G={0x0C,0.244f,8};
Sensitivity const XL_Sens_16G={0x04,0.488f,16};
Bandwidth const XL_Band_400Hz={0x00,400};
Bandwidth const XL_Band_200Hz={0x01,200};
Bandwidth const XL_Band_100Hz={0x02,100};
Bandwidth const XL_Band_50Hz={0x03,50};