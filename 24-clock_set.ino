#include <DS1302.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

DS1302 rtc(2, 3, 4); //对应DS1302的RST,DAT,CLK


//摇杆相关变量
#define pinX  A0
#define pinY  A1

int valueX = 0;
int valueY = 0;
unsigned char keyValue = 0;

unsigned char menu = 0;

int sec_temp;
Time set_temp(2020, 4, 25, 21, 50, 50, 7);//用于存储正在修改的时间数据

//多级菜单相关变量
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

unsigned char funIndex = 0;
void (*current)(void);
void menu00(void);
void menu11(void);
void menu12(void);
void menu21(void);
void menu22(void);
void menu23(void);
void menu24(void);
void menu25(void);
void menu26(void);


//定义按键操作数据
KEY_TABLE table[9] =
{
  {0, 0, 0, 0, 1, (*menu00)},
  {1, 1, 2, 0, 3, (*menu11)},
  {2, 1, 2, 0, 6, (*menu12)},
  {3, 3, 4, 1, 3, (*menu21)},
  {4, 3, 5, 1, 4, (*menu22)},
  {5, 4, 5, 1, 5, (*menu23)},
  {6, 6, 7, 2, 6, (*menu24)},
  {7, 6, 8, 2, 7, (*menu25)},
  {8, 7, 8, 2, 8, (*menu26)},
};

void menu00(void)
{
  if (menu == 1)//从调时界面退出后将调节后的时间数据写入DS1302
  {
    initRTCTime(set_temp);
    menu = 0;
  }
  updatTime();
}

void menu11(void)
{
  menu = 1;//进入调时界面

  oled.clearDisplay();//清屏
  oled.setCursor(15, 2);//设置显示位置
  oled.println("-Set Dat-");
  oled.setCursor(2, 25);//设置显示位置
  oled.println("->1.Dat");
  oled.setCursor(2, 50);//设置显示位置
  oled.println("  2.Tim");
  oled.display(); // 开显示
}

void menu12(void)
{
  oled.clearDisplay();//清屏
  oled.setCursor(15, 2);//设置显示位置
  oled.println("-Set Tim-");
  oled.setCursor(2, 25);//设置显示位置
  oled.println("  1.Dat");
  oled.setCursor(2, 50);//设置显示位置
  oled.println("->2.Tim");
  oled.display(); // 开显示
}

void menu21(void)
{
  set_temp.yr++;
  oled.clearDisplay();//清屏
  oled.setCursor(2, 2);//设置显示位置
  oled.print("->Yer:");
  oled.println(set_temp.yr);
  oled.setCursor(2, 25);//设置显示位置
  oled.print("  Mon: ");
  oled.println(set_temp.mon);
  oled.setCursor(2, 48);//设置显示位置
  oled.print("  Day: ");
  oled.println(set_temp.date);
  oled.display(); // 开显示

  if (set_temp.yr >= 2030)
  {
    set_temp.yr = 2019;
  }
}

void menu22(void)
{
  set_temp.mon++;
  oled.clearDisplay();//清屏
  oled.setCursor(2, 2);//设置显示位置
  oled.print("  Yer:");
  oled.println(set_temp.yr);
  oled.setCursor(2, 25);//设置显示位置
  oled.print("->Mon: ");
  oled.println(set_temp.mon);
  oled.setCursor(2, 48);//设置显示位置
  oled.print("  Day: ");
  oled.println(set_temp.date);
  oled.display(); // 开显示

  if (set_temp.mon >= 12)
  {
    set_temp.mon = 0;
  }
}

void menu23(void)
{
  set_temp.date++;
  oled.clearDisplay();//清屏
  oled.setCursor(2, 2);//设置显示位置
  oled.print("  Yer:");
  oled.println(set_temp.yr);
  oled.setCursor(2, 25);//设置显示位置
  oled.print("  Mon: ");
  oled.println(set_temp.mon);
  oled.setCursor(2, 48);//设置显示位置
  oled.print("->Day: ");
  oled.println(set_temp.date);
  oled.display(); // 开显示

  if (set_temp.date >= 31)
  {
    set_temp.date = 0;
  }
}

void menu24(void)
{
  set_temp.hr++;
  oled.clearDisplay();//清屏
  oled.setCursor(2, 2);//设置显示位置
  oled.print("->Hor: ");
  oled.println(set_temp.hr);
  oled.setCursor(2, 25);//设置显示位置
  oled.print("  Min: ");
  oled.println(set_temp.min);
  oled.setCursor(2, 48);//设置显示位置
  oled.print("  Sec: ");
  oled.println(set_temp.sec);
  oled.display(); // 开显示

  if (set_temp.hr >= 24)
  {
    set_temp.hr = 0;
  }
}

void menu25(void)
{
  set_temp.min++;
  oled.clearDisplay();//清屏
  oled.setCursor(2, 2);//设置显示位置
  oled.print("  Hor: ");
  oled.println(set_temp.hr);
  oled.setCursor(2, 25);//设置显示位置
  oled.print("->Min: ");
  oled.println(set_temp.min);
  oled.setCursor(2, 48);//设置显示位置
  oled.print("  Sec: ");
  oled.println(set_temp.sec);
  oled.display(); // 开显示

  if (set_temp.min >= 60)
  {
    set_temp.min = 0;
  }
}

void menu26(void)
{
  set_temp.sec++;
  oled.clearDisplay();//清屏
  oled.setCursor(2, 2);//设置显示位置
  oled.print("  Hor: ");
  oled.println(set_temp.hr);
  oled.setCursor(2, 25);//设置显示位置
  oled.print("  Min: ");
  oled.println(set_temp.min);
  oled.setCursor(2, 48);//设置显示位置
  oled.print("->Sec: ");
  oled.println(set_temp.sec);
  oled.display(); // 开显示

  if (set_temp.sec >= 60)
  {
    set_temp.sec = 0;
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


void initRTCTime(Time t)//初始化RTC时钟
{
  rtc.writeProtect(false); //关闭写保护
  rtc.halt(false); //清除时钟停止标志
  rtc.time(t);//向DS1302设置时间数据
}

void show_time(Time tim)
{
  char date[20];
  char timer[20];
  snprintf(date, sizeof(date), "%04d-%02d-%02d",
           tim.yr, tim.mon, tim.date);
  snprintf(timer, sizeof(timer), "%02d:%02d:%02d",
           tim.hr, tim.min, tim.sec);

  oled.clearDisplay();//清屏
  oled.setCursor(15, 2);//设置显示位置
  oled.println("--CLOCK--");
  oled.setCursor(4, 25);//设置显示位置
  oled.println(date);
  oled.setCursor(18, 50);//设置显示位置
  oled.println(timer);
  oled.display(); // 开显示

}

void updatTime()//更新时间数据
{
  Time tim = rtc.time(); //从DS1302获取时间数据
  set_temp = tim;//获取时间数据已备调节
  if (tim.sec != sec_temp) { //一秒刷新一次
    show_time(tim);
  }
  sec_temp = tim.sec;
}



void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(WHITE);//开像素点发光
  oled.clearDisplay();//清屏
  oled.setTextSize(2); //设置字体大小
}



void loop() {
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

  if (menu == 0)//只有在首页才进行时间刷新
  {
    updatTime();
  }
}
