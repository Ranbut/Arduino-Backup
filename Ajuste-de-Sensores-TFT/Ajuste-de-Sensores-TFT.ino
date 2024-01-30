#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include "DHT.h"
#define DHTPIN 21  
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
 
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define LIGADO  0x07E0
#define DESLIGADO 0xF800

#define keyboardPin 31
#define moneyPin    33
#define sasPin      35
#define cpuPin      37
#define buzzerPin   39

int keyboardState = 0;
int lastKeyboardState = 1;

int moneyState = 0;
int lastMoneyState= 1;

int sasState = 0;
int lastSASState = 1;

int cpuState = 0;
int lastCPUState = 1;

long corBot[4] = {DESLIGADO, DESLIGADO, DESLIGADO, DESLIGADO};

void setup(void)
{
    Serial.begin(9600);
    
    pinMode(keyboardPin, INPUT_PULLUP);
    pinMode(moneyPin, INPUT_PULLUP);
    pinMode(sasPin, INPUT_PULLUP);
    pinMode(cpuPin, INPUT_PULLUP);
    
    pinMode(buzzerPin, OUTPUT);
    
    dht.begin();
    tft.begin(0x9341);
    tft.fillScreen(BLACK);
    tft.setTextColor(YELLOW, BLACK);
    tft.setTextSize(2);
    IntroScreen();
  
    tft.setTextColor(WHITE);
    tft.setTextSize (3);

    tft.fillRect  (40, 20 , 160, 40, corBot[0]);
    tft.setCursor(55, 30);
    tft.println("Teclado");

    tft.fillRect  (40, 100, 160, 40, corBot[1]);
    tft.setCursor(55, 110);
    tft.println("Noteiro");

    tft.fillRect  (40, 180, 160, 40, corBot[2]);
    tft.setCursor(60, 190);
    tft.println("  SAS");

    tft.fillRect  (40, 260, 160, 40, corBot[3]);
    tft.setCursor(60, 270);
    tft.println("  CPU");
}

void loop() {
  check_buttons();

  draw_Buttons();
}

void IntroScreen() {
  tft.setCursor (70, 60);
  tft.setTextSize (5);
  tft.setTextColor(RED);
  tft.println("NVC");
  tft.setTextColor(WHITE);
  tft.setTextSize (3);
  tft.setCursor (30, 140);
  tft.println("Ajuste");
  tft.setCursor (30, 180);
  tft.println("de");
  tft.setCursor (30, 220);
  tft.println("Sensores");

  NVC_logo_drawing(5, 500);
 
  tft.fillScreen(BLACK);
}

void NVC_logo_drawing(int loops, int flashDelay){
    while(loops != 0){
    delay(flashDelay);
    tft.setCursor (70, 60);
    tft.setTextSize (5);
    tft.setTextColor(RED);
    tft.println("NVC");
    delay(flashDelay);
    tft.setCursor (70, 60);
    tft.setTextSize (5);
    tft.setTextColor(GREEN);
    tft.println("NVC");
    delay(flashDelay);
    tft.setCursor (70, 60);
    tft.setTextSize (5);
    tft.setTextColor(BLUE);
    tft.println("NVC");
  
    loops--;
  }
}

void check_buttons(){
  keyboardState = digitalRead(keyboardPin);
  moneyState = digitalRead(moneyPin);
  sasState = digitalRead(sasPin);
  cpuState = digitalRead(cpuPin);

  Serial.print("Last: ");
  Serial.print(lastKeyboardState);
  Serial.print("; Current: ");
  Serial.print(keyboardState);
  Serial.println(" ");

  if(keyboardState == LOW){
    corBot[0] = LIGADO;
  }
  else{
    corBot[0] = DESLIGADO;
  }

  if(moneyState == LOW){
    corBot[1] = LIGADO;
  }
  else{
    corBot[1] = DESLIGADO;
  }

  if(sasState == LOW){
    corBot[2] = LIGADO;
  }
  else{
    corBot[2] = DESLIGADO;
  }

  if(cpuState == LOW){
    corBot[3] = LIGADO;
  }
  else{
    corBot[3] = DESLIGADO;
  }
}

void draw_Buttons() {
  tft.setTextColor(WHITE);
  tft.setTextSize (3);
  
  if (lastKeyboardState != keyboardState){
    tft.fillRect  (40, 20 , 160, 40, corBot[0]);
    tft.setCursor(55, 30);
    tft.println("Teclado");
    lastKeyboardState = keyboardState;
  }
  if (lastMoneyState != moneyState){
    tft.fillRect  (40, 100, 160, 40, corBot[1]);
    tft.setCursor(55, 110);
    tft.println("Noteiro");
    lastMoneyState = moneyState;
  }
  if (lastSASState != sasState){
    tft.fillRect  (40, 180, 160, 40, corBot[2]);
    tft.setCursor(60, 190);
    tft.println("  SAS");
    lastSASState = sasState;
  }
  if (lastCPUState != cpuState){
    tft.fillRect  (40, 260, 160, 40, corBot[3]);
    tft.setCursor(60, 270);
    tft.println("  CPU");
    lastCPUState = cpuState;
  }
}
