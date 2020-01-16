/*
   OLED_Menu
   摇杆操作OLED多级菜单
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

//定义按键结构体
typedef struct
{
  unsigned char index;
  unsigned char up;
  unsigned char down;
  unsigned char left;
  unsigned char right;
  void (*operation)(void);
} KEY_TABLE;

//定义日期时间结构体变量
struct
{
  unsigned char month;
  unsigned char day;
  unsigned char hour;
  unsigned char minute;
} date = {0};

unsigned char funIndex = 0;
void (*current)(void);
void menu11(void);
void menu12(void);
void menu21(void);
void menu22(void);
void menu23(void);
void menu31(void);
void menu32(void);
void menu33(void);
void menu34(void);

//定义按键操作数据
KEY_TABLE table[9] =
{
  {0, 0, 1, 0, 2, (*menu11)},
  {1, 0, 1, 1, 4, (*menu12)},
  {2, 2, 3, 0, 5, (*menu21)},
  {3, 2, 3, 0, 7, (*menu22)},
  {4, 4, 4, 1, 4, (*menu23)},
  {5, 5, 6, 2, 5, (*menu31)},
  {6, 5, 6, 2, 6, (*menu32)},
  {7, 7, 8, 3, 7, (*menu33)},
  {8, 7, 8, 3, 8, (*menu34)},
};

//一级菜单1
void menu11(void)
{
  display.clearDisplay();//清屏
  display.setTextSize(2); //设置字体大小
  display.setCursor(15, 2);//设置显示位置
  display.println("--Menu--");
  display.setCursor(2, 25);//设置显示位置
  display.println("->1.Tim");
  display.setCursor(2, 50);//设置显示位置
  display.println("  2.About");
  display.display(); // 开显示
}

//一级菜单2
void menu12(void)
{
  display.clearDisplay();//清屏
  display.setTextSize(2); //设置字体大小
  display.setCursor(15, 2);//设置显示位置
  display.println("--Menu--");
  display.setCursor(2, 25);//设置显示位置
  display.println("  1.Tim");
  display.setCursor(2, 50);//设置显示位置
  display.println("->2.About");
  display.display(); // 开显示
}

//二级菜单1
void menu21(void)
{
  display.clearDisplay();//清屏
  display.setTextSize(2); //设置字体大小
  display.setCursor(15, 2);//设置显示位置
  display.println("--Tim--");
  display.setCursor(2, 25);//设置显示位置
  display.println("->1.Date");
  display.setCursor(2, 50);//设置显示位置
  display.println("  2.Time");
  display.display(); // 开显示
}

//二级菜单2
void menu22(void)
{
  display.clearDisplay();//清屏
  display.setTextSize(2); //设置字体大小
  display.setCursor(15, 2);//设置显示位置
  display.println("--Tim--");
  display.setCursor(2, 25);//设置显示位置
  display.println("  1.Date");
  display.setCursor(2, 50);//设置显示位置
  display.println("->2.Time");
  display.display(); // 开显示
}

//二级菜单3
void menu23(void)
{
  display.clearDisplay();//清屏
  display.setTextSize(2); //设置字体大小
  display.setCursor(15, 2);//设置显示位置
  display.println("--About--");
  display.setCursor(2, 25);//设置显示位置
  display.println("Multi menu");
  display.setTextSize(1); //设置字体大小
  display.setCursor(70, 50);//设置显示位置
  display.println("-TonyCode");
  display.display(); // 开显示
}

//三级菜单1
void menu31(void)
{
  date.month++;
  display.clearDisplay();//清屏
  display.setTextSize(2); //设置字体大小
  display.setCursor(15, 2);//设置显示位置
  display.println("--Date--");
  display.setCursor(2, 25);//设置显示位置
  display.print("->M:  ");
  display.println(date.month);
  display.setCursor(2, 50);//设置显示位置
  display.print("  D:  ");
  display.println(date.day);
  display.display(); // 开显示

  if (date.month >= 12)
  {
    date.month = 0;
  }
}

//三级菜单2
void menu32(void)
{
  date.day++;
  display.clearDisplay();//清屏
  display.setTextSize(2); //设置字体大小
  display.setCursor(15, 2);//设置显示位置
  display.println("--Date--");
  display.setCursor(2, 25);//设置显示位置
  display.print("  M:  ");
  display.println(date.month);
  display.setCursor(2, 50);//设置显示位置
  display.print("->D:  ");
  display.println(date.day);
  display.display(); // 开显示

  if (date.day >= 31)
  {
    date.day = 0;
  }
}

//三级菜单3
void menu33(void)
{
  date.hour++;
  display.clearDisplay();//清屏
  display.setTextSize(2); //设置字体大小
  display.setCursor(15, 2);//设置显示位置
  display.println("--Time--");
  display.setCursor(2, 25);//设置显示位置
  display.print("->H:  ");
  display.println(date.hour);
  display.setCursor(2, 50);//设置显示位置
  display.print("  M:  ");
  display.println(date.minute);
  display.display(); // 开显示

  if (date.hour >= 24)
  {
    date.hour = 0;
  }
}

//三级菜单4
void menu34(void)
{
  date.minute++;
  display.clearDisplay();//清屏
  display.setTextSize(2); //设置字体大小
  display.setCursor(15, 2);//设置显示位置
  display.println("--Time--");
  display.setCursor(2, 25);//设置显示位置
  display.print("  H:  ");
  display.println(date.hour);
  display.setCursor(2, 50);//设置显示位置
  display.print("->M:  ");
  display.println(date.minute);
  display.display(); // 开显示

  if (date.minute >= 30)
  {
    date.minute = 0;
  }

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
  display.clearDisplay();//清屏 vc
  menu11();
}

void loop()
{
  keyValue = keyScan();

  if (keyValue != 0) //每发生一次有效按键就根据按键功能获取对应函数并执行
  {
    switch (keyValue)//获取按键对应序号
    {
      case 1: funIndex = table[funIndex].right; break;
      case 2: funIndex = table[funIndex].left; break;
      case 3: funIndex = table[funIndex].down; break;
      case 4: funIndex = table[funIndex].up; break;
    }
    current = table[funIndex].operation;//根据需要获取对应需要执行的函数
    (*current)();//执行获取到的函数
  }
}
