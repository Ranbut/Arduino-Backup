//Programa: Trocadora de Fichas
//Autor: Vitor Gabriel do Carmo Alves da Silva

//Bibliotecas
#include <LiquidCrystal_I2C.h> //LCD
#include <EEPROM.h>

//LCD
#define endereco  0x27
#define colunas   16
#define linhas    2
LiquidCrystal_I2C lcd(endereco, colunas, linhas);

//Definição dos Botões

//Inserir Creditos
int const inCredito = 2; //Pino
int inEstado = 0; //Estado

//Saída de Creditos (Sensor)
int const outCredito = 5; //Pino
int outEstado = 0; //Estado

//Leitura de Entrada e Saída
int const botaoLeitura = A0; //Pino
int estadoLeitura = 0; //Estado

//Resetar Quantidade de Fichas
int const botaoFicha = A1; //Pino
int estadoFicha = 0; //Estado

//Definição do Rele
#define Rele 9 //Pino

//Define Credito
int atuaisCreditos = 0;
int const maxCreditos = 100;

//Tem Ficha?
bool temFicha = true;

//Apertado botão de Entrada
bool entrada = false;

//Tempo de Delay
unsigned long delayTime = 0;
unsigned long delayTimeButton = 0;
unsigned long delayTimeEntrada = 0;

//Valor de Entradas(IN) e Saídas(OUT)
int IN;
int OUT;

//Ficha
byte ficha;

void setup() {
  
  Serial.begin(9600);
  
  //EEPROM: Salvamento e Carregamento
  if(EEPROM[0] != 1){
    EEPROM[0] = 1;
    EEPROM[1] = IN;
    EEPROM[2] = OUT;
    EEPROM[3] = ficha;
  } else {
      IN = EEPROM[1];
      OUT = EEPROM[2];
      ficha = EEPROM[3];
  }

  //LCD
  lcd.init();  //Iniciação do Display LCD
  lcd.backlight(); //Ligar Luz de Fundo 
  
  //3° e Normal Tela do Display
  lcd.setCursor(0,0);
  lcd.print("TROCADOR/FICHAS");  
  lcd.setCursor(0,1);
  lcd.print("Fichas:");
  lcd.setCursor(9,1);
  lcd.print(atuaisCreditos); 
  
  //Estado dos Botões
  pinMode(inCredito, INPUT); //Credito
  pinMode(outCredito, INPUT); //Sensor
  pinMode(botaoLeitura, INPUT_PULLUP); //Leitura
  pinMode(botaoFicha, INPUT_PULLUP); //Ficha

  //Rele
  pinMode(Rele, OUTPUT);
  digitalWrite(Rele, LOW); //Começa sempre desligado

   atuaisCreditos = EEPROM[3]; 
}

void loop() 
{  
  inEstado = digitalRead(inCredito);
  outEstado = digitalRead(outCredito);
  estadoLeitura = digitalRead(botaoLeitura);
  
if (inEstado == LOW && atuaisCreditos < maxCreditos)
{
  if(inEstado = HIGH)
  {
  delayTime = 0;
  atuaisCreditos++;
  IN++;
  EEPROM[1] = IN;
  ficha++;
  EEPROM[3] = ficha;
  lcd.setCursor(9,1);
  lcd.print(atuaisCreditos); 
  delay (50);
  }
}
if(atuaisCreditos > 0 && inEstado == HIGH)
{
  if(delayTime > 10 && delayTime < 20)
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Aguarde a saida!");
  lcd.setCursor(0,1);
  lcd.print("Fichas:");
  lcd.setCursor(9,1);
  lcd.print(atuaisCreditos); 
  }

  if(delayTime < 5000)
  {
  delayTime++;
  delay(1);
  }
  
  if(delayTime == 750 && temFicha == true)
  {
  digitalWrite(Rele, HIGH);
  } 
}

if(atuaisCreditos <= 0 && delayTimeButton == 0 && entrada == false)
{
  lcd.setCursor(0,0);
  lcd.print("TROCADOR/FICHAS");
  lcd.setCursor(15,0);
  lcd.print(" ");   
  delayTime = 0;
  digitalWrite(Rele, LOW);
}

if(delayTime == 5000)
{  
  digitalWrite(Rele, LOW);
  delayTime = 0;
  delayTimeButton = 0;
  delayTimeButton = 5000;
  temFicha = false;  
}

if(delayTime == 200 && temFicha == false)
{
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("SEM FICHAS!");
  lcd.setCursor(0,1);
  lcd.print("Fichas:");
  lcd.setCursor(9,1);
  lcd.print(atuaisCreditos); 
  lcd.print(" ");  
}


if(delayTime == 1500 && temFicha == false)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CHAME O TECNICO!");
  lcd.setCursor(0,1);
  lcd.print("Fichas:");
  lcd.setCursor(9,1);
  lcd.print(atuaisCreditos); 
  lcd.print(" ");  
}

if (outEstado == HIGH && atuaisCreditos > 0)
{ 
  atuaisCreditos--;
  OUT++;
  EEPROM[2] = OUT;
  ficha--;
  EEPROM[3] = ficha;
  delayTime = 600;
  lcd.setCursor(9,1);
  lcd.print(atuaisCreditos); 
  lcd.print(" ");
  digitalWrite(Rele, LOW);
  delay(120);
}

if (estadoLeitura == LOW)
  entrada = true;

if(entrada == true && delayTimeEntrada == 1)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Entrada:");
  lcd.setCursor(9,0);
  lcd.print(IN);
  lcd.setCursor(0,1);
  lcd.print("Saida:");
  lcd.setCursor(9,1);
  lcd.print(OUT);
}

if(estadoLeitura == LOW & delayTime == 0)
{
  delayTimeButton++;
  delayTimeEntrada = 0;
}

if (estadoLeitura == HIGH & entrada == true)
{
  delayTimeEntrada++;
}

if (estadoLeitura == HIGH & delayTimeButton > 0)
{
  digitalWrite(Rele, LOW);
  delayTimeButton = 0;  
}

if (delayTimeButton == 600)
{
 delayTimeEntrada = 5000;
 digitalWrite(Rele, HIGH);
}

Serial.println(delayTimeButton);
  
if (delayTimeEntrada >= 600 && entrada == true)
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TROCADOR/FICHAS"); 
  lcd.setCursor(0,1);
  lcd.print("Fichas:");
  lcd.setCursor(9,1);
  lcd.print(atuaisCreditos);
  Serial.println(ficha);
  entrada = false;
  delayTimeEntrada = 0;
  }

  if(IN == 1000000)
  { 
     IN = 1;
     EEPROM[1] = IN;
  }

  if(OUT == 1000000)
  { 
     OUT = 1;
     EEPROM[2] = OUT;
  }

    if(atuaisCreditos < 0)
  {
    atuaisCreditos = 0;
    ficha = 0;
    EEPROM[3] = ficha;
  }
  if(ficha < 0)
  {
    atuaisCreditos = 0;
    ficha = 0;
    EEPROM[3] = ficha;
  }
}
