/*
    smeGyroscope Library - Localization Information

    This example print the 3Axis X,Y,Z information

    created 07 Oct 2016
    by Matteo Candido ()

    This example is in the public domain
    https://github.com/ameltech

    LSM6DS3  more information available here:
    http://www.st.com/content/st_com/en/products/mems-and-sensors/inemo-inertial-modules/lsm6ds3.html
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
    int x=gyroscope.getXAxis();
    int y=gyroscope.getYAxis();
    int z=gyroscope.getZAxis();
    SerialUSB.print("  X-Axis = ");
    SerialUSB.print(x, DEC);
    SerialUSB.print("  Y-Axis = ");
    SerialUSB.print(y, DEC);
    SerialUSB.print("  Z-Axis = ");
    SerialUSB.println(z, DEC);
    SerialUSB.println("++++++++++++++++++++++++++++++++++++++++");
    delay(1000);
}

