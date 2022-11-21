//Programa: 
//Autor: Paulo Andre e Vitor Gabriel
//Data: 

//#include <Keyboard.h>

//Reles
#define Rele A0

//Sensores
#define Sensor 2

//Botões
#define Credito 2
#define Iniciar 3
#define Leitura 6

//Estados
int estadoCredito;
int estadoIniciar;
int estadoLeitura;
int rele;
int bolas;

bool s_high = 0;

//Cads
String cad;

void setup() { // botoes estados:

  //Reles
  pinMode(Rele, OUTPUT);

  //Sensores
  pinMode(Sensor, INPUT_PULLUP);

  //Botões
  pinMode(Credito, INPUT_PULLUP);
  pinMode(Iniciar, INPUT_PULLUP);
  pinMode(Leitura, INPUT_PULLUP);

  digitalWrite(Rele, HIGH);
  
  Serial.begin(9600);
  
  //Keyboard.begin();
}

void loop() {

if(Serial.available()){
  cad = Serial.readString();
  rele = cad.toInt(); 
  if(rele == 1)
  {
      digitalWrite(Rele , LOW);
      bolas = 1;
      Serial.println("Ligando!");
  }

  if(rele == 2)
  {
      digitalWrite(Rele , LOW);
      bolas = 2;
      Serial.println("Ligando!");
  }

  if(rele == 3)
  {
      digitalWrite(Rele , LOW);
      bolas = 4;
      Serial.println("Ligando!");
  }
  
  if(rele == 0)
  {
    digitalWrite(Rele , HIGH);  
    Serial.println("Desligando!");
  }
}

  if(bolas < 0)
    bolas = 0;

  if(bolas == 0)
    digitalWrite(Rele , HIGH); 

  if(digitalRead(2)) s_high = 1;

  if(!digitalRead(2) && s_high)
  {
    s_high = 0;
    
    bolas--;
  }
    

 //Botões
 estadoCredito = digitalRead(Credito);
 estadoIniciar = digitalRead(Iniciar);
 estadoLeitura = digitalRead(Leitura);

  if(estadoCredito == LOW)
  {

    //Keyboard.write(194);
    
    while (estadoCredito != LOW){
      
    }
    delay(100);
  }

  if(estadoIniciar == LOW)
  {

    //Keyboard.write(195);

    while (estadoIniciar != LOW){
      
    }
    delay(100);
  }

  if(estadoLeitura == LOW)
  {

    //Keyboard.write(199);

    while (estadoLeitura != LOW){
      
    }
    delay(100);
  }
  
}
