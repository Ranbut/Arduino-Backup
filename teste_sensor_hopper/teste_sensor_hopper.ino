#define sensorPin 3
#define motorPin A3

long coinPut = 0;
int coin = 0;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensorPin),coinPulse,FALLING);
  pinMode(sensorPin, INPUT);
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin,HIGH);
  }  

void loop()
{
  
  while(Serial.available() == 0){}
  coinPut = Serial.parseInt();
  Serial.println(coinPut);
  digitalWrite(motorPin,LOW);
 }

void coinPulse()
{
    while(digitalRead(sensorPin)){}
    coin++;
    Serial.println(coin);
    if(coin == coinPut)
    {
      coin = 0;
      coinPut = 0;
      digitalWrite(motorPin,HIGH);
    }
}
