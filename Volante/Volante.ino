int pinos [] = {
  4,5,6,7,8,9,10,11,12};

  int lastButtonState[9] = {0,0,0,0,0,0,0,0,0};

  int pulsosVolta= 4760;

#include <Joystick.h>
#include <Encoder.h>

Joystick_ Joystick;

int ganho = 0;
int Position = 0;

long oldPosition  = -999;

Encoder myEnc(5, 6);

void setup() {

  
Serial.begin(115200);

//Joystick.setSteeringRange(0, (pulsosVolta*2.8));
  
//for(int i=0; i<9; i++){
//  pinMode(pinos[i],INPUT_PULLUP);
 // }
  //pinMode(4,INPUT_PULLUP);
 // pinMode(6,INPUT_PULLUP);

  Joystick.begin();

pinMode(13,OUTPUT);
  analogWrite(13,255);
}

void loop() {

long newPosition = myEnc.read();

Position = (newPosition + ganho);

if (Position >= pulsosVolta*1.4){
  Position = pulsosVolta*1.4;
}
if (Position <= pulsosVolta*(-1.4)){
  Position = pulsosVolta*(-1.4);
}
 
//Joystick.setSteering (map(Position,pulsosVolta*(-1.4),pulsosVolta*1.4,0,pulsosVolta*2.8));

//for (int index = 0; index < 9; index++)
 // {
 //   int currentButtonState = map(digitalRead(index + 5),HIGH,LOW,LOW,HIGH);
    
    
   // if (currentButtonState != lastButtonState[index])
   // {
    // Joystick.setButton(index, currentButtonState);
    //  lastButtonState[index] = currentButtonState;
      
    }
  //  Joystick.setButton(8, map(digitalRead(4),HIGH,LOW,LOW,HIGH));
   // Joystick.setButton(9, map(digitalRead(6),HIGH,LOW,LOW,HIGH));
 // }

  
//}
