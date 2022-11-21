#include <Keyboard.h>

              //Definição dos pinos
//-----------------------------------------------
#define B1 A3 //y - Linha 1
#define B2 A2 //j - Linha 5
#define B3 A1 //h - Linha 9
#define B4 A0 //m - Linha 15
#define B5 15 //n - Linha 25
#define B6 14 //v - Auto
#define B7 16 //g - Aposta
#define B8 10 //b - Jogar
#define B9 9 //f - Aposta Máxima
#define B10 8 //t - Tabela
#define L1 5 //4 - Leitura
#define P1 4 //r - Pagar 
#define C1 2 //p - Coin
//-----------------------------------------------

    //Definição das teclas (formato decimal)
//-----------------------------------------------
#define KEY_B1 121 //y
#define KEY_B2 106 //j
#define KEY_B3 104 //h
#define KEY_B4 109 //m
#define KEY_B5 110 //n
#define KEY_B6 118 //v
#define KEY_B7 103 //g
#define KEY_B8 98 //b
#define KEY_B9 102 //f
#define KEY_B10 116 //t
#define KEY_L1 52 //4
#define KEY_P1 114 //r
#define KEY_C1 112 //p
//-----------------------------------------------

   //Definição dos estados dos botões
//--------------------------------------
int B1_state = 0;
int B2_state = 0;
int B3_state = 0;
int B4_state = 0;
int B5_state = 0;
int B6_state = 0;
int B7_state = 0;
int B8_state = 0;
int B9_state = 0;
int B10_state = 0;
int L1_state = 0;
int P1_state = 0;
int C1_state = 0;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  
  //Modo de leitura dos botões
//------------------------------
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
  pinMode(B4, INPUT_PULLUP);
  pinMode(B5, INPUT_PULLUP);
  pinMode(B6, INPUT_PULLUP);
  pinMode(B7, INPUT_PULLUP);
  pinMode(B8, INPUT_PULLUP);
  pinMode(B9, INPUT_PULLUP);
  pinMode(B10, INPUT_PULLUP);
  pinMode(L1, INPUT_PULLUP);
  pinMode(P1, INPUT_PULLUP);
  pinMode(C1, INPUT);
//------------------------------
}

void loop() {

    //Leitura dos botões
//---------------------------
  B1_state = digitalRead(B1);
  B2_state = digitalRead(B2);
  B3_state = digitalRead(B3);
  B4_state = digitalRead(B4);
  B5_state = digitalRead(B5);
  B6_state = digitalRead(B6);
  B7_state = digitalRead(B7);
  B8_state = digitalRead(B8);
  B9_state = digitalRead(B9);
  B10_state = digitalRead(B10);
  L1_state = digitalRead(L1);
  P1_state = digitalRead(P1);
  C1_state = digitalRead(C1);

//---------------------------

        //Acionamento dos botões
//--------------------------------------
  if (B1_state == LOW) {
    Keyboard.write(KEY_B1);
    delay(300);
  }

  if (B2_state == LOW) {
    Keyboard.write(KEY_B2);
    delay(300);
  }

  if (B3_state == LOW) {
    Keyboard.write(KEY_B3);
    delay(300);
  }

  if (B4_state == LOW) {
    Keyboard.write(KEY_B4);
    delay(300);
  }

  if (B5_state == LOW) {
    Keyboard.write(KEY_B5);
    delay(300);
  }

  if (B6_state == LOW) {
    Keyboard.write(KEY_B6);
    delay(300);
  }

  if (B7_state == LOW) {
    Keyboard.write(KEY_B7);
    delay(300);
  }

  if (B7_state == LOW) {
    Keyboard.write(KEY_B7);
    delay(300);
  }

  if (B8_state == LOW) {
    Keyboard.write(KEY_B8);
    delay(300);
  }

  if (B9_state == LOW) {
    Keyboard.write(KEY_B9);
    delay(300);
  }

  if (B10_state == LOW) {
    Keyboard.write(KEY_B10);
    delay(300);
  }

  if (L1_state == LOW) {
    Keyboard.write(KEY_L1);
    delay(300);
  }

  if (P1_state == LOW) {
    Keyboard.write(KEY_P1);
    delay(300);
  }

  if (C1_state == HIGH) {
    Keyboard.write(KEY_C1);
    delay(100);
  }
}
//
//
//
