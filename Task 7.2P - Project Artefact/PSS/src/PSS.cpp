/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Ben/Desktop/PSS/src/PSS.ino"
/*
 * Project PSS
 * Description: This is the firmware code for the Particle Argon that will runs the Perimeter Security System
 * Author: Ben Marriner
 * Date: 20/05/2021
 */

// LED Constants
void turnOnLED(int pin);
void turnOffLED(int pin);
void turnOffAllLEDs();
void toggleLED(int pin);
void buzz(double seconds);
void buzz();
void silence();
bool motionDetected(int sensorPin);
bool getSwitchState();
void toggleSystem();
void testHardware();
void initHardware();
void setup();
void loop();
#line 9 "c:/Users/Ben/Desktop/PSS/src/PSS.ino"
const int RED_LED_1 = D8;
const int RED_LED_2 = D7;
const int RED_LED_3 = D6;
const int BLUE_LED = D5;

const int LEDS[] = { RED_LED_1, RED_LED_2, RED_LED_3, BLUE_LED };
const int LEDS_SIZE = 4;

// Motion Sensor Constants
const int MOTION_SENSOR_1 = D11;
const int MOTION_SENSOR_2 = D12;
const int MOTION_SENSOR_3 = D13;

const int MOTION_SENSORS[] = { MOTION_SENSOR_1, MOTION_SENSOR_2, MOTION_SENSOR_3 };
const int MOTION_SENSORS_SIZE = 3;
const int MOTION_SENSOR_BAUD_RATE = 9600;

// Alarm Constants
const int ALARM_SWITCH = D4;
const int ALARM_BUZZER = D3;
const int ALARM_SOUND_FREQ = 1000;

// Button pressed state
bool lastButtonState = false;

// Is the alarm system activated/deactivated
bool sysEnabled = false;

// Turn on a specified LED
void turnOnLED(int pin)
{
  digitalWrite(pin, HIGH);
}

// Turn off a specified LED
void turnOffLED(int pin)
{
  digitalWrite(pin, LOW);
}

// Turn of all LEDs in the system
void turnOffAllLEDs()
{
  for (int i = 0; i < LEDS_SIZE; i++) turnOffLED(LEDS[i]);
}

// Toggle an LED between on and off
void toggleLED(int pin)
{
  if (digitalRead(pin) == HIGH) turnOffLED(pin);
  else turnOnLED(pin);
}

// Sound the alarm for the given number of seconds
void buzz(double seconds)
{
  tone(ALARM_BUZZER, ALARM_SOUND_FREQ, seconds * 1000);
}

// Sound the alarm indefinitely
void buzz()
{
  tone(ALARM_BUZZER, ALARM_SOUND_FREQ);
}

// Silence the alarm if it is buzzing
void silence()
{
  noTone(ALARM_BUZZER);
}

// Return true if motion is detected by the specified sensor
bool motionDetected(int sensorPin)
{
  return digitalRead(sensorPin) == HIGH;
}

// Returns the switch of the state such that the state will be true for only one loop
bool getSwitchState()
{
  return digitalRead(ALARM_SWITCH) == HIGH;
}

// Toggle the enabled state of the security system
void toggleSystem()
{
  sysEnabled = !sysEnabled;
}

// Test all the hardware connected to the system
void testHardware()
{
  // Testing LEDs
  for (int i = 0; i < LEDS_SIZE; i++)
  {
    turnOnLED(LEDS[i]);
    delay(250);
    turnOffLED(LEDS[i]);
  }

  // Testing alarm buzzer
  buzz(1);

  // Testing motion sensors
  Serial.begin(MOTION_SENSOR_BAUD_RATE);
  for (int i = 0; i < MOTION_SENSORS_SIZE; i++)
  {
    bool motion = motionDetected(MOTION_SENSORS[i]);
    
    Serial.print("Motion Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(motion ? "Motion detected" : "No motion detected");
    Serial.println();
  }
  Serial.end();
}

// Initialise Argon to correct pin modes
void initHardware()
{  
  for (int i = 0; i < LEDS_SIZE; i++)
  {
    pinMode(LEDS[i], OUTPUT);
    turnOffLED(LEDS[i]);
  }

  for (int i = 0; i < MOTION_SENSORS_SIZE; i++)
  {
    pinMode(MOTION_SENSORS[i], INPUT);
  }

  pinMode(ALARM_SWITCH, INPUT);
  pinMode(ALARM_BUZZER, OUTPUT);

  testHardware();
}

// Initialise hardware
void setup()
{
  initHardware();
}

void loop()
{
  // Toggle Alarm system state
  if (getSwitchState())
  {
    lastButtonState = !lastButtonState;
    toggleSystem();
  }
  while (getSwitchState()) delay(50);
  
  // Toggle blue light based on if the alarm system is on
  sysEnabled ? turnOnLED(BLUE_LED) : turnOffLED(BLUE_LED);

  // Procedure to execute if system is enabled/disabled
  if (sysEnabled)
  {
    // Check for motion from all sensors
    for (int i = 0; i < MOTION_SENSORS_SIZE; i++)
    {
      // Sound alarm if motion detected and turn on corresponding LED
      if (motionDetected(MOTION_SENSORS[i]))
      {
        buzz();
        turnOnLED(LEDS[i]);
      }
    }
  }
  // Switch off all LEDs and silence the alarm
  else
  {
    turnOffAllLEDs();
    silence();
  }
}