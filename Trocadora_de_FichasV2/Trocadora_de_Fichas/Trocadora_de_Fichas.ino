//Programa: Trocadora de Fichas
//Descrição: Trocadora de Fichas - Tema: Super Mario Bros.
//Autor: Vitor Gabriel do Carmo

//Bibliotecas
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#define SD_ChipSelectPin 10
#include <SPI.h>
#include <TMRpcm.h>
#include <EEPROM.h>
#include <Wire.h>

//LCD
#define endereco  0x27 // Endereços comuns: 0x27, 0x3F
#define colunas   16
#define linhas    2

LiquidCrystal_I2C lcd(endereco, colunas, linhas);

//Som
int const soundPin = 5;
int soundState = 0;
bool temSom;
TMRpcm tmrpcm;

//Rele
const int RelePin = A1;

//Sensor
int const sensorPin = 3; //Pino do sensor
int sensorState = 0; //Estado do sensor
bool s_high = 0;

//Botões
//Adicionar Ficha (IN)
const int pin = 2; //Pino do botão
int state = 0; //Estado do botão

//Acionar Motor
const int onButtonPin = A2; //Pino do botão
int onButtonState = 1; //Estado do botão
const int ledPin = 4; //Pino LED

//Leitura Entrada (IN) e Saída (OUT)
const int dataButtonPin = A3; //Pino do botão
int dataButtonState = 0; //Estado do botão

//Tempo dos textos no LCD (milisegundos)
long eventTime_1_text = 5000; //5000 milisegundos = 5 segundos
long eventTime_2_text = 10000; //10000 milisegundos = 10 segundos

//Armazenar tempo anterior
unsigned long previousTime_1 = 0; 
unsigned long previousTime_2 = 0;

unsigned long int timer;  

//Variável
int ficha = 0;
int figura = 0;
bool temFicha = false;
bool ligado = false;
int IN; //Entrada(s)
int OUT; //Saída(s)

//Banco de Dados (Dados que serão salvos)
int dataIN; //Entradas
int dataOUT; //Saídas

//Figuras
//Estrela
byte star[] = {
  B00100,
  B10101,
  B01110,
  B01110,
  B01110,
  B01110,
  B10101,
  B00100
};

//Fogo do Foguete
byte rocketFire[] = {
  B11111,
  B11111,
  B00000,
  B11111,
  B11111,
  B00000,
  B11111,
  B11111
};

//Traseira do Foguete
byte rocketBack[] = { 
  B11111,
  B11111,
  B01011,
  B11111,
  B11111,
  B01011,
  B11111,
  B11111
};

//Meio do Foguete
byte rocketMiddle[] = {
  B11111,
  B00000,
  B01110,
  B11111,
  B11111,
  B01110,
  B00000,
  B11111
};

//Ponta do Foguete
byte rocketEnd[] = {
  B10000,
  B01000,
  B00100,
  B00011,
  B00011,
  B00100,
  B01000,
  B10000
};

void leituraNoteiro();

void saidaFicha();

//Estabelecendo definições
void setup()
{
  IN = EEPROM.read(dataIN);
  OUT = EEPROM.read(dataOUT);
  
  //Som
  tmrpcm.speakerPin = 9;
  pinMode(soundPin, INPUT_PULLUP);

  Serial.begin(9600);
  
if(!SD.begin(SD_ChipSelectPin))
  {
  Serial.println("Cartão SD falhou em carregar!");
  return;
  }
  else
  {
    Serial.println("Trocadora de Fichas");
    Serial.println("DiverKids");
    Serial.println("Cartão SD carregou com sucesso!");
    Serial.print("Entradas: ");
    Serial.println(IN);
    Serial.print("Saídas: ");
    Serial.println(OUT);
  }
  
  lcd.init(); // INICIA A COMUNICAÇÃO COM O DISPLAY
  lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY
  
  //Botões
  pinMode(pin, INPUT_PULLUP);
  pinMode(onButtonPin, INPUT_PULLUP); // Botão para ligar o Rele
  pinMode(dataButtonPin, INPUT_PULLUP); //Botão de Leitura de Entrada (IN) e Saída (OUT)

  //LED
  pinMode(ledPin, OUTPUT); // Coloca LED como saída
  
  //Sensor
  pinMode(sensorPin, INPUT); // Coloca sensor como entrada

  //Rele
  pinMode(RelePin, OUTPUT); // Coloca o pino Rele como saída 
  digitalWrite(RelePin, HIGH); //Deixe desligado
}

//O Programa
void loop()
{ 
  //attachInterrupt(digitalPinToInterrupt(sensorPin), saidaFicha, FALLING);
  
  state = digitalRead(pin);

  if(digitalRead(sensorPin)) s_high = 1;
  
  //Tempo
  unsigned long currentTime = millis(); //Tempo atual em milisegundos

  //Ler o aperto de botões para os estados...
  onButtonState = digitalRead(onButtonPin);
  sensorState = digitalRead(sensorPin);
  dataButtonState = digitalRead(dataButtonPin);
  soundState = digitalRead(soundPin);
  
  if(!tmrpcm.isPlaying() && temSom == true)
  {
    tmrpcm.play("theme.wav"); //Toque "test1.wav"
  }

  //LCD Texto 1
  if (currentTime - previousTime_1 >= eventTime_1_text && temFicha == false && figura < 3)
  {
  lcd.clear(); //Tire o texto do LCD e coloque...
  lcd.setCursor(2,0); //Coloque na coluna 0, linha 1
  lcd.print("Troca fichas"); //Escreva "Troca fichas"
  lcd.setCursor(0,1); //Coloque na coluna 0, linha 0
  lcd.print("1 ficha = R$1,00"); //Escreva "1 ficha = R$1,00"
  
  figura++;
  previousTime_1 = currentTime;
  }
  
  //LCD Texto 2
  if (currentTime - previousTime_2 >= eventTime_2_text && figura == 2)
  {
  if(temFicha == false)
  {
  lcd.clear(); //Tire o texto do LCD e coloque...
  }
  lcd.setCursor(0,0); //Coloque na coluna 0, linha 0
  lcd.print("Em reais: "); //Escreva "Em reais: "
  lcd.setCursor(9,0); //Coloque na coluna 0, linha 1
  lcd.print(ficha); //Escreva "x" (x = ficha)
  
  if(ficha < 10)
  {
  lcd.setCursor(10,0); //Coloque na coluna 0, linha 0
  lcd.print(",00"); //Escreva ",00"
  }
  
  if (ficha > 9 && ficha < 100)
  {
  lcd.setCursor(11,0); //Coloque na coluna 11, linha 0
  lcd.print(",00"); //Escreva ",00"
  }

  if (ficha == 100)
  {
  lcd.setCursor(12,0); //Coloque na coluna 12, linha 0
  lcd.print(",00"); //Escreva ",00"
  }

  lcd.setCursor(0,1); //Coloque na coluna 0, linha 1
  lcd.print("Fichas: "); //Escreva "Fichas: "
  lcd.setCursor(7,1); //Coloque na coluna 7, linha 1
  lcd.print(ficha); //Escreva "x" (x = ficha)

  if (ficha == false)
  {
  figura++;
  previousTime_2 = currentTime;
  }
  } 

  //LCD Texto 3
  if (currentTime - previousTime_1 >= eventTime_1_text && temFicha == false && figura == 3)
  {
  lcd.clear(); //Tire o texto do LCD e coloque...
  lcd.createChar(1, rocketFire);
  lcd.createChar(2, rocketBack);
  lcd.createChar(3, rocketMiddle);
  lcd.createChar(4, rocketEnd);
  lcd.createChar(5, star);
  for(int i = 0; i < 4; i++)
  {
  lcd.clear();
  lcd.setCursor(i+1,0); //Coloque na coluna 0, linha 0
  lcd.write(1);
  lcd.setCursor(i+2,0); //Coloque na coluna 0, linha 0
  lcd.write(2);
  lcd.setCursor(i+3,0); //Coloque na coluna 0, linha 0
  lcd.write(3);
  lcd.setCursor(i+4,0); //Coloque na coluna 0, linha 0
  lcd.write(3);
  lcd.setCursor(i+5,0); //Coloque na coluna 0, linha 0
  lcd.write(3);
  lcd.setCursor(i+6,0); //Coloque na coluna 0, linha 0
  lcd.write(3);
  lcd.setCursor(i+7,0); //Coloque na coluna 0, linha 0
  lcd.write(3);
  lcd.setCursor(i+8,0); //Coloque na coluna 0, linha 0
  lcd.write(4);
  lcd.setCursor(6-i,1); //Coloque na coluna 0, linha 0
  lcd.print("DiverKids");
  delay(250);
  }
  lcd.setCursor(0,0); //Coloque na coluna 0, linha 0
  lcd.write(5);
  lcd.setCursor(15,0); //Coloque na coluna 0, linha 0
  lcd.write(5);
  
  previousTime_1 = currentTime;
  }
  
  if (currentTime - previousTime_2 >= eventTime_2_text && temFicha == false && figura == 3)
  
  {
     figura = 0;
     previousTime_2 = currentTime;
  }

  //Ativar/desativar som (Pulso)
  if (soundState == LOW) 
  {
    temSom = true;
  }
  if (soundState == HIGH)
  {
    temSom = false;
  }

  if(state == LOW)
  {
    if(ficha == 0)
    {
    lcd.clear(); //Tire o texto do LCD e coloque...
    }
    Serial.print("Fichas: ");
    Serial.println(ficha + 1);
    ficha++;
    tmrpcm.setVolume(5); //Coloque o volume no 5
    tmrpcm.play("coin.wav"); //Toque o efeito sonoro da moeda
    IN++;
    EEPROM.write(dataIN, IN);
    delay(150);
  }

  if(onButtonState == LOW && temFicha == true)
  {
    ligado = true; //Rele está ligado
  }

  if (temFicha == true)
  {
    tmrpcm.setVolume(0);
    currentTime = 0;
    eventTime_1_text = 0;
    eventTime_2_text = 0;
  }
  //Se não tiver ficha
  else
  {
    tmrpcm.setVolume(5);
    currentTime = 0;
    eventTime_1_text = 5000;
    eventTime_2_text = 10000;
    ligado = false; //Rele não está ligado
  }


 //Se ficha for maior que 0
 if(ficha > 0)
 {
  figura = 2;
  digitalWrite(ledPin, LOW);//Ligue LED do botão do Rele
  temFicha = true; // Agora tem ficha
 }
 else //Se não
 {
  digitalWrite(ledPin, HIGH); //Desligue LED do botão do Rele
  temFicha = false; // Agora não tem ficha
 }

  //Se apertar o botão do Rele e tiver ficha
  if(onButtonState == LOW && temFicha == true)
  {
    ligado = true; //Rele está ligado
  }

  if (temFicha == true)
  {
    tmrpcm.setVolume(0);
    currentTime = 0;
    eventTime_1_text = 0;
    eventTime_2_text = 0;
  }
  //Se não tiver ficha
  else
  {
    tmrpcm.setVolume(5);
    currentTime = 0;
    eventTime_1_text = 5000;
    eventTime_2_text = 10000;
    ligado = false; //Rele não está ligado
  }

  //Se a variavel ligado é true (verdadeiro)
  if(ligado == true)
  {
  digitalWrite(RelePin, LOW); //Ligue o Rele
  }
  else //Caso não
  {
  digitalWrite(RelePin, HIGH); //Deixe desligado
  }

  //Se sensor é ativado, tem ficha e o Rele está ligado
  if (sensorState == HIGH && ficha > 0 && ligado == true)
  {
    if(ficha == 10)
    {
      lcd.clear();
    }
    
    if(ficha == 100)
    {
      lcd.clear();
    }
    //if(!digitalRead(sensorPin) && s_high){
    ficha--;
    tmrpcm.setVolume(5); //Coloque o volume no 5
    tmrpcm.play("coin.wav"); //Toque o efeito sonoro da moeda
    OUT++; //Registre na saída (OUT)
    EEPROM.write(dataOUT, OUT);
    Serial.print("Fichas: ");
    Serial.println(ficha);
    //}
  }
  
  if (dataButtonState == LOW)
  {
    lcd.clear(); //Tire o texto do LCD e coloque...
    lcd.setCursor(0,0); //Na coluna 0 e linha 0
    lcd.print("Entrada: "); //Escreva "Entrada: "
    lcd.setCursor(10,0); //Na coluna 10 e linha 0
    lcd.print(IN); //Escreva o valor da entrada (IN)
    lcd.setCursor(0,1); //Na coluna 0 e linha 1
    lcd.print("Saida: "); //Escreva "Saida: "
    lcd.setCursor(10,1); //Na coluna 10 e linha 1
    lcd.print(OUT); //Escreva o valor da saída (OUT)
    delay(10000); //Demore 10000 milegundos (10 segundos) por segurança e visualização do texto
    lcd.clear(); //Tire o texto do LCD e coloque...
  }

  if(IN == 1000000)
  { 
     IN = 0;
     EEPROM.write(dataIN, IN);
  }

  if(OUT == 1000000)
  { 
     OUT = 0;
     EEPROM.write(dataOUT, OUT);
  }

  if(ficha < 0)
  {
    ficha = 0;
  }
  
}//Termino do Programa de Loop

void saidaFicha()
{
  if(s_high && ligado == true) ficha--; //Tire a ficha
}
