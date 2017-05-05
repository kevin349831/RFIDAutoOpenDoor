#include <SPI.h>
#include <MFRC522.h>     // 引用程式庫
#include <Servo.h> //馬達

#define RST_PIN      9        // 讀卡機的重置腳位
#define SS_PIN       10        // 晶片選擇腳位

MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件
Servo myservo; // 建立Servo物件，控制伺服馬達
//LED
int ledPin = 8;
//所有卡號
int UserID[] = {*,*,*,*,*,*,*,*,*,*,*,*};
void setup() {
  Serial.begin(9600);
  Serial.println("RFID reader is ready!");

  SPI.begin();
  mfrc522.PCD_Init();   // 初始化MFRC522讀卡機模組

  pinMode(ledPin,OUTPUT);

  myservo.attach(7); // 修正脈衝寬度範圍
  myservo.write(50); // 一開始先置中90度
  delay(3000);
}

void loop() {
    // 確認是否有新卡片
  
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {

      
      
      byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
      byte idSize = mfrc522.uid.size;   // 取得UID的長度
      Serial.print("PICC type: ");      // 顯示卡片類型
      // 根據卡片回應的SAK值（mfrc522.uid.sak）判斷卡片類型
      MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
      Serial.println(mfrc522.PICC_GetTypeName(piccType));

      Serial.print("UID Size: ");       // 顯示卡片的UID長度值
      Serial.println(idSize);
      

      
        if((UserID[0] == id[0]) && (UserID[1] == id[1]) && (UserID[2] == id[2]) && (UserID[3] == id[3])){
          //偵測到卡片就亮燈
          digitalWrite(ledPin, HIGH);
          delay(100);
          myservo.write(180);
        }
        else if((UserID[4] == id[0]) && (UserID[5] == id[1]) && (UserID[6] == id[2]) && (UserID[7] == id[3])){
          //偵測到卡片就亮燈
          digitalWrite(ledPin, HIGH);
          delay(100);
          myservo.write(180);
        }
        else if((UserID[8] == id[0]) && (UserID[9] == id[1]) && (UserID[10] == id[2]) && (UserID[11] == id[3])){
          //偵測到卡片就亮燈
          digitalWrite(ledPin, HIGH);
          delay(100);
          myservo.write(180);
        }
      
          
      for (byte i = 0; i < idSize; i++) {  // 逐一顯示UID碼
        
        Serial.print("id[");
        Serial.print(i);
        Serial.print("]: ");
        //Serial.println(id[i], HEX);       // 以16進位顯示UID值
        Serial.print(id[i]);
      }
      
      Serial.println();

      mfrc522.PICC_HaltA();  // 讓卡片進入停止模式

      delay(3000);
      myservo.write(50);
    } 
    //結束後關燈
      digitalWrite(ledPin, LOW);
    
}
