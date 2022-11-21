//Multi-Moedeiro (R$ 1,00)

#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

#define RELE A5

uint16_t counter = 2;
float valor = 0;
uint32_t t;

void setup() {
  Serial.begin(9600);
  Timer1.initialize();
  MFS.initialize(&Timer1);

  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, HIGH);
}


void loop() {

  MFS.write(valor, 2);

  byte btn = MFS.getButton();
  
  if (btn)
  {
    byte buttonNumber = btn & B00111111;
    byte buttonAction = btn & B11000000;
    
    if (buttonAction == BUTTON_PRESSED_IND && buttonNumber == 1)  //Moeda
    {
      MFS.beep(5, 5, 1);
      valor += 0.25;
      counter = 2;
    }
  }

   if(valor >= 1){
      if (millis() - t >= 1000)
  {
    
    t = millis();
    
    if (counter > 0)
    {
      counter--;
      MFS.blinkDisplay(DIGIT_ALL, ON);
      MFS.writeLeds(LED_1, ON);
      MFS.beep(50, 50, 1);
    }
    else
    {
      MFS.writeLeds(LED_1, OFF);
      MFS.blinkDisplay(DIGIT_ALL, OFF);
      counter = 2;
      valor -= 1;
      MFS.writeLeds(LED_2, ON);
      digitalWrite(RELE, LOW);
      delay(150);
      digitalWrite(RELE, HIGH);
      MFS.writeLeds(LED_2, OFF);
    }
   }
}
}
