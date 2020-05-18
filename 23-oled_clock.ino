#include <DS1302.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET     4
Adafruit_SSD1306 oled(128, 64, &Wire, OLED_RESET);

DS1302 rtc(2, 3, 4); //对应DS1302的RST,DAT,CLK

int sec_temp;

void initRTCTime(void)//初始化RTC时钟
{
  rtc.writeProtect(false); //关闭写保护
  rtc.halt(false); //清除时钟停止标志
  Time t(2020, 4, 25, 21, 50, 50, 7); //新建时间对象 最后参数位星期数据，周日为1，周一为2以此类推
  rtc.time(t);//向DS1302设置时间数据
}

void updatTime()//打印时间数据
{
  Time tim = rtc.time(); //从DS1302获取时间数据
  char date[20];
  char timer[20];
  snprintf(date, sizeof(date), "%04d-%02d-%02d",
           tim.yr, tim.mon, tim.date);
  snprintf(timer, sizeof(timer), "%02d:%02d:%02d",
           tim.hr, tim.min, tim.sec);

  if (tim.sec != sec_temp) { //一秒刷新一次
    oled.clearDisplay();//清屏
    oled.setCursor(15, 2);//设置显示位置
    oled.println("--CLOCK--");
    oled.setCursor(4, 25);//设置显示位置
    oled.println(date);
    oled.setCursor(18, 50);//设置显示位置
    oled.println(timer);
    oled.display(); // 开显示
  }
  sec_temp = tim.sec;
}

void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(WHITE);//开像素点发光
  oled.clearDisplay();//清屏
  oled.setTextSize(2); //设置字体大小

  //新模块上电需要设置一次当前时间，
  //下载完成后需屏蔽此函数再次下载，否则每次上电都会初始化时间数据
  //  initRTCTime();

}

void loop() {
  updatTime();
}
