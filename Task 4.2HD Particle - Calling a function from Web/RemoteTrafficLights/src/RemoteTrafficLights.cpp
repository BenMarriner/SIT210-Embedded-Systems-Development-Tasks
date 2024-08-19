/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/goolo/Desktop/RemoteTrafficLights/RemoteTrafficLights/src/RemoteTrafficLights.ino"
/*
 * Project RemoteTrafficLights
 * Description: Code for controlling traffic lights remotely on a particle device
 * Author: Ben Marriner (220253518)
 * Date: 9/05/2020
 */

bool ToggleLight(int pinIdx);
bool ToggleLight(int pinIdx, bool state);
void TurnOffAllLights();
void TestLights();
int DoToggleLight(String light);
void setup();
void loop();
#line 8 "c:/Users/goolo/Desktop/RemoteTrafficLights/RemoteTrafficLights/src/RemoteTrafficLights.ino"
const int LED_PINS_SIZE = 3;
const int LED_PINS[LED_PINS_SIZE] = {D7, D6, D5};

// Switch on/off a light if current state isn't known
bool ToggleLight(int pinIdx)
{
  if (digitalRead(LED_PINS[pinIdx]) == HIGH)
  {
    digitalWrite(LED_PINS[pinIdx], LOW);
    return false;
  }
  else
  {
    digitalWrite(LED_PINS[pinIdx], HIGH);
    return true;
  }

  return false;
}

// Switch on/off a light
bool ToggleLight(int pinIdx, bool state)
{
  digitalWrite(LED_PINS[pinIdx], state ? HIGH : LOW);
  return state;
}

// Turn off all lights at once
void TurnOffAllLights()
{
  for (int i = 0; i < LED_PINS_SIZE; i++) ToggleLight(i, false);
}

void TestLights()
{
  // Switch off all lights first
  TurnOffAllLights();
  // Then turn them on one by one
  for (int i = 0; i < LED_PINS_SIZE; i++)
  {
    digitalWrite(LED_PINS[i], HIGH);
    delay(500);
  }
  // Turn them off again
  TurnOffAllLights();
}

// Cloud function
int DoToggleLight(String light)
{
  Serial.print("Received args: ");
  Serial.print(light);
  Serial.println();
  
  // Red light
  if (light == "red") return ToggleLight(0);
  // Green light
  else if (light == "green") return ToggleLight(1);
  // Blue light
  else if (light == "blue") return ToggleLight(2);
  // Function was called with an invalid light string
  else return -1;
}

void setup() {
  Particle.function("togglelight", DoToggleLight);
  Serial.begin();
  
  for (int i = 0; i < LED_PINS_SIZE; i++)
  {
    pinMode(LED_PINS[i], OUTPUT);
  }
  TestLights();
}

void loop() {
  
}