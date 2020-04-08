#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

byte nuidPICC[4]; //存储读取的UID

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("RC522初始化完成...");
}

void loop() {
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

  Serial.print("十进制UID：");
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();

  // 使放置在读卡区的IC卡进入休眠状态，不再重复读卡
  rfid.PICC_HaltA();

  // 停止读卡模块编码
  rfid.PCD_StopCrypto1();
}

// 十六进制输出
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

//十进制输出
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : "");
    Serial.print(buffer[i], DEC);
  }
}
