//MP3 Player Arduino
//EduArduino

 #include <LiquidCrystal.h> //inclusão das bibliotecas 
 #include <Wtv020sd16p.h>

int resetPin = 4;  //Pino Reset
int clockPin = 5;  //Pino clock
int dataPin = 6;   //Pino data (DI)
int busyPin = 7;   //Pino busy
unsigned long time;//Variável para armazenar o tempo mostrado no display
int estadoBoton1 = 0; //Variável que armazena o estado do botão NEXT
int estadoBoton2 = 0; //Variável que armazena o estado do botão PREV
int estadoBotonA0 = 0; //Variável que armazena o estado do botão PLAY
int valor=0; //Variável criada para monitorar se a música está tocando



LiquidCrystal lcd (13, 12, 11, 10, 9, 8); //configuração e pinagem do lcd 
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);//configuração e pinagem do da placa MP3

void setup()
{
  lcd.begin (16,2); //Inicializa o LCD
  //Rotina Inicial do LCD
  lcd.clear(); 
  lcd.setCursor(0,0);   
  lcd.print ("EduArduino MP3"); 
  lcd.setCursor(0,1); 
  lcd.print ("Selecione Faixa");   
  delay (2000); 

  wtv020sd16p.reset(); //Inicializa o modulo WTV020

//Definição dos pinos
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT);

}
int numero = 0;  //Variável para contar as faixas quando as teclas são acionadas
int segundos=0;  //Variável para incrementar os segundos para o tempo de execução do áudio
int minutos=0; //Variável para incrementar os minutos para o tempo de execução do áudio

void loop()
{   
  valor = digitalRead(A1);//Leitura do pino busy para saber quando o áudio está tocando
//Rotina para mostrar o tempo quando o áudio está tocando
 if(valor==1){
segundos = ++time;
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("faixa 000"); 
   lcd.print(numero); 
   //colocar 0 na frente quando os segundos forem menores que 10
   if(segundos<10)
   {
  lcd.setCursor(3,1);
   lcd.print("0"); 
   lcd.print(segundos);
   }
   else{
   lcd.setCursor(3,1);
   lcd.print(segundos);
   }
   
//colocar 0 na frente quando minutos forem menores que 10
  if(minutos<10){
      lcd.setCursor(0,1);
      lcd.print("0"); 
      lcd.print(minutos);
      lcd.print(":");
  }
  else{
       lcd.setCursor(0,1);
       lcd.print(minutos);
       lcd.print(":");}
       //Para aparecer 00 depois do 59
 if(segundos==60){
    lcd.setCursor(3,1); 
    lcd.print("00");
  }
   

 delay(1000); 

      }
 
//Para o contador de faixas não apresentar - 1
if(numero<0){
  numero=0;
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("faixa 000"); 
   lcd.print(numero); 
   lcd.setCursor(0,1);
   lcd.print("Aperte Play");
   }
   //Para aumentar o contador de faixas quando o NEXT for pressionado
if(estadoBoton1 == LOW) {
  numero = numero +1; 
  time=0;
  minutos=0;
   delay(50); 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("faixa 000"); 
    lcd.print(numero); 
    lcd.setCursor(0,1);
    lcd.print("Aperte Play");
    
}
 //Para diminuir o contador de faixas quando o PREV for pressionado
if(estadoBoton2 == LOW) {
  numero = numero -1;
    time=0;
    minutos=0;
   delay(50);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("faixa 000"); 
    lcd.print(numero); 
    lcd.setCursor(0,1);
    lcd.print("Aperte Play");
    wtv020sd16p.stopVoice();
     delay(100);
}
//_____________________________________________
//Botão >> (NEXT)
  estadoBoton1 = digitalRead(2); 
  if (estadoBoton1 == LOW ) { 
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("faixa 000"); 
     lcd.print(numero); 
     lcd.setCursor(0,1);
     lcd.print("Aperte Play");
     Serial.println(numero);
     //Para parar a música quando em execução e o NEXT for pressionado
     wtv020sd16p.stopVoice();
     delay(100);
    }
    
  //_____________________________________________
    //Botão << (PREV)
    estadoBoton2 = digitalRead(3); 
    if (estadoBoton2 == LOW ) { 

     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("faixa 000"); 
     lcd.print(numero);     
     lcd.setCursor(0,1);
     lcd.print("Aperte Play");
     Serial.println(numero);
     //Para parar a música quando em execução e o PREV for pressionado
      wtv020sd16p.stopVoice();
      delay(100);
    
 }
 //_____________________________________________
  //Botão > (PLAY)
    estadoBotonA0 = digitalRead(A0); 
    if(estadoBotonA0 == LOW) { 
      //Zera o tempo
        time=0;
        minutos=0;
        
        //Só tocar quando estiver dentro da quantidade que há no cartão 
        //Neste caso está configurado para ler faixas de 0 à 8 e no 9 aparecer "vazio"
     if(numero>=0 && numero < 9){
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("faixa 000"); 
     lcd.print(numero);     

      
      wtv020sd16p.stopVoice();
      delay(100);
      wtv020sd16p.asyncPlayVoice(numero);        
      delay(100); 
      wtv020sd16p.stopVoice();
      delay(100);
       }
       else
        {
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("faixa 000"); 
       lcd.print(numero);     
       lcd.setCursor(0,1);
       lcd.print("Vazio !");
        }
     
 }
 //Para aumentar os minutos quando segundos atingirem 59
  if (time>59){
    time=0;
    minutos=minutos+1; 
  }
 
}
 



 

