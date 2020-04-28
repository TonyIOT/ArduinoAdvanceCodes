#include <DS1302.h>

DS1302 rtc(2, 3, 4); //对应DS1302的RST,DAT,CLK

void initRTCTime(void)//初始化RTC时钟
{
  rtc.writeProtect(false); //关闭写保护
  rtc.halt(false); //清除时钟停止标志
  Time t(2020, 4, 25, 21, 50, 50, 7); //新建时间对象 最后参数位星期数据，周日为1，周一为2以此类推
  rtc.time(t);//向DS1302设置时间数据
}

void printTime()//打印时间数据
{
  Time tim = rtc.time(); //从DS1302获取时间数据
  char buf[50];
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
           tim.yr, tim.mon, tim.date,
           tim.hr, tim.min, tim.sec);

  Serial.println(buf);
}

void setup() {
  Serial.begin(9600);

  //新模块上电需要设置一次当前时间，
  //下载完成后需屏蔽此函数再次下载，否则每次上电都会初始化时间数据
  //  initRTCTime();

}

void loop() {
  printTime();
  delay(1000);
}
