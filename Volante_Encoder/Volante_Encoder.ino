//Autor: Vitor Gabriel do Carmo Alves da Silva
//Descrição do Programa:

//Carrega a biblioteca do encoder e joystick
#include <RotaryEncoder.h>
#include <Joystick.h>

//Pinos de ligacao do encoder e joystick
RotaryEncoder encoderX(5, 6);

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD, 
  1, 0,
  true, true, false,
  false, false, false,
  false, false,
  false, false, false); 
  
//Variavel para a posição do encoder

int newXPos = 0;
static int xPos = 0;
const int xLimit = 1;

unsigned timeJoystick = 0;

void setup()
{
  Serial.begin(9600);
  Joystick.begin();
  Joystick.setXAxisRange(-xLimit, xLimit);
}
void loop()
{
  //Lê a posição do enconder
  encoderX.tick();
  newXPos = encoderX.getPosition();
  
  if (xPos != newXPos) {
    Serial.print(newXPos);
    Serial.println();
    
    if(xPos < newXPos)
       Joystick.setXAxis(-xLimit);

    if(xPos > newXPos)
     Joystick.setXAxis(xLimit);
     
    xPos = newXPos;
    timeJoystick = 0;
  }
  if (xPos == newXPos)
    timeJoystick++;
    
  if (timeJoystick == 8000)
    Joystick.setXAxis(0);
}
