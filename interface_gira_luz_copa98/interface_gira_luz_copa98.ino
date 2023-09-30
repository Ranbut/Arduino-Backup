//Programa: Paulo Andre.  Data:13/05/2023.

#include <Keyboard.h>

// Botões:

#define BrasilButton 2 // Brasil (Y)
#define FrancaButton 3 // França (J)
#define ItaliaButton 4 // Italia (H)
#define AlemanhaButton 5 // Alemanha (M)
#define HolandaButton 6 // Holanda (N)
#define DinamarcaButton 7 // Dinamarca (T)
#define ArgentinaButton 8 //Argentina (F)
#define CroaciaButton 9 //Croacia (V)
#define PlayButton 10 //Jogar (B)
#define ConfigButton 16 // configuraçao (C)
#define payButton A0 //Pagar (R)
#define readingButton A1 //Leitura (G)
#define coinButton A2 //Coin (P)

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
  
  pinMode(BrasilButton, INPUT_PULLUP); //Brasil
  pinMode(FrancaButton, INPUT_PULLUP); //França
  pinMode(ItaliaButton, INPUT_PULLUP); //Italia
  pinMode(AlemanhaButton, INPUT_PULLUP); //Alemanha
  pinMode(HolandaButton, INPUT_PULLUP); //Holanda
  pinMode(DinamarcaButton, INPUT_PULLUP); //Dinamarca
  pinMode(ArgentinaButton, INPUT_PULLUP); //Argentina
  pinMode(CroaciaButton, INPUT_PULLUP); //Croacia
  pinMode(PlayButton, INPUT_PULLUP); //Jogar
  pinMode(ConfigButton, INPUT_PULLUP); //Configurações
  pinMode(payButton, INPUT_PULLUP); //Pagar
  pinMode(readingButton, INPUT_PULLUP); //Leitura
  pinMode(coinButton, INPUT_PULLUP); //Creditos
  
  Keyboard.begin();
}

void loop() {
  if (digitalRead(BrasilButton) == LOW) 
  {
    Keyboard.write(89);
    delay (100);
  }
    if (digitalRead(FrancaButton) == LOW) 
  {
    Keyboard.write(74);
    delay (100);
  }
    if (digitalRead(ItaliaButton) == LOW) 
  {
    Keyboard.write(72);
    delay (100);
  }
    if (digitalRead(AlemanhaButton) == LOW) 
  {
    Keyboard.write(77);
    delay (100);
  }
    if (digitalRead(HolandaButton) == LOW) 
  {
    Keyboard.write(78);
    delay (100);
  }
     if (digitalRead(DinamarcaButton) == LOW) 
  {
    Keyboard.write(84);
    delay (100);
  }
    if (digitalRead(ArgentinaButton) == LOW) 
  {
    Keyboard.write(70);
    delay (100);
  }
        if (digitalRead(CroaciaButton) == LOW) 
  {
    Keyboard.write(86);
    delay (100);
  }
    if (digitalRead(PlayButton) == LOW) 
  {
    Keyboard.write(66);
    delay (100);
  }
    if (digitalRead(ConfigButton) == LOW) 
  {
    Keyboard.write(67);
    delay (100);
  }
      if (digitalRead(payButton) == LOW) 
  {
    Keyboard.write(82);
    delay (100);
  }
      if (digitalRead(readingButton) == LOW) 
  {
    Keyboard.write(71);
    delay (100);
  }
      if (digitalRead(coinButton) == LOW) 
  {
    Keyboard.write(80);
    delay (100);
  }
  
  
}
