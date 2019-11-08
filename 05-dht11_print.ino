#include "DHT.h"

#define DHTPIN  2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test");
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();//读湿度
  float t = dht.readTemperature();//读温度(摄氏度)

  Serial.print("Humidity:");
  Serial.print(h);
  Serial.print("% Temperature:");
  Serial.print(t);
  Serial.println("℃");
  delay(2000);
}
