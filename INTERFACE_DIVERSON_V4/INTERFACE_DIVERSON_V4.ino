//Programa: Trocadora de Fichas
//Autor: Paulo Andre e Vitor Gabriel
//Data: 11/01/2021.

#include <Keyboard.h>

// botoes selecionados:
const int coinButton = 21;
const int leftButton = 6;
const int downButton = 7;
const int upButton = 8;
const int rightButton = 14;
const int enterButton = 16;
const int cancelButton = 10;
const int v1Button = 15;
const int v2Button = 9;

bool segurando = false;

void setup() { // botoes estados:
  pinMode(coinButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(enterButton, INPUT_PULLUP);
  pinMode(cancelButton, INPUT_PULLUP);
  pinMode(v1Button, INPUT_PULLUP);
  pinMode(v2Button, INPUT_PULLUP);
 
  Serial.begin(9600);
  
  Keyboard.begin();
}

void loop() {

 

 //Função dos botões:

  //Credito
  if (digitalRead(coinButton) == LOW) 
  {
    Keyboard.write(223);

    while (!digitalRead(coinButton)){
      
    }
    delay (100);
  }

 //Seta Esquerda
  if (digitalRead(leftButton) == LOW) 
  {
    Keyboard.write(KEY_DELETE);
    delay (300);
  }

  //Seta Baixo
  if (digitalRead(downButton) == LOW) 
  {
    Keyboard.write(KEY_DOWN_ARROW);
     delay (300);
  }

  //Seta Cima
  if (digitalRead(upButton) == LOW) 
  {
     Keyboard.write(KEY_UP_ARROW);
     delay (300);
  }

  //Seta Direita
  if (digitalRead(rightButton) == LOW) 
  {
    Keyboard.write(KEY_INSERT); 
    delay (300);
  }

  //Tocar
  if (digitalRead(enterButton) == LOW & segurando == false) 
  {
    Keyboard.write(KEY_RETURN);
    segurando = true;
    delay(300);
  }
  if (digitalRead(enterButton) == HIGH) 
  {
    segurando = false;
  }

  //Cancelar
  if (digitalRead(cancelButton) == LOW) 
  {
    Keyboard.write(KEY_F8); 
    delay (400);
  }

  //Volume menos (-)
  if (digitalRead (v1Button) == LOW) 
  {
    Keyboard.write(KEY_F10); 
    delay (300);
  }
  
 //Volume mais (+)
  if (digitalRead(v2Button) == LOW) 
  {
    Keyboard.write(KEY_F9); 
    delay (300);
  }
  
}
