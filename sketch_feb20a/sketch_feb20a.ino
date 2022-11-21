const int coinButton = 2;
int coinState = 0;

int const sensorPin = 3;
int sensorState = 0;

#define rele A3

int count = 0;

void setup() {
  Serial.begin(9600);

  pinMode(coinButton, INPUT_PULLUP);
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH); 
}

void loop() {
  coinState = digitalRead(coinButton);
  sensorState = digitalRead(sensorPin);


  if(sensorState == LOW)
  {
      digitalWrite(rele, LOW);
  }
  else
  {
      count++;
      Serial.print("Contando: ");
      Serial.println(count);
      digitalWrite(rele, HIGH);
      delay(2000);
  }
}
