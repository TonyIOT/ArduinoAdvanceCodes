/*
   OLED_BH1750
   光照传感器OLED背光控制
*/

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h> 

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);//使用硬件IIC

int BH1750address = 0x23;
byte buff[2];
uint16_t val = 0;
char str[6];

void setup()
{
  Wire.begin();
  BH1750_Init(BH1750address);
  u8g2.begin();
  u8g2.setFont(u8g2_font_fur20_tf);
}

void loop()
{
  if (2 == BH1750_Read(BH1750address))
  {
    if (buff[0] == 255 && buff[1] == 255)
    {
      val = 65535;
    } else {
      val = ((buff[0] << 8) | buff[1]) / 1.2; //芯片手册中规定的数值计算方式
    }
  }

  strcpy(str, u8x8_u16toa(val, 5));  

  u8g2.firstPage();
  do {
    u8g2.drawStr(20, 20, "-Light-");
    u8g2.drawStr(10, 60, str);
    u8g2.drawStr(95, 60, "Lx");
    u8g2.setContrast(255 - map(val, 0, 500, 0, 255)); //将光照数据进行区间映射，控制OLED背光
  } while ( u8g2.nextPage() );
}

int BH1750_Read(int address)
{
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available())
  {
    buff[i] = Wire.read();  // receive one byte
    i++;
  }
  Wire.endTransmission();
  return i;
}

void BH1750_Init(int address)
{
  Wire.beginTransmission(address);
  Wire.write(0x10);
  Wire.endTransmission();
}
