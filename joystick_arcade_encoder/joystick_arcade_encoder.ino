#include <Joystick.h>
#include <Encoder.h>

int pulsosVolta= 4760;
int ganho = 0;
int Position = 0;
long oldPosition  = -999;
//Encoder pin A and B to pin 5 and 6
Encoder myEnc(5, 6);

#define Button_B      7
#define Button_Y      4
#define Button_A      10
#define Button_X      16
#define Button_Start  3
#define Button_Select 2
 
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD, 
  11, 0,                  // Quantidade de botões, Numero de Hat Switch
  true, true, true,     // Eixos X e Y no joystick, mas não o eixo Z
  true, true, true,   // Sem Rx, Ry, ou Rz
  false, false,          // Sem rudder ou throttle
  false, false, true);  // Sem acelerador, freio, ou direção

  
void setup() {

  Joystick.setZAxisRange   (0, 1023);
  Joystick.setRxAxisRange  (0, 1023);
  Joystick.setRyAxisRange  (0, 1023);
  Joystick.setRzAxisRange  (0, 1023);
  Joystick.setSteeringRange(0, (pulsosVolta*2.8));

  
  // Todos os botões abaixo estão setados como INPUT_PULLUP, dispensando resistores.
  pinMode(Button_B , INPUT_PULLUP);
  pinMode(Button_Y , INPUT_PULLUP);
  pinMode(Button_A , INPUT_PULLUP);
  pinMode(Button_X , INPUT_PULLUP);
  pinMode(Button_Start , INPUT_PULLUP);
  pinMode(Button_Select , INPUT_PULLUP);
  
  Joystick.begin();
  
 }
 
void loop() {

  long newPosition = myEnc.read();

if (digitalRead(4)== LOW){
 ganho = (map(newPosition,(pulsosVolta*(-1.4)),(pulsosVolta*1.4),(pulsosVolta*1.4),(pulsosVolta*(-1.4))));
}


if (newPosition != oldPosition){
   oldPosition = newPosition;



Position = (newPosition + ganho);

if (Position >= pulsosVolta*1.4){
  Position = pulsosVolta*1.4;
}
if (Position <= pulsosVolta*(-1.4)){
  Position = pulsosVolta*(-1.4);
}
}
  Joystick.setSteering (map(Position,pulsosVolta*(-1.4),pulsosVolta*1.4,0,pulsosVolta*2.8));
  Joystick.setZAxis  (analogRead(A2));
  Joystick.setRxAxis (analogRead(A1));
  Joystick.setRyAxis (analogRead(A0));
  Joystick.setRzAxis (analogRead(A3));

  // Como estamos usando INPUT_PULLUP, o valor precisa ser invertido.
   Joystick.setButton(0, !digitalRead(Button_X));
   Joystick.setButton(1, !digitalRead(Button_A));
   Joystick.setButton(2, !digitalRead(Button_B));
   Joystick.setButton(3, !digitalRead(Button_Y));
   Joystick.setButton(9, !digitalRead(Button_Start));
   Joystick.setButton(8, !digitalRead(Button_Select));
   
   // Um pequeno delay na ordem de fração do nosso movimento dos dedos.
   delay(50); 
}
