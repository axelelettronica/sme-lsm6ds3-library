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
	_status_sensor_value=XL_STATUS_BIT;
	_sensor_sensitivity=XL_Sens_2G;
	_sensor_control_registry=CTRL1_XL_REG_ADDRESS;
}

//Accelerometer supports all the power mode values
boolean LSM6DS3_Accelerometer::isValidPowerValue(PowerValues power_value){
	return true;
}

int LSM6DS3_Accelerometer::getXAxis()
{
	int value=readCombinedRegistry(OUTX_L_XL,OUTX_H_XL);
	return value*_sensor_sensitivity.value;
}
int LSM6DS3_Accelerometer::getYAxis()
{
	int value=readCombinedRegistry(OUTY_L_XL,OUTY_H_XL);
	return value*_sensor_sensitivity.value;
}
int LSM6DS3_Accelerometer::getZAxis()
{
	int value=readCombinedRegistry(OUTZ_L_XL,OUTZ_H_XL);
	return value*_sensor_sensitivity.value;
}

boolean LSM6DS3_Accelerometer::isValidSensitivity(Sensitivity sensitivity)
{
	return sensitivity.value>=XL_Sens_2G.value && sensitivity.value<=XL_Sens_16G.value;
}

LSM6DS3_Accelerometer accelerometer;
Sensitivity const XL_Sens_2G={0x00,0.061f};
Sensitivity const XL_Sens_4G={0x08,0.122f};
Sensitivity const XL_Sens_8G={0x0C,0.244f};
Sensitivity const XL_Sens_16G={0x04,0.488f};