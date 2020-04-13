#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  while (!Serial);    // 等待串口打开
  SPI.begin();
  mfrc522.PCD_Init();

  // 出厂默认使用FF FF FF FF FF FF作为密码A和B
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("开始扫描卡进行读写..."));
  Serial.print(F("使用密码:"));
  dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
  Serial.println();

  Serial.println(F("数据将被写入到#1扇区"));
}

void loop() {
  //寻找新卡
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  //验证UID是否可读
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;

  //显示卡信息
  Serial.print(F("卡 UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
  Serial.print(F("卡类型: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  // 检查是否MIFARE卡类型
  if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
          &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
          &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("不支持读取此卡类型"));
    return;
  }


  // 操作扇区1
  // 扇区1包括:块4~块7
  byte sector         = 1;
  byte blockAddr      = 4;
  byte dataBlock[]    = {
    0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C,
    0x0D, 0x0E, 0x0F, 0x10
  };//要写入的数据
  byte trailerBlock   = 7;
  MFRC522::StatusCode status;
  byte buffer[18];
  byte size = sizeof(buffer);

  // 使用密码A进行身份认证
  Serial.println(F("使用密码A进行身份认证..."));
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("身份认证失败 "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // 显示当前扇区数据
  Serial.println(F("当前扇区数据:"));
  mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
  Serial.println();


  // 读取写入前块数据
  Serial.print(F("读取写入前块")); Serial.print(blockAddr);
  Serial.println(F("数据..."));
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("读取失败 "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }
  Serial.print(F("块")); Serial.print(blockAddr); Serial.println(F("数据:"));
  dump_byte_array(buffer, 16); Serial.println();
  Serial.println();

  // 使用密码B进行身份认证
  Serial.println(F("使用密码B进行身份认证..."));
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("身份认证失败 "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //写入数据
  Serial.print(F("写数据到块")); Serial.print(blockAddr);
  Serial.println(F("..."));
  dump_byte_array(dataBlock, 16); Serial.println();
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("写入失败 "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }
  Serial.println();


  //读取写入后块数据
  Serial.print(F("读取写入后块")); Serial.print(blockAddr);
  Serial.println(F("数据..."));
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("读取失败 "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }
  Serial.print(F("块")); Serial.print(blockAddr); Serial.println(F("块:"));
  dump_byte_array(buffer, 16); Serial.println();


  // 显示当前扇区数据
  Serial.println(F("当前扇区数据:"));
  mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
  Serial.println();


  //使放置在读卡区的IC卡进入休眠状态，不再重复读卡
  mfrc522.PICC_HaltA();

  // 停止读卡模块编码
  mfrc522.PCD_StopCrypto1();
}

// 十六进制输出
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
