/*
 * Project BuddySystem
 * Description: Waves to another particle device
 * Author: Ben Marriner (220253518)
 * Date: 9/05/2021
 */

const int LED_PIN = D3;

void FlashLED()
{
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}

void FlashLED(int delayTime)
{
  digitalWrite(LED_PIN, HIGH);
  delay(delayTime / 2);
  digitalWrite(LED_PIN, LOW);
  delay(delayTime / 2);
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

void PatHandler(const char *event, const char *data)
{
  int delayTime = 1000;

  while (delayTime >= 1)
  {
    FlashLED(delayTime);
    delayTime /= 2;
  }
}

void setup() {
  Particle.subscribe("wave", WaveHandler);
  Particle.subscribe("pat", PatHandler);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {

}