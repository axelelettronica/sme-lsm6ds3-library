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
	_sensorSettings.status_sensor_value=G_ENABLED;
	_sensorSettings.sensor_control_registry=CTRL2_G_REG_ADDRESS;
	_sensorSettings.power_mode_registry=CTRL7_G_REG_ADDRESS;
	_sensorSettings.operating_mode_reset_mask=G_OM_RESET_MASK;
	_sensorSettings.output_data_rate_reset_mask=G_ODR_RESET_MASK;
	_sensorSettings.full_scale_reset_mask=G_FS_RESET_MASK;
	_sensorSettings.axisRegistry.XAxis.lowRegistry=OUTX_L_G;
	_sensorSettings.axisRegistry.XAxis.highRegistry=OUTX_H_G;
	_sensorSettings.axisRegistry.YAxis.lowRegistry=OUTY_L_G;
	_sensorSettings.axisRegistry.YAxis.highRegistry=OUTY_H_G;
	_sensorSettings.axisRegistry.ZAxis.lowRegistry=OUTZ_L_G;
	_sensorSettings.axisRegistry.ZAxis.highRegistry=OUTZ_H_G;
	_sensorSettings.fullScale=G_FS_245_DPS;
	_sensorSettings.operatingMode=G_HM_High_Performance;
}

boolean LSM6DS3_Gyroscope::isValidFullScale(FullScale fs)
{
	return fs.range>=G_FS_245_DPS.range && fs.range<=G_FS_2000_DPS.range;
}


boolean LSM6DS3_Gyroscope::isValidOutputDataRate(OutputDataRate odr){
	return odr>=POWER_12_5_HZ && odr<=POWER_1_66_KHZ;
}

boolean LSM6DS3_Gyroscope::isValidOperatingMode(OperatingMode om){
	return om.bits==G_HM_Normal.bits || om.bits==G_HM_High_Performance.bits;
}

float LSM6DS3_Gyroscope::convertAxisValue(int value){
	FullScale fullScale=_sensorSettings.fullScale;
	return  (float)value *fullScale.full_scale_value / 1000;
}

LSM6DS3_Gyroscope gyroscope;
const OperatingMode G_HM_Normal={G_HM_NORMAL_MODE};
const OperatingMode G_HM_High_Performance={G_HM_HIGH_PERFORMANCE};
const FullScale G_FS_245_DPS={0x00,8.75,245};
const FullScale G_FS_500_DPS={0x04,17.50,500};
const FullScale G_FS_1000_DPS={0x08,35,1000};
const FullScale G_FS_2000_DPS={0x0C,70,2000};
