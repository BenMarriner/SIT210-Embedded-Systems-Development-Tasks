#include <BH1750Lib.h>

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
    lux = sensor.lightLevel();

    Serial.print(lux);
    Serial.print(" lx");
    Serial.println();

    delay(1000);
}