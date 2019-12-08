/*
   MQ-2烟雾传感器的使用
*/

#include <Arduino.h>

#define Sensor_AO A0
#define Sensor_DO 2

unsigned int sensorValue = 0;

void setup()
{
  pinMode(Sensor_DO, INPUT);
  Serial.begin(9600);
}

void loop()
{
  sensorValue = analogRead(Sensor_AO);
  Serial.print("Sensor AD Value = ");
  Serial.println(sensorValue);

  if (digitalRead(Sensor_DO) == LOW)
  {
    Serial.println("Alarm!");
  }
  delay(1000);
}
