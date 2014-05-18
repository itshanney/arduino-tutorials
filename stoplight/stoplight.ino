const int GREEN_LED   = 5;
const int YELLOW_LED  = 6;
const int RED_LED     = 7;

const int MODE_CYCLE  = 1;
const int MODE_BLINK  = 2;

const byte RED_MASK    = 0x04;
const byte YELLOW_MASK = 0x02;
const byte GREEN_MASK  = 0x01;

const int ONE_SECOND = 1000;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  allOff();
}

void loop() {
  processMode(MODE_CYCLE);
}

int captureMode() {
  allOn();
  delay(ONE_SECOND);
  allOff();
  
  return MODE_CYCLE; 
}

void processMode(int mode) {
  switch(mode) {
    case MODE_CYCLE:
      modeCycle();
      break;
    default:
      break; 
  }
}

void modeCycle() {
  ledOn(RED_LED);
  delay(ONE_SECOND);
  
  ledOff(RED_LED);
  ledOn(GREEN_LED);
  delay(2*ONE_SECOND);

  ledOff(GREEN_LED);
  ledOn(YELLOW_LED);
  delay(ONE_SECOND);
  
  ledOff(YELLOW_LED);
}

void allOff() {
  ledOff(GREEN_LED);
  ledOff(YELLOW_LED);
  ledOff(RED_LED);
}

void allOn() {
  ledOn(GREEN_LED);
  ledOn(YELLOW_LED);
  ledOn(RED_LED);
}

void ledOff(int led) {
  digitalWrite(led, LOW); 
}

void ledOn(int led) {
  digitalWrite(led, HIGH);
}
