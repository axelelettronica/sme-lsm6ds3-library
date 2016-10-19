/*
 * Gyroscope.ino
 *
 * Created on: 29/09/2016 23:02:00
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

#include <Arduino.h>
#include "LSM6DS3.h"
#include "Wire.h"

void setup() {
    Wire.begin();
    SerialUSB.begin(115200);    
    if(gyroscope.powerOn()){
        SerialUSB.println("Gyroscope Power ON");
    }else{
        SerialUSB.println("Gyroscope Not Powered On");
    }
}

void loop() {
    SerialUSB.println("++++++++++++++++++++++++++++++++++++++++");
    SerialUSB.println("Gyroscope Values ");
    SerialUSB.print("Raw  X = ");
    SerialUSB.print(gyroscope.getRawXAxis(), DEC);
    SerialUSB.print("  Y = ");
    SerialUSB.print(gyroscope.getRawYAxis(), DEC);
    SerialUSB.print("  Z = ");
    SerialUSB.println(gyroscope.getRawZAxis(), DEC);
    SerialUSB.print("X = ");
    SerialUSB.print(gyroscope.getConvertedXAxis(), DEC);
    SerialUSB.print("dms  Y = ");
    SerialUSB.print(gyroscope.getConvertedYAxis(), DEC);
    SerialUSB.print("dms  Z = ");
    SerialUSB.print(gyroscope.getConvertedZAxis(), DEC);
    SerialUSB.println("dms");
    SerialUSB.println("++++++++++++++++++++++++++++++++++++++++");
    delay(1000);
}

