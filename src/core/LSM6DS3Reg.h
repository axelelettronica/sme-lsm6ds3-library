 /*
 * LSM6DS3Reg.h
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


#ifndef LSM6DS3_REG_H_
#define LSM6DS3_REG_H_

#define LSM6DS3_ADDRESS				0x6A //Common for both accelerometer and gyroscope

#define WHO_AM_I_REG_ADDRESS		0x0F
#define WHO_AM_I_VALUE				0x69 //Fixed registry value

#define STATUS_REG_ADDRESS			0x1E //GDA & XLDA

/******* ACCELEROMETER *******/
#define CTRL1_XL_REG_ADDRESS		0x10 //Linear acceleration sensor control register 1 (r/w)
#define CTRL6_C_REG_ADDRESS			0x15 //Angular rate sensor control register 6 (r/w)
//X-Axis value
#define OUTX_L_XL					0x28
#define OUTX_H_XL					0x29
//Y-Axis Value
#define OUTY_L_XL					0x2A
#define OUTY_H_XL					0x2B
//Z-Axis Value
#define OUTZ_L_XL					0x2C
#define OUTZ_H_XL					0x2D

//high-performance operating mode disabled ( By default High Performance mode is enabled )
#define XL_HM_MODE_NORM_PERF		0x10 //Normal Mode ( CTRL6_C Registry )
#define XL_STATUS_BIT				0x01 //GDA

/******* GYROSCOPE	 *******/
#define CTRL2_G_REG_ADDRESS			0x11 //Angular rate sensor control register 2 (r/w).
#define CTRL7_G_REG_ADDRESS			0x16 //Angular rate sensor control register 7 (r/w).

//X value
#define OUTX_L_G					0x22
#define OUTX_H_G					0x23
//Y Value
#define OUTY_L_G					0x24
#define OUTY_H_G					0x25
//Z Value
#define OUTZ_L_G					0x26
#define OUTZ_H_G					0x27

//high-performance operating mode disabled ( By default High Performance mode is enabled )
#define G_HM_MODE_NORM_PERF			0x80 //Normal Mode ( CTRL7_G Registry )
#define G_STATUS_BIT				0x02 //XLDA


#endif /* INCFILE1_H_ */
