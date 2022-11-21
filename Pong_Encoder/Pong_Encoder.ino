//Autor: Vitor Gabriel do Carmo Alves da Silva
//Descrição do Programa:

//Carrega a biblioteca do encoder e joystick
#include <RotaryEncoder.h>
#include <Joystick.h>

//Pinos de ligacao do encoder e joystick
RotaryEncoder encoderY(5, 6);

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD, 
  1, 0,
  true, true, false,
  false, false, false,
  false, false,
  false, false, false); 
  
//Variavel para a posição do encoder

int newYPos = 0;
static int yPos = 0;
const int yLimit = 1;

unsigned timeJoystick = 0;

void setup()
{
  Serial.begin(9600);
  Joystick.begin();
  Joystick.setYAxisRange(-yLimit, yLimit);
}
void loop()
{
  //Lê a posição do enconder
  encoderY.tick();
  newYPos = encoderY.getPosition();
  
  if (yPos != newYPos) {
    Serial.print(newYPos);
    Serial.println();
    
    if(yPos < newYPos)
       Joystick.setYAxis(-yLimit);

    if(yPos > newYPos)
     Joystick.setYAxis(yLimit);
     
    yPos = newYPos;
    timeJoystick = 0;
  }
  if (yPos == newYPos)
    timeJoystick++;
    
  if (timeJoystick == 8000)
    Joystick.setYAxis(0);
}
