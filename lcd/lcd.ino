#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const long SECOND_IN_MILLIS = 1000;

const int SWITCH_PIN  = 6;

const int MODE_ONOFF  = 0;
const int MODE_BLINK  = 1;
const int MODE_CYCLE  = 2;

int switchState     = 0;
int prevSwitchState = 0;
int mode            = 0;

int state_red       = 0;
int state_yellow    = 0;
int state_green     = 0;

int cycleStep        = 0;
long cycleMillis     = 0;
long prevCycleMillis = 0;

boolean canChangeMode = false;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  processModeSwitch();
  performMode();
  
  printMode();
  printLightStatus();
}

void doModeCycle() {
  cycleMillis = millis();
  prevCycleMillis = (prevCycleMillis == 0) ? cycleMillis : prevCycleMillis;
  
  if((cycleMillis - prevCycleMillis) >= SECOND_IN_MILLIS) {
    // Reset the millisecond counter
    prevCycleMillis = cycleMillis;
    
    // Advance the cycle step
    cycleStep = (cycleStep == 2) ? 0 : cycleStep + 1;
  }
  
  if(cycleStep == 0) {
    state_red    = 1;
    state_yellow = 0;
    state_green  = 0;
  } else if(cycleStep == 1) {
    state_red    = 0;
    state_yellow = 1;
    state_green  = 0;
  } else if(cycleStep == 2) {
    state_red    = 0;
    state_yellow = 0;
    state_green  = 1;
  }
}

void performMode() {
  if(mode == MODE_CYCLE) {
    doModeCycle();
  }
}

/**
 * Prints out a textual representation of the 
 * current Mode based on an integer value:
 *  0 - On/Off
 *  1 - Blink
 *  2 - Cycle
 */
void printMode() {
  lcd.setCursor(0, 0);
  lcd.print("Mode: ");
  
  if(mode == MODE_ONOFF) {
    lcd.print("On/Off  ");
  } else if(mode == MODE_BLINK) {
    lcd.print("Blink   ");
  } else if(mode == MODE_CYCLE) {
    lcd.print("Cycle   "); 
  } else {
    lcd.print("Unknown "); 
  }
}

/**
 * Prints out the light status On/Off for
 * the individual colors, red, yellow, green
 */
void printLightStatus() {
  lcd.setCursor(0, 1);
  lcd.print("R: ");
  lcd.print(state_red);
  lcd.print(" Y: "); 
  lcd.print(state_yellow);
  lcd.print(" G: ");
  lcd.print(state_green);
}

void processModeSwitch() {
  // Read the state of the push-button
  switchState = digitalRead(SWITCH_PIN);
  
  // Track if button has been released
  if(switchState == LOW) {
    canChangeMode = true;  
  }
  
  // Activate on button push *and* allowance to change mode
  if(switchState == HIGH && canChangeMode) {
    canChangeMode = false;  
    mode++;
   
    // Cycle back to beginning
    if(mode > MODE_CYCLE) {
      mode = MODE_ONOFF;
    } 
    
    printMode();
    turnLightsOff();
  }
}

void turnLightsOff() {
  state_red    = 0;
  state_yellow = 0;
  state_green  = 0; 
}
