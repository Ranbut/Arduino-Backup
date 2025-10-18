//Autor: Vitor Gabriel
//Programa: Interface Crossy Road Arcade USB
//Data: 28/09/2025

#include <Keyboard.h>

// Fios:
#define player1Button 5 //Jogador 1
#define coinButton 15 //Coin
#define player2Button 4 //Jogador 2

bool checkReleased = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(player1Button, INPUT_PULLUP); //Pagar
  pinMode(coinButton, INPUT_PULLUP); //Coin
  pinMode(player2Button, INPUT_PULLUP); //Leitura
  Keyboard.begin();
}

void loop() {

  //Terra
  if (digitalRead(player1Button) == LOW) 
  {
    Serial.println("Space");
    Keyboard.press(32); //Space
  }
  else {
    Keyboard.release(32);
  }

  if (digitalRead(coinButton) == LOW) 
  {
    Serial.println("C");
    Keyboard.press(67); //C
  }
  else {
    Keyboard.release(67);
  }
  
  if (digitalRead(player2Button) == LOW) 
  {
    Serial.println("KEY_UP_ARROW");
    Keyboard.press(KEY_UP_ARROW); //KEY_UP_ARROW
  }
  else {
    Keyboard.release(KEY_UP_ARROW);
  }

  if(!checkReleased)
  {
    digitalWrite(player1Button, HIGH);
    digitalWrite(coinButton, HIGH);
    digitalWrite(player2Button, HIGH);
    Keyboard.releaseAll();
    checkReleased = true;
  }
}

//
