#include <MFRC522.h>
#include <Servo.h>
#include <SPI.h>

int rstPin = 9;
int ssPin = 10;
int servoPin = 8;

Servo motor;
MFRC522 rfid(ssPin, rstPin);
byte ID[4] = {0,0,0,0};

void setup() {
  motor.attach(8);
  Serial.begin(9600);
  Serial.print("Otomatik Kapi");
  SPI.begin();
  rfid.PCD_Init();

}

void loop() {
  if(! rfid.PICC_IsNewCardPresent())
    return;
  if(! rfid.PICC_ReadCardSerial())
      return;
  if(rfid.uid.uidByte[0] == ID[0] &&
  rfid.uid.uidByte[1] == ID[1] &&
  rfid.uid.uidByte[2] == ID[2] &&
  rfid.uid.uidByte[3] == ID[3]){
    Serial.println("Kapı acildi");
    ekranaYazdir();
    motor.write(180);
    delay(3000);
    motor.write(0);
    delay(1000);
  }
  else{
    Serial.print("Yetkisiz kart");
    ekranaYazdir();
  }
  rfid.PICC_HaltA();

}

void ekranaYazdir(){
  Serial.print("ID Numarasi");
  for(int sayac=0; sayac<4; sayac++){
    Serial.print(rfid.uid.uidByte[sayac]);
    Serial.print(" ");
  }
  Serial.println("");
}
