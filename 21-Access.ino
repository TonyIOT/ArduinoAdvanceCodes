#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <SPI.h>
#include <MFRC522.h>


#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

#define OLED_RESET     4
Adafruit_SSD1306 oled(128, 64, &Wire, OLED_RESET);

byte nuidPICC[4]; //存储读取的UID
byte cardID[4] = {0x6D, 0xC5, 0x4D, 0x96};//存储有权限的卡ID

void setup() {

  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("RC522初始化完成...");


  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(WHITE);//开像素点发光
  oled.clearDisplay();//清屏
  oled.setTextSize(2); //设置字体大小
}


void loop() {
  oled.clearDisplay();//清屏
  oled.setCursor(15, 2);//设置显示位置
  oled.println("--RFID--");
  oled.setCursor(25, 40);//设置显示位置
  oled.println("SCAN...");
  oled.display(); // 开显示

  //搜索新卡
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // 验证NUID是否可读
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  // 检查是否MIFARE卡类型
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println("不支持读取此卡类型");
    return;
  }

  // 保存读取到的UID
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }

  Serial.print("十六进制UID：");
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();

  if (nuidPICC[0] == cardID[0] && nuidPICC[1] == cardID[1]
      && nuidPICC[2] == cardID[2] && nuidPICC[3] == cardID[3])
  {
    oled.clearDisplay();//清屏
    oled.setCursor(15, 2);//设置显示位置
    oled.println("--RFID--");
    oled.setCursor(25, 40);//设置显示位置
    oled.println("CHECK OK");
    oled.display(); // 开显示

    delay(1000);
    oled.clearDisplay();//清屏
    oled.setCursor(15, 2);//设置显示位置
    oled.println("--RFID--");
    oled.setCursor(25, 40);//设置显示位置
    oled.println("OPEN...");
    oled.display(); // 开显示
  } else {
    oled.clearDisplay();//清屏
    oled.setCursor(15, 2);//设置显示位置
    oled.println("--RFID--");
    oled.setCursor(15, 40);//设置显示位置
    oled.println("CHECK ERR");
    oled.display(); // 开显示
  }

  // 使放置在读卡区的IC卡进入休眠状态，不再重复读卡
  rfid.PICC_HaltA();

  // 停止读卡模块编码
  rfid.PCD_StopCrypto1();
  delay(3000);
}

// 十六进制输出
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
