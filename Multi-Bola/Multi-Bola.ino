//Multi-Bola (R$ 2,00)

#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <AccelStepper.h>           // Load the AccelStepper library

#define motorPin1  A5                // IN1 pin on the ULN2003A driver
#define motorPin2  5                // IN2 pin on the ULN2003A driver
#define motorPin3  6               // IN3 pin on the ULN2003A driver
#define motorPin4  9               // IN4 pin on the ULN2003A driver

#define RELE A5

uint16_t counter = 2;
float valor = 0;
uint32_t t1;
uint32_t t2;
bool ligado = false;
bool stepperOn = false;

int stepsPerRevolution = 64;        // steps per revolution
float degreePerRevolution = 5.625;  // degree per revolution

AccelStepper stepper(AccelStepper::HALF4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  Serial.begin(9600);
  Timer1.initialize();
  MFS.initialize(&Timer1);

  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, HIGH);

  stepper.setMaxSpeed(1000.0);      // set the max motor speed
  stepper.setAcceleration(1000.0);   // set the acceleration
  stepper.setSpeed(200);            // set the current speed
}


void loop() {

  Serial.print(counter);

  MFS.write(valor, 2);

  byte btn = MFS.getButton();
  
  if (btn)
  {
    byte buttonNumber = btn & B00111111;
    byte buttonAction = btn & B11000000;
    
    if (buttonAction == BUTTON_PRESSED_IND && buttonNumber == 1) //Moeda de RS 2,00
    {
      MFS.beep(5, 5, 1);
      valor += 0.25;
      counter = 2;
    }

    if (buttonAction == BUTTON_PRESSED_IND && buttonNumber == 2 && ligado == true) //Sensor
    {
      ligado = false;
      MFS.blinkDisplay(DIGIT_ALL, OFF);
      MFS.writeLeds(LED_1, OFF);
      digitalWrite(RELE, HIGH);
    }
    if (buttonAction == BUTTON_PRESSED_IND && buttonNumber == 3) //Moeda de RS 1,00
    {
      MFS.beep(5, 5, 1);
      valor += 1;
      counter = 2;
    }
  }

  if(ligado == true){
    if (millis() - t2 >= 1000)
  {
    
    t2 = millis();
    
    if (counter > 0)
    {
      counter--;
      MFS.blinkDisplay(DIGIT_ALL, ON);
      MFS.writeLeds(LED_1, ON);
    }
    else
    {
      MFS.blinkDisplay(DIGIT_ALL, OFF);
      MFS.writeLeds(LED_1, OFF);
      ligado = false;
      digitalWrite(RELE, HIGH);
    }
  }
  }

   if(valor >= 1){
      if (millis() - t1 >= 1000)
  {
    
    t1 = millis();
    
    if (counter > 0)
    {
      counter--;
      MFS.blinkDisplay(DIGIT_ALL, ON);
      MFS.writeLeds(LED_1, ON);
    }
    else
    {
      MFS.writeLeds(LED_1, OFF);
      MFS.blinkDisplay(DIGIT_ALL, OFF);
      ligado = true;
      counter = 5;
      valor -= 1;
      MFS.writeLeds(LED_2, ON);
      delay(150);
      digitalWrite(RELE, LOW);
      MFS.writeLeds(LED_2, OFF);
      stepper.move-/(degToSteps(360));
    }
   }
}
stepper.run();
}
float degToSteps(float deg) {
  return (stepsPerRevolution / degreePerRevolution) * deg;
}
