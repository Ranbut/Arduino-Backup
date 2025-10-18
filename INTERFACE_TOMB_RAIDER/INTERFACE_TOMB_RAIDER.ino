//Autor: Vitor Gabriel
//Programa: Interface Subway USB
//Data: 18/10/2025

#include <Keyboard.h>

// Teclas:
#define wKey 87
#define sKey 83
#define aKey 65
#define dKey 68
#define alpha1Key 49
#define alpha5Key 53

// Fios:
#define upButton 5
#define downButton 4
#define leftButton 2
#define rightButton 3
#define startButton 6
#define coinButton 15

void setup() {
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(coinButton, INPUT);

  Keyboard.begin();
}

void loop() {
  //Terra
  if (digitalRead(upButton) == LOW) 
  {
    Keyboard.press(wKey);
  }
  else{
    Keyboard.release(wKey);
  }

  if (digitalRead(downButton) == LOW) 
  {
    Keyboard.press(sKey);

  }
  else{
    Keyboard.release(sKey);
  }

  if (digitalRead(leftButton) == LOW) 
  {
    Keyboard.press(aKey);
  }
  else{
    Keyboard.release(aKey);
  }

  if (digitalRead(rightButton) == LOW) 
  {
    Keyboard.press(dKey);
  }
  else{
    Keyboard.release(dKey);
  }

  if (digitalRead(startButton) == LOW) 
  {
    Keyboard.press(alpha1Key);
  }
  else{
    Keyboard.release(alpha1Key);
  }
  
  if (digitalRead(coinButton) == LOW) 
  {
     Keyboard.press(alpha5Key);
  }
  else
  {
     Keyboard.release(alpha5Key);
  }
}
