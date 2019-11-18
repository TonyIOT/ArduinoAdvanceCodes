#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "DHT.h"

#define DHTPIN  2
#define DHTTYPE DHT11

//iic驱动方式
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  u8g2.begin();
  dht.begin();
}

char h_str[3];
char t_str[3];
float h;
float t;

void loop() {

  h = dht.readHumidity();//读湿度
  t = dht.readTemperature();//读温度(摄氏度)
  strcpy(h_str, u8x8_u8toa(h, 2));    /* convert m to a string with two digits */
  strcpy(t_str, u8x8_u8toa(t, 2));    /* convert m to a string with two digits */

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_fur20_tf);
    u8g2.drawStr(0, 23, "T");
    u8g2.drawStr(20, 23, ":");
    u8g2.drawStr(40, 23, t_str);
    u8g2.drawStr(90, 23, "C");

    u8g2.drawStr(0, 63, "H");
    u8g2.drawStr(20, 63, ":");
    u8g2.drawStr(40, 63, h_str);
    u8g2.drawStr(90, 63, "%");
  } while ( u8g2.nextPage() );
  delay(1000);
}
