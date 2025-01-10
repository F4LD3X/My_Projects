#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
// Pin tanımları
Servo servo;
#define SS_pin 10
#define RST_pin 9
#define red_led 2
#define green_led 3

MFRC522 mfrc522(SS_pin, RST_pin);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const String authorizedUIDS = "83D9092E","90479443";
  // Yetkili kart UID'si

void setup() {
  Serial.begin(9600);
  lcd_wait();
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Close your card");

  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  servo.attach(7);
  servo.write(0);
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent())
    return;
  if (!mfrc522.PICC_ReadCardSerial())
    return;

  String bilgi = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    bilgi += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    bilgi += String(mfrc522.uid.uidByte[i], HEX);
  }
  bilgi.toUpperCase();

  Serial.println("Card UID: " + bilgi);

  lcd.clear();
  if (bilgi == authorizedUIDS) {
    accepted_code();
    lcd_wait();
  }  
  else  {
    rejected_code();
    lcd_wait();
  }
}
void lcd_wait() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Waiting");
  lcd.setCursor(3, 1);
  lcd.print("operation");
}
void accepted_code() {
  Serial.println("Login accepted");
  lcd.setCursor(1, 0);
  lcd.print("Login accepted");
  digitalWrite(green_led, HIGH);
  servo.write(90);  // Kapıyı aç
  delay(2000);
  servo.write(0);  // Kapıyı kapat
  digitalWrite(green_led, LOW);
  lcd.init();
}
void rejected_code() {
    Serial.println("Login rejected");
    lcd.setCursor(1, 0);
    lcd.print("Login rejected");
    lcd.setCursor(1, 1);
    lcd.print("Try Again");
    digitalWrite(red_led, HIGH);
    delay(2000);
    digitalWrite(red_led, LOW);
    lcd.init();
  }