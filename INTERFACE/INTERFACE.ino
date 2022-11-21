//Programa:

#include <Keyboard.h>

// Botões:
#define betButton 8 //Aposta
#define maxBetButton 9 //Aposta máxima
#define playButton 7 //Jogar
#define autoPlayButton 10 //Jogar auto
#define chartButton 16 //Tabela
#define payButton A0 //Pagar
#define readingButton A1 //Leitura
#define coinButton A2 //Coin
#define lineButton1 2 //Linha 2
#define lineButton5 3 //Linha 5
#define lineButton9 4 //Linha 9
#define lineButton15 5 //Linha 15
#define lineButton25 6 //Linha 25

bool holding = false; //Estado de Segurado

void buttonKeyboard(char buttonName, int key)
{
    if (digitalRead(buttonName) == LOW) 
  {
    Keyboard.write(key); //G
    delay(100);
  }
}

void setup() { // Botões Estados:

  Serial.begin(9600);
  
  pinMode(betButton, INPUT_PULLUP); //Aposta
  pinMode(maxBetButton, INPUT_PULLUP); //Aposta máxima
  pinMode(playButton, INPUT_PULLUP); //Jogar
  pinMode(autoPlayButton, INPUT_PULLUP); //Jogar auto
  pinMode(chartButton, INPUT_PULLUP); //Tabela
  pinMode(payButton, INPUT_PULLUP); //Pagar
  pinMode(readingButton, INPUT_PULLUP); //Leitura
  pinMode(coinButton, INPUT_PULLUP); //Coin
  pinMode(lineButton1, INPUT_PULLUP); //Linha 1
  pinMode(lineButton5, INPUT_PULLUP); //Linha 5
  pinMode(lineButton9, INPUT_PULLUP); //Linha 9
  pinMode(lineButton15, INPUT_PULLUP); //Linha 15
  pinMode(lineButton25, INPUT_PULLUP); //Linha 25
  
  Keyboard.begin();
}

void loop() {
  if (digitalRead(betButton) == LOW) 
  {
    Keyboard.write(71);
    delay (100);
  }
    if (digitalRead(maxBetButton) == LOW) 
  {
    Keyboard.write(70);
    delay (100);
  }
    if (digitalRead(chartButton) == LOW) 
  {
    Keyboard.write(66);
    delay (100);
  }
    if (digitalRead(autoPlayButton) == LOW) 
  {
    Keyboard.write(86);
    delay (100);
  }
    if (digitalRead(coinButton) == LOW) 
  {
    Keyboard.write(80);
    delay (100);
  }
     if (digitalRead(readingButton) == LOW) 
  {
    Keyboard.write(52);
    delay (100);
  }
    if (digitalRead(chartButton) == LOW) 
  {
    Keyboard.write(84);
    delay (100);
  }
        if (digitalRead(payButton) == LOW) 
  {
    Keyboard.write(82);
    delay (100);
  }
    if (digitalRead(lineButton1) == LOW) 
  {
    Keyboard.write(89);
    delay (100);
  }
    if (digitalRead(lineButton5) == LOW) 
  {
    Keyboard.write(74);
    delay (100);
  }
      if (digitalRead(lineButton9) == LOW) 
  {
    Keyboard.write(72);
    delay (100);
  }
      if (digitalRead(lineButton15) == LOW) 
  {
    Keyboard.write(77);
    delay (100);
  }
      if (digitalRead(lineButton25) == LOW) 
  {
    Keyboard.write(78);
    delay (100);
  }
  
  /*buttonKeyboard("betButton", 71); //Aposta
  buttonKeyboard("maxBetButton", 70); //Aposta máxima
  buttonKeyboard("playButton", 66); //Jogar
  buttonKeyboard("autoPlayButton", 86); //Jogar auto
  buttonKeyboard("chartButton", 84); //Tabela
  buttonKeyboard("payButton", 82); //Pagar
  buttonKeyboard("readingButton", 52); //Leitura
  buttonKeyboard("coinButton", 80); //Coin
  buttonKeyboard("lineButton1", 89); //Linha 1
  buttonKeyboard("lineButton5", 74); //Linha 5
  buttonKeyboard("lineButton9", 72); //Linha 9
  buttonKeyboard("lineButton15", 77); //Linha 15
  buttonKeyboard("lineButton25", 78); //Linha 25
*/
}
