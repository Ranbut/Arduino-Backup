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

bool segurando = false;

unsigned long duracao = 0;

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
  pinMode(coinButton, INPUT); //Coin
  pinMode(readingButton, INPUT_PULLUP); //Leitura
  Keyboard.begin();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    switch(key){
      case 'Y':
        Serial.println("Y");
        Keyboard.press('Y');
        break;
      case 'T':
        Serial.println("T");
        Keyboard.press('T');
        break;
      case 'J':
        Serial.println("J");
        Keyboard.press('J');
        break;
      case 'V':
        Serial.println("V");
        Keyboard.press('V');
        break;
       case 'F':
        Serial.println("F");
        Keyboard.press('F');
        break;
      case 'H':
        Serial.println("H");
        Keyboard.press('H');
        break;
      case 'G':
        Serial.println("G");
        Keyboard.press('G');
        break;
      case 'M':
        Serial.println("M");
        Keyboard.press('M');
        //Keyboard.write(77);
        break;
      case 'B':
        Serial.println("B");
        Keyboard.press('B');
        break;
      case 'N':
        Serial.println("N");
        Keyboard.press('N');
        break;
    }
    delay(50);
    Keyboard.releaseAll();
  }
  
  //Terra
  if (digitalRead(payButton) == LOW) 
  {
    Serial.println("R");
    Keyboard.write(82); //R
    while(!digitalRead(payButton)){}
    delay(300);
  }

  if (digitalRead(coinButton) == LOW) 
  {
    Serial.println("P");
    Serial.print("Duração: ");
    Serial.println(duracao);
    Keyboard.write(80); //P             
    duracao = pulseIn(coinButton, HIGH);
  }
  
  if (digitalRead(readingButton) == LOW) 
  {
    Serial.println("4");
    Keyboard.write(52); //4
    while(!digitalRead(readingButton)){}
    delay(300);
  }
}
