#include <Wtv020sd16p.h>

int resetPin = 4;
int clockPin = 5;
int dataPin = 6;
int busyPin = 7;

//Variavel que armazena os caracteres recebidos
char buf;

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);

void setup()
{
   //Inicializa a serial
   Serial.begin(9600);
   //Inicializa o modulo WTV020
   wtv020sd16p.reset();
   //Informacoes iniciais   
   menu();
}

void loop()
{
  //Aguarda os dados da serial
  while(Serial.available() >0)
  {
    buf = Serial.read();
    if(buf == '1')
    {
      //Caso seja recebido o numero 1, reproduz o arquivo 0000.ad4
      Serial.println("Reproduzindo 0000.ad4");
      wtv020sd16p.asyncPlayVoice(0);
      delay(100);
      wtv020sd16p.stopVoice();
      delay(100);
      menu();
    }
 if(buf == '2')
    {
      //Caso seja recebido o numero 2, reproduz o arquivo 0001.ad4
      Serial.println("Reproduzindo 0000.ad4");
      wtv020sd16p.asyncPlayVoice(1);
      delay(100);
      wtv020sd16p.stopVoice();
      delay(100);
      menu();
    }
    
  }
}
//Mostra menu de opcoes
void menu()
{
  Serial.println("\nDigite a opção: ");
  Serial.println("1 - Reproduz arquivo 0000.ad4");
  Serial.println("2 - Reproduz arquivo 0001.ad4");
  Serial.println();
  
}

