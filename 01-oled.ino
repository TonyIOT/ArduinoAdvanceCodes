/*
 * OLED显示
 */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET     4
Adafruit_SSD1306 display(128, 64, &Wire,OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.setTextColor(WHITE);//开像素点发光
  display.clearDisplay();//清屏
  
  display.setTextSize(1); //设置字体大小  
  display.setCursor(35, 5);//设置显示位置
  display.println("-TonyCode-");

  display.setTextSize(2);//设置字体大小  
  display.setCursor(15, 30);//设置显示位置
  display.println("OLED TEST");
  
  display.display(); // 开显示
 
}

void loop() {

}
