/*
   OLED_JoyStick
   摇杆控制OLED移动显示
*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET     4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);
#define pinX  A0
#define pinY  A1

//定义圆心和半径变量
int xCircle = 0;
int ycircle = 0;
int radius = 4;

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);//开像素点发光
  display.clearDisplay();//清屏
}

void loop()
{
  xCircle = map(analogRead(pinX), 1023, 0, radius, 128 - radius); //将X轴获取的AD值映射到oled的X显示方向
  ycircle = map(analogRead(pinY), 1023, 0, radius, 64 - radius); //将Y轴获取的AD值映射到oled的Y显示方向

  display.drawRect(0, 0, 128, 64, 1);//画矩形
  display.drawCircle(xCircle, ycircle , radius, 1); //画圆
  display.display();//开显示
  display.clearDisplay();//清屏
}
