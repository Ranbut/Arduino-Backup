//Autor: Vitor Gabriel
//Programa: Interface Subway USB
//Data: 05/08/2024

#include <Keyboard.h>

// Fios:
#define upButton 5
#define downButton 4
#define leftButton 2
#define rightButton 3
#define startButton 6
#define coinButton 15
#define countPin A1

void setup() {
  Serial.begin(9600);
  
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(coinButton, INPUT);
  pinMode(countPin, OUTPUT);

  digitalWrite(countPin, HIGH);
  Keyboard.begin();
}

void loop() {
  //Terra
  if (digitalRead(upButton) == LOW) 
  {
    Keyboard.press(KEY_UP_ARROW);
  }
  else{
    Keyboard.release(KEY_UP_ARROW);
  }

  if (digitalRead(downButton) == LOW) 
  {
    Keyboard.press(KEY_DOWN_ARROW);

  }
  else{
    Keyboard.release(KEY_DOWN_ARROW);
  }

  if (digitalRead(leftButton) == LOW) 
  {
    Keyboard.press(KEY_LEFT_ARROW);
  }
  else{
    Keyboard.release(KEY_LEFT_ARROW);
  }

  if (digitalRead(rightButton) == LOW) 
  {
    Keyboard.press(KEY_RIGHT_ARROW);
  }
  else{
    Keyboard.release(KEY_RIGHT_ARROW);
  }

  if (digitalRead(startButton) == LOW) 
  {
    Keyboard.press(49);
  }
  else{
    Keyboard.release(49);
  }
  
  if (digitalRead(coinButton) == LOW) 
  {
    Keyboard.write(229);
    digitalWrite(countPin, LOW);
    pulseIn(coinButton, HIGH);
    digitalWrite(countPin, HIGH);
  } 
}
