/*
   OLED_Key
   摇杆按键操作OLED
*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET     4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

#define pinX  A0
#define pinY  A1

int valueX = 0;
int valueY = 0;
unsigned char keyValue = 0;
int value = 0;


void menu(unsigned char index)
{
  display.clearDisplay();//清屏
  display.setCursor(20, 2);//设置显示位置
  display.println("--KEY--");
  display.setCursor(2, 35);//设置显示位置

  if (index == 1)
  {
    display.print("R:  [");
    value = value - 1;
  } else if (index == 2)
  {
    display.print("L:  [");
    value = value + 1;
  } else if (index == 3)
  {
    display.print("D:  [");
    value = value - 10;
  }
  else if (index == 4)
  {
    display.print("U:  [");
    value = value + 10;
  }

  if (value >= 100)
  {
    value = 100;
  }
  if (value <= 0)
  {
    value = 0;
  }
  display.print(value);
  display.print("]");
  display.display(); // 开显示

}

//按键扫描函数
unsigned char keyScan(void)
{
  static unsigned char keyUp = 1;

  valueX = analogRead(pinX);
  valueY = analogRead(pinY);

  if (keyUp && ((valueX <= 10) || (valueX >= 1010) || (valueY <= 10) || (valueY >= 1010)))
  {
    delay(10);
    keyUp = 0;
    if (valueX <= 10)return 1;
    else if (valueX >= 1010)return 2;
    else if (valueY <= 10)return 3;
    else if (valueY >= 1010)return 4;
  } else if ((valueX > 10) && (valueX < 1010) && (valueY > 10) && (valueY < 1010))keyUp = 1;
  return 0;
}

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);//开像素点发光
  display.clearDisplay();//清屏
  display.setTextSize(2); //设置字体大小
  display.setCursor(20, 2);//设置显示位置
  display.println("--KEY--");
  display.display(); // 开显示
}

void loop()
{
  keyValue = keyScan();

  if (keyValue != 0)
  {
    menu(keyValue);
  }
}
