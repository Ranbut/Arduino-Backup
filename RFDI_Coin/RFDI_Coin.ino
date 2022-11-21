//Programa: 
//Autor: Vitor Gabriel do Carmo Alves da Silva

//Bibliotecas
#include <LiquidCrystal_I2C.h> //LCD
#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>

//LCD
#define endereco  0x27
#define colunas   16
#define linhas    2
LiquidCrystal_I2C lcd(endereco, colunas, linhas);

//RFDI
#define RST_PIN 9
#define SS_PIN 10
MFRC522 LeitorRFID (SS_PIN, RST_PIN);


//Botões
const int c2Pin = 7; // Botão para escrever R$ 2
int c2Estado = 0; //Estado

const int c5Pin = 6; //Botão para escrever R$ 5
int c5Estado = 0; //Estado

//Rele
#define Rele A0

//Variaveis
int estado = 0;
int saida = 0;
String IDtag = ""; //Variável que armazenará o ID da Tag
String c2ID = "";
String c5ID = "";
unsigned long movimento = 0;

//Desenho


void setup() {
  
  Serial.begin(9600);
  
  //EEPROM: Salvamento e Carregamento
  if(EEPROM[0] != 9){
    EEPROM[0] = 9;
    EEPROM[1] = saida;
    
  } else {
    saida = EEPROM[1];
  }

  //LCD
  lcd.init();  //Iniciação do Display LCD
  lcd.backlight(); //Ligar Luz de Fundo 

  //RFDI
  SPI.begin();
  LeitorRFID.PCD_Init();

  //Botões
  pinMode(c2Pin, INPUT_PULLUP);
  pinMode(c5Pin, INPUT_PULLUP);

  //Rele
  pinMode(Rele, OUTPUT);
  digitalWrite(Rele, HIGH);

  //Desenho
  
  //1° Tela
  lcd.setCursor(4,0);
  lcd.print("DIVERSOM");
  lcd.setCursor(4,1);
  lcd.print("Music-box");

  saida = EEPROM[1];
}

void telaPrincipal()
{
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("DIVERSOM");
  lcd.setCursor(4,1);
  lcd.print("Music-box");
}

void Registro(){
        IDtag = ""; //Inicialmente IDtag deve estar vazia.
        
        // Verifica se existe uma Tag presente
        if ( !LeitorRFID.PICC_IsNewCardPresent() || !LeitorRFID.PICC_ReadCardSerial() ) {
            delay(50);
            return;
        }
        
        // Pega o ID da Tag através da função LeitorRFID.uid e Armazena o ID na variável IDtag        
        for (byte i = 0; i < LeitorRFID.uid.size; i++) {        
            IDtag.concat(String(LeitorRFID.uid.uidByte[i], HEX));
        }
        
        if(estado == 1)
        {
          estado = 1;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Gravado cartao");
          lcd.setCursor(0,1);
          lcd.print("Valor: R$ 2,00");
          delay(5000);
          telaPrincipal();
          c2ID = IDtag;
          if(c5ID == c2ID){c5ID = "";}
        }
        if(estado == 2)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Gravado cartao");
          lcd.setCursor(0,1);
          lcd.print("Valor: R$ 5,00");
          delay(5000);
          telaPrincipal();
          c5ID = IDtag;
          if(c2ID == c5ID){c2ID = "";}
         }
}

void Leitura(){
        IDtag = ""; //Inicialmente IDtag deve estar vazia.
        
        // Verifica se existe uma Tag presente
        if ( !LeitorRFID.PICC_IsNewCardPresent() || !LeitorRFID.PICC_ReadCardSerial() ) {
            delay(50);
            return;
        }
        
        // Pega o ID da Tag através da função LeitorRFID.uid e Armazena o ID na variável IDtag        
        for (byte i = 0; i < LeitorRFID.uid.size; i++) {        
            IDtag.concat(String(LeitorRFID.uid.uidByte[i], HEX));
        }

        if(IDtag == c2ID)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Cartao R$ 2,00");
          lcd.setCursor(0,1);
          lcd.print("Inseridos 2cred.");
          for(int i = 0; i < 2; i++)
          {
            digitalWrite(Rele, LOW);
            delay(150);
            saida++;
            saida = EEPROM[1];
            digitalWrite(Rele, HIGH);
            delay(150);
          }
          delay(1000);
          telaPrincipal();
        }
        if(IDtag == c5ID)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Cartao R$ 5,00");
          lcd.setCursor(0,1);
          lcd.print("Inseridos 5cred.");
          for(int i = 0; i < 5; i++)
          {
            digitalWrite(Rele, LOW);
            delay(150);
            saida++;
            saida = EEPROM[1];
            digitalWrite(Rele, HIGH);
            delay(150);
          }
          delay(1000);
          telaPrincipal();
        }
}

void loop() 
{  
  c2Estado = digitalRead(c2Pin);
  c5Estado = digitalRead(c5Pin);

  Leitura();
  Registro();

  movimento++;

  if(movimento >= 32) movimento = 0;
  
  if(c2Estado == HIGH && c5Estado == HIGH)
  estado = 0;
  
  if(c2Estado == LOW && c5Estado == HIGH)
  estado = 1;

  if(c2Estado == HIGH && c5Estado == LOW)
  estado = 2;

  if(c2Estado == LOW && c5Estado == LOW)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Relogio digital:");
    lcd.setCursor(0,1);
    lcd.print(saida);
    delay(5000);
    telaPrincipal();
  }

  if(saida == 1000000)
  { 
     saida = 1;
     EEPROM[1] = saida;
  }
}
