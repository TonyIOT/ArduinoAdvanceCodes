/*
 * BH1750
 * 数字光照传感器实验
 */
 
#include <Wire.h> //IIC

int BH1750address = 0x23;
byte buff[2];
uint16_t val = 0;

void setup()
{
  Wire.begin();
  BH1750_Init(BH1750address);
  Serial.begin(9600);
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

    Serial.print(val, DEC);
    Serial.println("[lx]");
  }
  delay(500);
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
