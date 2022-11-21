#include <Keyboard.h>

              //Definição dos pinos
//-----------------------------------------------
#define B1 A2 //a
#define B2 A1 //Espaço
#define B3 A0 //w
#define B4 15 //q
#define B5 14 //Tab
#define B6 16 //e
#define B7 10 //Enter
//#define C1 2 //m[Ctrl Esquerdo]i1f[Alt Esquerdo]
#define C2 3 //m[Ctrl Esquerdo]i1f[Alt Esquerdo]
#define P1 8 //l
#define L1 9 //p
//-----------------------------------------------

    //Definição das teclas (formato decimal)
//-----------------------------------------------
#define a 97
#define Espaco 32
#define w 119
#define q 113
#define Tab 179
#define e 101
#define Enter 176
#define l 108
#define p 112
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
//int C1_state = 0;
int C2_state = 0;
int P1_state = 0;
int L1_state = 0;

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
  //pinMode(C1, INPUT_PULLUP);
  pinMode(C2, INPUT);
  pinMode(P1, INPUT_PULLUP);
  pinMode(L1, INPUT_PULLUP);
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
  //C1_state = digitalRead(C1);
  C2_state = digitalRead(C2);
  P1_state = digitalRead(P1);
  L1_state = digitalRead(L1);
//---------------------------

        //Acionamento dos botões
//--------------------------------------
  if (B1_state == LOW) {
    Keyboard.write(a);
    delay(300);
  }

  if (B2_state == LOW) {
    Keyboard.write(Espaco);
    delay(300);
  }

  if (B3_state == LOW) {
    Keyboard.write(w);
    delay(300);
  }

  if (B4_state == LOW) {
    Keyboard.write(q);
    delay(300);
  }

  if (B5_state == LOW) {
    Keyboard.write(Tab);
    delay(300);
  }

  if (B6_state == LOW) {
    Keyboard.write(e);
    delay(300);
  }

  if (B7_state == LOW) {
    Keyboard.press(Enter);
  }
  else{
    Keyboard.release(Enter);;
  }

  /*if (C1_state == LOW) {
    Keyboard.write(109);
    Keyboard.write(128);
    Keyboard.write(105);
    Keyboard.write(49);
    Keyboard.write(102);
    Keyboard.write(130);
    delay(85);
  }*/

    if (C2_state == LOW) {
    Keyboard.write(109);
    Keyboard.write(128);
    Keyboard.write(105);
    Keyboard.write(49);
    Keyboard.write(102);
    Keyboard.write(130);
    delay(100);
  }

  if (P1_state == LOW) {
    Keyboard.write(l);
    delay(300);
  }

  if (L1_state == LOW) {
    Keyboard.press(p);
  }
  else{
    Keyboard.release(p);
  }
}
