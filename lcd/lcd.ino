#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int SWITCH_PIN  = 6;

int switchState     = 0;
int prevSwitchState = 0;
int mode            = 0;


void setup() {
  lcd.begin(16, 2);
  
  pinMode(SWITCH_PIN, INPUT);
  
  lcd.print("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.print("Mode: ");
  lcd.print(mode);
}

void loop() {
  switchState = digitalRead(SWITCH_PIN);
  
  if(switchState == HIGH) {
    mode++; 
  }
  
  lcd.setCursor(0, 1);
  lcd.print("Mode: ");
  lcd.print(mode);
}
