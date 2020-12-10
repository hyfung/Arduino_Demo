#include <SPI.h>
#include <MFRC522.h>     // 引用程式庫

#define RST_PIN      9        // 讀卡機的重置腳位
#define SS_PIN       10        // 晶片選擇腳位
#define LED          13
#define TONE         3
#define JSON_
#define TONE_
#define RELAY_

#ifdef RELAY_
#define RELAY_PIN 2
bool relayState = false;

#endif

MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  //  Serial.println("RFID reader is ready!");

#ifdef RELAY_
  pinMode(RELAY_PIN, OUTPUT);
#endif

#ifdef TONE_
  pinMode(TONE, OUTPUT);
#endif

  SPI.begin();
  mfrc522.PCD_Init();   // 初始化MFRC522讀卡機模組
}

void loop() {
  digitalWrite(LED, HIGH);
  // 確認是否有新卡片
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
#ifdef TONE_
    tone(TONE, 2500);
#endif
    digitalWrite(LED, LOW);
    byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
    byte idSize = mfrc522.uid.size;   // 取得UID的長度

#ifdef JSON_
    Serial.print("{'id':'");
#endif

    for (byte i = 0; i < idSize; i++) {  // 逐一顯示UID碼
      Serial.print(id[i], HEX);
      //      Serial.print("id[");
      //      Serial.print(i);
      //      Serial.print("]: ");
      //      Serial.println(id[i], HEX);       // 以16進位顯示UID值
    }

#ifdef JSON_
    Serial.print("'}");
#endif

    //        Serial.print(/"/////PICC type: ");      // 顯示卡片類型
    // 根據卡片回應的SAK值（mfrc522.uid.sak）判斷卡片類型
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    //    Serial.println(mfrc522.PICC_GetTypeName(piccType));
    //    Serial.print("UID Size: ");       // 顯示卡片的UID長度值
    //    Serial.println(idSize);

    Serial.println();

    mfrc522.PICC_HaltA();  // 讓卡片進入停止模式

#ifdef RELAY_
    relayState = !relayState;
    digitalWrite(RELAY_PIN, relayState);
#endif

#ifdef TONE_
    delay(200);
    noTone(TONE);
#endif
  }
}
