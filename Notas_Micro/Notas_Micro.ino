//Autor: Vitor Gabriel do Carmo Alves da Silva

//Bibliotecas
#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>

/*RFDI
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 * 
*/
#define RST_PIN 9
#define SS_PIN 10
MFRC522 LeitorRFID (SS_PIN, RST_PIN);

#define Buzzer 4

//Rele
#define Coin A2

#define Botao 2
int botaoEstado = 0;

//Variaveis
int valor = 0;
int estado = 0;
bool gravando = false;

//IDs
String idTag = ""; //Variável que armazenará o ID da Tag
String id1;
String id2;
String id3;
String id4;
String id5;
int eepromOffset = 0;

unsigned int tempo = 0; //Tempo de aceitação de leitura

void setup() {
  Serial.begin(9600);
  SPI.begin();      // Inicia  SPI bus
  LeitorRFID.PCD_Init();   // Inicia MFRC522
  pinMode(Buzzer,OUTPUT); // Inicia Buzzer
  pinMode(Coin, OUTPUT); // Inicia Coin
  pinMode(Botao, INPUT_PULLUP); // Inicia Botão

  Serial.println("Inicializando...");

  Serial.println("Carregando IDs!");
  int id1AddrOffset = lerStringDoEEPROM(eepromOffset, &id1);
  Serial.print("ID 1: "); Serial.println(id1);
  int id2AddrOffset = lerStringDoEEPROM(id1AddrOffset, &id2);
  Serial.print("ID 2: "); Serial.println(id2);
  int id3AddrOffset = lerStringDoEEPROM(id2AddrOffset, &id3);
  Serial.print("ID 3: "); Serial.println(id3);
  int id4AddrOffset = lerStringDoEEPROM(id3AddrOffset, &id4);
  Serial.print("ID 4: "); Serial.println(id4);
  lerStringDoEEPROM(id4AddrOffset, &id5);
  Serial.print("ID 5: "); Serial.println(id5);
  eepromOffset = 0; //Restaurar valor do endereço;
}

void Registro(){
        idTag = ""; //Inicialmente idTag deve estar vazia.
        
        // Verifica se existe uma Tag presente
        if ( !LeitorRFID.PICC_IsNewCardPresent() || !LeitorRFID.PICC_ReadCardSerial() ){
          delay(25);
          return;
        }
        else{
            tempo = 100;
            estado++;
        }

        
        // Pega o ID da Tag através da função LeitorRFID.uid e Armazena o ID na variável idTag        
        for (byte i = 0; i < LeitorRFID.uid.size; i++) {        
            idTag.concat(String(LeitorRFID.uid.uidByte[i], HEX));
        }
        
        switch(estado)
        {
          case 1:
          Serial.println("Gravado ID de 2 reais!");
          tocarBeep(30, 2);
          delay(1000);
          id1 = idTag;
          Serial.print("Novo ID 1: "); Serial.println(idTag);
          break;

          case 2:
          Serial.println("Gravado ID de 5 reais!");
          tocarBeep(30, 2);
          delay(1000);
          id2 = idTag;
          Serial.print("Novo ID 2: "); Serial.println(idTag);
          break;

          case 3:
          Serial.println("Gravado ID de 10 reais!");
          tocarBeep(30, 2);
          delay(1000);
          id3 = idTag;
          Serial.print("Novo ID 3: "); Serial.println(idTag);
          break;

          case 4:
          Serial.println("Gravado ID de 20 reais!");
          tocarBeep(30, 2);
          delay(1000);
          id4 = idTag;
          Serial.print("Novo ID 4: "); Serial.println(idTag);
          break;

          case 5:
          Serial.println("Gravado ID de 50 reais!");
          tocarBeep(30, 2);
          delay(1000);
          id5 = idTag;
          Serial.print("Novo ID 5: "); Serial.println(idTag);
          break;
        }
        
          int id1AddrOffset = escreverStringAEEPROM(eepromOffset, id1);
          int id2AddrOffset = escreverStringAEEPROM(id1AddrOffset, id2);
          int id3AddrOffset = escreverStringAEEPROM(id2AddrOffset, id3);
          int id4AddrOffset = escreverStringAEEPROM(id3AddrOffset, id4);
          escreverStringAEEPROM(id4AddrOffset, id5);
}

void Leitura(){
        idTag = ""; //Inicialmente idTag deve estar vazia.
        
        // Verifica se existe uma Tag presente
        if ( !LeitorRFID.PICC_IsNewCardPresent() || !LeitorRFID.PICC_ReadCardSerial() ){
          delay(25);
          return;
        }
        
        // Pega o ID da Tag através da função LeitorRFID.uid e Armazena o ID na variável idTag        
        for (byte i = 0; i < LeitorRFID.uid.size; i++) {        
            idTag.concat(String(LeitorRFID.uid.uidByte[i], HEX));
        }
        
  if (idTag == id1)
  {
    Serial.print("ID 1: "); Serial.println(idTag);
    Serial.println("Nota de 2 reais!");
    valor += 2;
    tocarBeep(30, 2);
    delay(1000);
  }
  else if (idTag == id2)
  {
    Serial.print("ID 2: "); Serial.println(idTag);
    Serial.println("Nota de 5 reais!");
    valor += 5;
    tocarBeep(30, 2);
    delay(1000);
  }

  else if (idTag == id3)
  {
    Serial.print("ID 3: "); Serial.println(idTag);
    Serial.println("Nota de 10 reais!");
    valor += 10;
    tocarBeep(30, 2);
    delay(1000);
  }

  else if (idTag == id4)
  {
    Serial.print("ID 4: "); Serial.println(idTag);
    Serial.println("Nota de 20 reais!");
    valor += 20;
    tocarBeep(30, 2);
    delay(1000);
  }

  else if (idTag == id5)
  {
    Serial.print("ID 5: "); Serial.println(idTag);
    Serial.println("Nota de 50 reais!");
    valor += 50;
    tocarBeep(30, 2);
    delay(1000);
  }
  else
  {
    Serial.print("ID: "); Serial.println(idTag);
    Serial.println("Cartão Invalido!");
    tocarBeep(10, 2);
  }
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
  
  botaoEstado = digitalRead(Botao);

  if (botaoEstado == LOW && tempo <= 0 && gravando == false)
  {
        estado = 0;
        tempo = 100;
        String id1 = "";
        String id2 = "";
        String id3 = "";
        String id4 = "";
        String id5 = "";
        Serial.println("Resetando e gravando IDs!");
        int id1AddrOffset = escreverStringAEEPROM(eepromOffset, id1);
        int id2AddrOffset = escreverStringAEEPROM(id1AddrOffset, id2);
        int id3AddrOffset = escreverStringAEEPROM(id2AddrOffset, id3);
        int id4AddrOffset = escreverStringAEEPROM(id3AddrOffset, id4);
        escreverStringAEEPROM(id4AddrOffset, id5);
        tocarBeep(5, 2);
        delay(500);
        tocarBeep(5, 2);
        delay(500);
        tocarBeep(5, 2);
        gravando = true;
  }
  if(gravando == true && tempo <= 0){
    tocarBeep(5, 2);
    delay(500);
    tocarBeep(5, 2);
    delay(500);
    tocarBeep(5, 2);
    gravando = false;
    Serial.println("Tempo acabado!");
  }
  
    if(tempo > 0){
      Serial.print("Tempo: ");
      Serial.println(tempo);
      Registro();
      tempo--;
    }
    else
      Leitura();
}

void tocarBeep(int pitch, int repeat){
  for (int i = 0; i < repeat; i++){
    tone(Buzzer, pitch);
    delay(100);
    noTone(Buzzer);
  }
}

int escreverStringAEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
  return addrOffset + 1 + len;
}

int lerStringDoEEPROM(int addrOffset, String *strToRead)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';
  *strToRead = String(data);
  return addrOffset + 1 + newStrLen;
}
