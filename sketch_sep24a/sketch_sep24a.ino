//Autor: Vitor Gabriel do Carmo Alves da Silva
//Data: 24/09/22
//Programa: Pro-5 promoção de créditos para equipamentos de diversão elétronicas

#define inPin 2 //Pino de Entrada
#define outPin 3 //Pino de Saída

int inState = 0; //Estado de Entrada

int inValue = 0; //Valor da Entrada

void setup() {
  pinMode(inPin, INPUT); //Pino 2 como Entrada
  pinMode(outPin, OUTPUT); //Pino 3 como Saída
}

void loop() {
  inState = digitalRead(inPin);

  if(inState == HIGH){
    inValue++; // 1/1
    delay(100);
  }

  switch(inValue){
    case 5:
        inValue++; // Valor a ser creditado 5+1 pulso
      break;
    case 10:
        inValue += 4; // Valor a ser creditado 10+4 pulsos
      break;
    case 20:
        inValue += 6; // Valor a ser creditado 20+6 pulsos
      break;
    case 50;
        inValue += 10; // Valor a ser creditado 50+10 pulsos
      break;
    case 100:
        inValue += 20; // Valor a ser creditado 100+20 pulsos    
      break;
  }

  while(inValue > 0){
    digitalWrite(outPin, HIGH);
    delay(100);
    digitalWrite(outPin, LOW);
    inValue--; 
  }
}
