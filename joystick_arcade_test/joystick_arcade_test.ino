//Autor: Vitor Gabriel do Carmo Alves da Silva
//Descrição do Programa:

//Carrega a biblioteca do joystick
#include <Joystick.h>

//Pinos de ligacao do encoder e joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD, 
  11, 0,
  true, true, true,
  true, true, true,
  false, false,
  false, false, true);

const int pinoPot = A0;

//Variavel para a posição
int newPos = 0;
static int pos = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(pinoPot, INPUT);
  
  Joystick.begin();
  Joystick.setXAxisRange(-127, 127); 
}
void loop()
{

  Joystick.setXAxis(map(analogRead(pinoPot),0,1023,-127,127));
}
