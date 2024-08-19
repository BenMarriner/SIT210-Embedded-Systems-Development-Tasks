/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/goolo/Desktop/BuddySystem/src/BuddySystem.ino"
/*
 * Project BuddySystem
 * Description: Waves to another particle device
 * Author: Ben Marriner (220253518)
 * Date: 9/05/2021
 */

void FlashLED();
void WaveHandler(const char *event, const char *data);
void setup();
void loop();
#line 8 "c:/Users/goolo/Desktop/BuddySystem/src/BuddySystem.ino"
const int LED_PIN = D12;

void FlashLED()
{
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}

void WaveHandler(const char *event, const char *data)
{
  int i = 0;
  while (i < 3)
  {
    FlashLED();
    i++;
  }
}

void setup() {
  Particle.subscribe("wave", WaveHandler);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {

}