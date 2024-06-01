//Autor: Vitor Gabriel
//Programa: Interface Hallowen USB
//Data: 01/06/2024

#include <Keyboard.h>
#include <Keypad.h>

const byte ROWS = 6;
const byte COLS = 2;

// Fios:
#define payButton A1 //Pagar
#define coinButton 15 //Coin
#define readingButton A2 //Leitura

byte rowPins[ROWS] = { 2, 3, 4, 5, 6, 7 }; // Marrom, Roxo, Preto, Cinza, Azul, Laranja 
byte colPins[COLS] = { 8, 9 }; // Vermelho, Branco

char keys[ROWS][COLS] = {
// VM   BR
  {'T', 'Y'}, // Marrom
  {'V', 'J'}, // Roxo
  {'F', 'H'}, // Preto
  {'G', 'M'}, // Cinza
  {'0', 'N'}, // Azul
  {'B', '0'}, // Laranja
};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  
  pinMode(payButton, INPUT_PULLUP); //Pagar
  pinMode(coinButton, INPUT_PULLUP); //Coin
  pinMode(readingButton, INPUT_PULLUP); //Leitura
  Keyboard.begin();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    switch(key){
      case 'Y':
        Serial.println("Y");
        Keyboard.write(89);
        break;
      case 'T':
        Serial.println("T");
        Keyboard.write(84);
        break;
      case 'J':
        Serial.println("J");
        Keyboard.write(74);
        break;
      case 'V':
        Serial.println("V");
        Keyboard.write(86);
        break;
       case 'F':
        Serial.println("F");
        Keyboard.write(70);
        break;
      case 'H':
        Serial.println("H");
        Keyboard.write(72);
        break;
      case 'G':
        Serial.println("G");
        Keyboard.write(71);
        break;
      case 'M':
        Serial.println("M");
        Keyboard.write(77);
        break;
      case 'B':
        Serial.println("B");
        Keyboard.write(66);
        break;
      case 'N':
        Serial.println("N");
        Keyboard.write(78);
        break;
    }
  }
  
  //Terra
  if (digitalRead(payButton) == LOW) 
  {
    Keyboard.write(82); //R
    delay (100);
  }
    if (digitalRead(coinButton) == LOW) 
  {
    Keyboard.write(80); //P
    delay (100);
  }
    if (digitalRead(readingButton) == LOW) 
  {
    Keyboard.write(52); //4
    delay (100);
  }
}
