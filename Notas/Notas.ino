#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define Buzzer 8
#define Coin A0
#define Pagar A1

int valor = 0;
 
void setup() 
{
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  pinMode(Buzzer,OUTPUT);
  pinMode(Coin, OUTPUT);
  pinMode(Pagar, OUTPUT);
  digitalWrite(Coin, HIGH);
  digitalWrite(Pagar, HIGH);
}
 
void loop() 
{
  if(valor > 0){
    if(digitalRead(Coin == HIGH)){
        digitalWrite(Coin, LOW);
        valor--;
        delay(100);
        digitalWrite(Coin, HIGH);
        delay(100);
    }
  }
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  conteudo.toUpperCase();
  
  if (conteudo.substring(1) == "C7 F9 96 7A")
  {
    Serial.println("Nota de 2 reais!");
    valor += 2;
    tone(Buzzer, 30);
    delay(100);
    noTone(Buzzer);
    delay(100);
    tone(Buzzer, 30);
    delay(100);
    noTone(Buzzer);
    delay(1000);
  }
  
  else if (conteudo.substring(1) == "57 BB 80 B2")
  {
    Serial.println("Nota de 5 reais!");
    valor += 5;
    tone(Buzzer, 30);
    delay(100);
    noTone(Buzzer);
    delay(100);
    tone(Buzzer, 30);
    delay(100);
    noTone(Buzzer);
    delay(1000);
  }

    else if (conteudo.substring(1) == "8B A7 AD 1B")
  {
    Serial.println("Nota de 10 reais!");
    valor += 10;
    tone(Buzzer, 30);
    delay(100);
    noTone(Buzzer);
    delay(100);
    tone(Buzzer, 30);
    delay(100);
    noTone(Buzzer);
    delay(1000);
  }

    else if (conteudo.substring(1) == "0B E0 5E 0A")
  {
    Serial.println("Nota de 20 reais!");
    valor += 20;
    tone(Buzzer, 30);
    delay(100);
    noTone(Buzzer);
    delay(100);
    tone(Buzzer, 30);
    delay(100);
    noTone(Buzzer);
    delay(1000);
  }

    else if (conteudo.substring(1) == "4B D2 6B 0D")
  {
    Serial.println("Nota de 50 reais!");
    valor += 50;
    tone(Buzzer, 30);
    delay(100);
    noTone(Buzzer);
    delay(100);
    tone(Buzzer, 30);
    delay(100);
    noTone(Buzzer);
    delay(1000);
  }
  
  else if (conteudo.substring(1) == "D9 45 29 5A")
  {
    Serial.println("Pagar!");
    tone(Buzzer, 30);
    delay(100);
    noTone(Buzzer);
    digitalWrite(Pagar, LOW);
    delay(500);
    digitalWrite(Pagar, HIGH);
    delay(1000);
  }
  else
  {
    Serial.println("Cartão Invalido!");
    tone(Buzzer, 10);
    delay(100);
    noTone(Buzzer);
    delay(100);
    tone(Buzzer, 10);
    noTone(Buzzer);
  }
} 
