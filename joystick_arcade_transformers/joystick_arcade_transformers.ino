//Autor: Vitor Gabriel do Carmo Alves da Silva
//Descrição do Programa:

//Carrega a biblioteca do encoder e joystick
#include <Joystick.h>

int xPin = A0;
int yPin = A1;

unsigned int inValue = 0;
unsigned int timeDelay = 0;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD, 
  5, 0,                  // Quantidade de botões, Numero de Hat Switch
  true, true, false,     // Eixos X e Y no joystick, mas não o eixo Z
  false, false,  false,   // Sem Rx, Ry, ou Rz
  false, false,          // Sem rudder ou throttle
  false, false, false);  // Sem acelerador, freio, ou direção

  const unsigned long cycleDelta =50;
  unsigned long nextTime = 0;

//Variavel para a posição do encoder

//Eixo X
int newXPos = 1;
static int xPos = 1;
const int xLimit = 1100;

int newYPos = 1;
static int yPos = 1;
const int yLimit = 1000;

void setup()
{
  Serial.begin(9600);
  Joystick.begin();
  
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  
  Joystick.setXAxisRange(0, xLimit);
  Joystick.setYAxisRange(0, yLimit);

  digitalWrite(16, HIGH);
}
void loop(){
   Joystick.setButton(0, !digitalRead(5));
   Joystick.setButton(1, !digitalRead(6));
   Joystick.setButton(2, !digitalRead(9));
   Joystick.setButton(3, !digitalRead(7));

if (millis() >= nextTime) {

  Joystick.sendState();

  nextTime = millis ()+ cycleDelta;
  
   }

{
  newXPos = analogRead(xPin);
  
  //Se a posicao foi alterada, mostrar o valor
  if (xPos != newXPos) {
    //Serial.print("X: ");
    //Serial.print(newXPos);
    //Serial.print("   | Y:");
    //Serial.print(newYPos - 100);
    //Serial.println("");
    xPos = newXPos;
  }
  
  Joystick.setXAxis(xPos);

  newYPos = analogRead(yPin);
  
  //Se a posicao foi alterada, mostrar o valor
  if (yPos != newYPos) {
    //Serial.print("X: ");
    //Serial.print(newXPos);
    //Serial.print("   | Y:");
    //Serial.print(newYPos);
    //Serial.println("");
    yPos = newYPos;
  }  
  Joystick.setYAxis(yPos);
}

  if (digitalRead(15) == LOW) 
  {
    inValue++;
    pulseIn(15, HIGH);
    Serial.print("Creditos: ");
    Serial.println(inValue);
  }

if(inValue > 0){
  timeDelay++;
}

if(timeDelay > 100){
  switch(inValue){
    case 2:
        Serial.print("Iniciar deposito com: ");
        Serial.println(inValue);
        addCredits(1);
      break;
     case 5:
        Serial.print("Iniciar deposito com: ");
        Serial.println(inValue);
        addCredits(3); 
      break;
    case 10:
        Serial.print("Iniciar deposito com: ");
        Serial.println(inValue);
        addCredits(6);
      break;
    case 20:
        Serial.print("Iniciar deposito com: ");
        Serial.println(inValue);
        addCredits(12);
      break;
  }
}
}

void addCredits(int cout){
    int credits = cout;
    while(credits > 0){
      Joystick.pressButton(4);
      credits--;
      delay(300);
      Joystick.releaseButton(4);
  }
  inValue = 0;
  timeDelay = 0;
}
