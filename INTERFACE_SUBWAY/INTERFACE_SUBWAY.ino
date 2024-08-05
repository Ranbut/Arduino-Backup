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
  pinMode(coinButton, INPUT_PULLUP);
  pinMode(countPin, OUTPUT);

  digitalWrite(countPin, HIGH);
  Keyboard.begin();
}

void loop() {
  
  //Terra
  if (digitalRead(upButton) == LOW) 
  {
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.releaseAll();
    while(!digitalRead(upButton)){}
    delay(100);
  }

  if (digitalRead(downButton) == LOW) 
  {
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.releaseAll();
    while(!digitalRead(downButton)){}
    delay(100);
  }

  if (digitalRead(leftButton) == LOW) 
  {
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.releaseAll();
    while(!digitalRead(leftButton)){}
    delay(100);
  }

  if (digitalRead(rightButton) == LOW) 
  {
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.releaseAll();
    while(!digitalRead(rightButton)){}
    delay(100);
  }

  if (digitalRead(startButton) == LOW) 
  {
    Keyboard.write(49);
    while(!digitalRead(startButton)){}
    delay(100);
  }
  
  if (digitalRead(coinButton) == LOW) 
  {
    Serial.println("Funcionou crédito!");
    Keyboard.write(53);
    digitalWrite(countPin, LOW);
    pulseIn(coinButton, HIGH);
    digitalWrite(countPin, HIGH);
  }
}
