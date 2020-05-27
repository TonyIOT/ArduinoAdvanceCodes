#include "Adafruit_APDS9960.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_APDS9960 apds;
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(WHITE);//开像素点发光
  oled.clearDisplay();//清屏
  oled.setTextSize(2); //设置字体大小

  apds.begin();
  apds.enableProximity(true);
  apds.enableGesture(true);
}

void loop() {

  uint8_t gesture = apds.readGesture();
  oled.clearDisplay();//清屏
  oled.setCursor(15, 2);//设置显示位置
  oled.println("APDS-9960");
  oled.setCursor(32, 40);//设置显示位置

  switch (gesture)
  {
    case APDS9960_UP: oled.println("[ Up ]"); break;
    case APDS9960_DOWN: oled.println("[Down]"); break;
    case APDS9960_LEFT: oled.println("[Left]"); break;
    case APDS9960_RIGHT: oled.println("[Right]"); break;
    default: oled.println("[----]"); break;
  }
  oled.display(); // 开显示
}
