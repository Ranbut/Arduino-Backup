#define sensorPin 3


void setup() {

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensorPin),coinPulse,FALLING);
  pinMode(sensorPin, INPUT);
 
}

void loop() {
  
 
}

void coinPulse()

{
  Serial.println("Ok");
}
