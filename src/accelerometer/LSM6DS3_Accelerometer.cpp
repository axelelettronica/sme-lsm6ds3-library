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
	_sensorSettings.status_sensor_value=XL_ENABLED;
	_sensorSettings.sensor_control_registry=CTRL1_XL_REG_ADDRESS;
	_sensorSettings.power_mode_registry=CTRL6_C_REG_ADDRESS;
	_sensorSettings.operating_mode_reset_mask=XL_OM_RESET_MASK;
	_sensorSettings.output_data_rate_reset_mask=XL_ODR_RESET_MASK;
	_sensorSettings.full_scale_reset_mask=XL_FS_RESET_MASK;
	_sensorSettings.bandwidth_reset_mask=XL_BW_RESET_MASK;
	_sensorSettings.axisRegistry.XAxis.lowRegistry=OUTX_L_XL;
	_sensorSettings.axisRegistry.XAxis.highRegistry=OUTX_H_XL;
	_sensorSettings.axisRegistry.YAxis.lowRegistry=OUTY_L_XL;
	_sensorSettings.axisRegistry.YAxis.highRegistry=OUTY_H_XL;
	_sensorSettings.axisRegistry.ZAxis.lowRegistry=OUTZ_L_XL;
	_sensorSettings.axisRegistry.ZAxis.highRegistry=OUTZ_H_XL;
	_sensorSettings.bandwidth=XL_Band_400Hz;
	_sensorSettings.fullScale=XL_FS_2G;
	_sensorSettings.operatingMode=XL_HM_High_Performance;
}

boolean LSM6DS3_Accelerometer::changeBandwidth(Bandwidth bandwidth){
	if(isValidBandwidth(bandwidth))
	{
		uint8_t data=readRegister(CTRL1_XL_REG_ADDRESS);
		//Reset Bandwidth bits
		data&=_sensorSettings.bandwidth_reset_mask;
		//Set the new value
		data|=bandwidth.bits;
		writeRegister(CTRL1_XL_REG_ADDRESS,data);
		return true;
	}
	return false;
}

void LSM6DS3_Accelerometer::setManualBandwidthSelection(){
	uint8_t data=readRegister(CTRL4_C_REG_ADDRESS);
	data|=XL_BW_SCAL_ODR_MANUAL;
	writeRegister(CTRL4_C_REG_ADDRESS,data);
}

boolean LSM6DS3_Accelerometer::isValidFullScale(FullScale fs)
{
	return fs.range>=XL_FS_2G.range && fs.range<=XL_FS_16G.range;
}

boolean LSM6DS3_Accelerometer::isValidBandwidth(Bandwidth bandwidth){
	return bandwidth.value==XL_Band_400Hz.value || bandwidth.value==XL_Band_200Hz.value || bandwidth.value==XL_Band_100Hz.value || bandwidth.value==XL_Band_50Hz.value;
}

//Accelerometer supports all the power mode values
boolean LSM6DS3_Accelerometer::isValidOutputDataRate(OutputDataRate odr){
	return true;
}

boolean LSM6DS3_Accelerometer::isValidOperatingMode(OperatingMode om){
	return om.bits==XL_HM_Normal.bits || om.bits==XL_HM_High_Performance.bits;
}

void LSM6DS3_Accelerometer::customInit(){
	LSM6DS3::customInit();
	//Bandwidth determined by setting BW_XL[1:0] in CTRL1_XL (10h) register.)
	setManualBandwidthSelection();
	//Reset to default value
	changeBandwidth(_sensorSettings.bandwidth);
}

float LSM6DS3_Accelerometer::convertToFloatvalue(int value){
	FullScale fullScale=_sensorSettings.fullScale;
	return (float)value*fullScale.full_scale_value*(fullScale.range >> 1)/1000;
}

LSM6DS3_Accelerometer accelerometer;
const OperatingMode XL_HM_Normal={XL_HM_NORMAL_MODE};
const OperatingMode XL_HM_High_Performance={XL_HM_HIGH_PERFORMANCE};
const FullScale XL_FS_2G={0x00,0.061f,2};
const FullScale XL_FS_4G={0x08,0.122f,4};
const FullScale XL_FS_8G={0x0C,0.244f,8};
const FullScale XL_FS_16G={0x04,0.488f,16};
const Bandwidth XL_Band_400Hz={0x00,400};
const Bandwidth XL_Band_200Hz={0x01,200};
const Bandwidth XL_Band_100Hz={0x02,100};
const Bandwidth XL_Band_50Hz={0x03,50};