/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Ben/Desktop/IFTTT/IFTTT.ino"
#include <BH1750Lib.h>

void setup();
void loop();
#line 3 "c:/Users/Ben/Desktop/IFTTT/IFTTT.ino"
BH1750Lib sensor;
int lux;

void setup()
{
    Particle.variable("Luminosity", &lux, INT);
    sensor.begin(BH1750LIB_MODE_CONTINUOUSHIGHRES2);
    Serial.begin(9600);
}

void loop()
{
    Serial.print(lux);
    Serial.print(" lx");
    Serial.println();

    delay(1000);
}