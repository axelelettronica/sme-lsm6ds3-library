 /*
 * LSM6DS3_Gyroscope.h
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
LSM6DS3_Gyroscope::LSM6DS3_Gyroscope()
{
	_status_sensor_value=G_STATUS_BIT;
	_sensor_sensitivity=G_Sens_245_DPS;
	_sensor_control_registry=CTRL2_G_REG_ADDRESS;
}

//Accelerometer supports all the power mode values
boolean LSM6DS3_Gyroscope::isValidPowerValue(PowerValues power_value){
	return power_value>=POWER_12_5_HZ && power_value<=POWER_1_66_KHZ;
}

int LSM6DS3_Gyroscope::getXAxis()
{
	int value=readCombinedRegistry(OUTX_L_G,OUTX_H_G);
	return value*_sensor_sensitivity.value;
}
int LSM6DS3_Gyroscope::getYAxis()
{
	int value=readCombinedRegistry(OUTY_L_G,OUTY_H_G);
	return value*_sensor_sensitivity.value;
}
int LSM6DS3_Gyroscope::getZAxis()
{
	int value=readCombinedRegistry(OUTZ_L_G,OUTZ_H_G);
	return value*_sensor_sensitivity.value;
}

boolean LSM6DS3_Gyroscope::isValidSensitivity(Sensitivity sensitivity)
{
	return sensitivity.value>=G_Sens_245_DPS.value && sensitivity.value<=G_Sens_2000_DPS.value;
}

LSM6DS3_Gyroscope gyroscope;
const Sensitivity G_Sens_245_DPS={0x00,8.75};
const Sensitivity G_Sens_500_DPS={0x04,17.50};
const Sensitivity G_Sens_1000_DPS={0x08,35};
const Sensitivity G_Sens_2000_DPS={0x0C,70};
