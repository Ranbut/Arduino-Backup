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
int const outCredito = 3; //Pino
int outEstado = 0; //Estado

//Leitura de Entrada e Saída
#define botaoLeitura A2 //Pino
int estadoLeitura = 0; //Estado

//Resetar Quantidade de Fichas
#define botaoFicha A1 //Pino
int estadoFicha = 0; //Estado

//Definição do Rele
#define Rele A3 //Pino

//Define Credito
int atuaisCreditos = 0;
int const maxCreditos = 50;

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
  
  //1° Tela
  lcd.setCursor(0,0);
  lcd.print("** DIVERKIDS **");
  lcd.setCursor(0,1);
  lcd.print("** BEM-VINDO **");
  
  delay(2000);
  lcd.clear();

  //2° Tela
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
  
  delay(5000);
  lcd.clear();
  
  //3° e Normal Tela do Display
  lcd.setCursor(0,0);
  lcd.print("Bolas Premiadas");  
  lcd.setCursor(0,1);
  lcd.print("Creditos:");
  lcd.setCursor(11,1);
  lcd.print(atuaisCreditos);
  if(atuaisCreditos < 10)
  {
    lcd.setCursor(12,1);
    lcd.print("/2");
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print("/2");
  }
  
  //Estado dos Botões
  pinMode(inCredito, INPUT); //Credito
  pinMode(outCredito, INPUT); //Sensor
  pinMode(botaoLeitura, INPUT_PULLUP); //Leitura
  pinMode(botaoFicha, INPUT_PULLUP); //Ficha

  //Rele
  pinMode(Rele, OUTPUT);
  digitalWrite(Rele, HIGH); //Começa sempre desligado

   atuaisCreditos = EEPROM[3];

  lcd.setCursor(11,1);
  lcd.print(atuaisCreditos);
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
  lcd.setCursor(11,1);
  lcd.print(atuaisCreditos); 
    if(atuaisCreditos < 10)
  {
    lcd.setCursor(12,1);
    lcd.print("/2");
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print("/2");
  }
  delay (150);
  }
}
if(atuaisCreditos > 1 && inEstado == HIGH)
{
  if(delayTime > 10 && delayTime < 20)
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Aguarde a saida!");
  lcd.setCursor(0,1);
  lcd.print("Creditos:");
  lcd.setCursor(11,1);
  lcd.print(atuaisCreditos);
    if(atuaisCreditos < 10)
  {
    lcd.setCursor(12,1);
    lcd.print("/2");
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print("/2");
  } 
  }

  if(delayTime < 5000)
  {
  delayTime++;
  delay(1);
  }
  
  if(delayTime == 750 && temFicha == true)
  {
  digitalWrite(Rele, LOW);
  } 
}

if(atuaisCreditos <= 0 && delayTimeButton == 0 && entrada == false)
{
  lcd.setCursor(0,0);
  lcd.print("Bolas Premiadas");
  lcd.setCursor(15,0);
  lcd.print(" ");   
  delayTime = 0;
  digitalWrite(Rele, HIGH);
}

if(delayTime == 5000)
{  
  digitalWrite(Rele, HIGH);
  delayTime = 0;
  delayTimeButton = 0;
  delayTimeButton = 5000;
  temFicha = false;  
}

if(delayTime == 200 && temFicha == false)
{
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("SEM BOLAS!");
  lcd.setCursor(0,1);
  lcd.print("Creditos:");
  lcd.setCursor(11,1);
  lcd.print(atuaisCreditos);
    if(atuaisCreditos < 10)
  {
    lcd.setCursor(12,1);
    lcd.print("/2");
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print("/2");
  } 
  lcd.print(" ");  
}


if(delayTime == 1500 && temFicha == false)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CHAME O TECNICO!");
  lcd.setCursor(0,1);
  lcd.print("Creditos:");
  lcd.setCursor(11,1);
  lcd.print(atuaisCreditos);
    if(atuaisCreditos < 10)
  {
    lcd.setCursor(12,1);
    lcd.print("/2");
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print("/2");
  } 
  lcd.print(" ");  
}

if (outEstado == HIGH && atuaisCreditos > 1)
{ 
  atuaisCreditos -= 2;
  OUT++;
  EEPROM[2] = OUT;
  ficha -= 2;
  EEPROM[3] = ficha;
  delayTime = 600;
  lcd.setCursor(11,1);
  lcd.print(atuaisCreditos);
    if(atuaisCreditos < 10)
  {
    lcd.setCursor(12,1);
    lcd.print("/2");
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print("/2");
  } 
  lcd.print(" ");
  if(atuaisCreditos == 1)
  {
    lcd.setCursor(0,0);
    lcd.print("Valor faltando!");
  }
  digitalWrite(Rele, HIGH);
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
  lcd.setCursor(7,1);
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
  digitalWrite(Rele, HIGH);
  delayTimeButton = 0;  
}

if (delayTimeButton == 600)
{
 delayTimeEntrada = 5000;
 digitalWrite(Rele, LOW);
}

Serial.println(delayTimeButton);
  
if (delayTimeEntrada >= 600 && entrada == true)
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bolas premiadas"); 
  lcd.setCursor(0,1);
  lcd.print("Creditos:");
  lcd.setCursor(11,1);
  lcd.print(atuaisCreditos);
    if(atuaisCreditos < 10)
  {
    lcd.setCursor(12,1);
    lcd.print("/2");
  }
  else
  {
    lcd.setCursor(13,1);
    lcd.print("/2");
  }
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
