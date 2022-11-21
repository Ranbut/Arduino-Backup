//Autor: Vitor Gabriel do Carmo Alves da Silva
//Descrição do Programa:

//Carrega a biblioteca do encoder e joystick
#include <RotaryEncoder.h>
#include <Joystick.h>

//Pinos de ligacao do encoder e joystick
RotaryEncoder encoderX(5, 6);
RotaryEncoder encoderY(8, 7);

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD, 
  11, 0,
  true, true, false,
  false, false, false,
  false, false,
  false, false, false); 

//Variavel para a posição do encoder

//Eixo X
int newXPos = 0;
static int xPos = 0;
const int xLimit = 15;

int newYPos = 0;
static int yPos = 0;
const int yLimit = 15;

void setup()
{
  Serial.begin(9600);
  Joystick.begin();
  Joystick.setXAxisRange(-xLimit, xLimit);
  Joystick.setYAxisRange(-yLimit, yLimit);
}
void loop()
{
  //Lê a posição do enconder
  encoderX.tick();
  newXPos = encoderX.getPosition();
  encoderY.tick();
  newYPos = encoderY.getPosition();
  
  //Se a posicao foi alterada, mostrar o valor
  if (xPos != newXPos) {
    Serial.print(newXPos);
    Serial.println();
    xPos = newXPos;
    
    if(xPos < -xLimit)
    encoderX.setPosition(-xLimit);

    if(xPos > xLimit)
    encoderX.setPosition(xLimit);
  }
  
  if (yPos != newYPos) {
    Serial.print(newYPos);
    Serial.println();
    yPos = newYPos;
    
    if(yPos < -yLimit)
    encoderY.setPosition(-yLimit);

    if(yPos > yLimit)
    encoderY.setPosition(yLimit);
  }
  
  Joystick.setXAxis(xPos);
  Joystick.setYAxis(yPos);
  
}
