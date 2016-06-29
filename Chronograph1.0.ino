#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

const byte pinRead1 = A1;
const byte pinRead2 = A0;

int threshFirst;
int threshSecond;
const float ledFactor = 0.9;

unsigned long int startTime;
unsigned long int endTime;
unsigned long int FPS;

int arrayFPS[100];
int shotCount = 0;
long sumFPS;
int averageFPS;



void setup() {
lcd.begin(16,2);
lcd.print("Calibrating");
threshFirst = ledFactor * analogRead(pinRead1);
threshSecond = ledFactor * analogRead(pinRead2);
delay(2000);
lcd.clear();
lcd.print("Ready");
}

void loop() {
if (analogRead(pinRead1) <= threshFirst) {
  startTime = micros();
  shotCount ++;
  sumFPS = 0;
  lcd.clear();
  
  while(analogRead(pinRead2) >= threshSecond) {
  }
  endTime = micros();
  FPS = 500000/(endTime - startTime);
  arrayFPS[shotCount - 1] = FPS;
 
  for (int storedSpeed = 0; storedSpeed < shotCount; storedSpeed++){
    sumFPS = sumFPS + arrayFPS[storedSpeed];
  }
  
  averageFPS = sumFPS / shotCount;
   
  lcd.print("Shot ");
  lcd.print(shotCount);
  lcd.print(":");
  
  lcd.setCursor(8,0);
  lcd.print(FPS);
  lcd.print(" FPS");

  lcd.setCursor(0,1);
  lcd.print("Average: ");
  lcd.print(averageFPS);
  lcd.print("FPS");
  
  
  delay(2000);
  }
}


