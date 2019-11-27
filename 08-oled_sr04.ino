#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET     4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);


#define TrigPin 2
#define EchoPin 3

int Value_cm;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);//开像素点发光
  display.clearDisplay();//清屏

  display.setTextSize(2); //设置字体大小
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop() {

  digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  Value_cm = int( pulseIn(EchoPin, HIGH) * 17 ) / 1000;

  display.clearDisplay();//清屏
  display.setCursor(50,10);
  display.print(Value_cm);
  display.println("cm");
  display.drawRect(0, 33, 128, 12, WHITE);
  display.fillRect(2, 35, map(Value_cm, 2, 20, 2, 124), 8, WHITE);
  display.display();//开显示
}
