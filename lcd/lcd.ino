#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const long SECOND_IN_MILLIS = 1000;

const int SWITCH_PIN  = 6;

const int MODE_ONOFF  = 0;
const int MODE_BLINK  = 1;
const int MODE_CYCLE  = 2;

int switch_state = 0;
int mode         = 0;

int state_red    = 0;
int state_yellow = 0;
int state_green  = 0;

int cycle_step         = 0;
long cycle_millis      = 0;
long prev_cycle_millis = 0;

boolean can_change_mode = false;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  process_mode_switch();
  perform_mode();
  print_status();
}

/**
 * Method that will process the Cycle mode
 * 
 * The Cycle mode is simply a mode where the light will operate
 * as if it were a normal traffic light, alternating between
 * Red, Green and Yellow with a one second delay between changes.
 * 
 * The delay does not use the delay() method to halt the program
 * but will use a millisecond counter and compare that against an
 * interval (i.e. one second) and will adjust the counter if the
 * interval has been reached.
 */
void do_mode_cycle() {
  cycle_millis = millis();
  prev_cycle_millis = (prev_cycle_millis == 0) ? cycle_millis : prev_cycle_millis;
  
  if((cycle_millis - prev_cycle_millis) >= SECOND_IN_MILLIS) {
    // Reset the millisecond counter
    prev_cycle_millis = cycle_millis;
    
    // Advance the cycle step
    cycle_step = (cycle_step == 2) ? 0 : cycle_step + 1;
  }
  
  // Set the Light state
  if(cycle_step == 0) {
    state_red    = 1;
    state_yellow = 0;
    state_green  = 0;
  } else if(cycle_step == 1) {
    state_red    = 0;
    state_yellow = 1;
    state_green  = 0;
  } else if(cycle_step == 2) {
    state_red    = 0;
    state_yellow = 0;
    state_green  = 1;
  }
}

/**
 * Method that processes the particular Mode the controller is in
 * based on the selection from the input switch/
 */
void perform_mode() {
  if(mode == MODE_CYCLE) {
    do_mode_cycle();
  }
}

/**
 * Prints out a textual representation of the current Mode based 
 * the following table of values:
 *  0 - On/Off
 *  1 - Blink
 *  2 - Cycle
 */
void print_mode() {
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
 * Prints out the light status On/Off for the individual colors
 * Red, Yellow and Green.
 */
void print_light_status() {
  lcd.setCursor(0, 1);
  lcd.print(" R: "); lcd.print(state_red);
  lcd.print(" Y: "); lcd.print(state_yellow);
  lcd.print(" G: "); lcd.print(state_green);
}

/**
 * Prints out the current status of the program on the 2-line LCD.
 * 
 * The first line contains the Mode the program is currently running
 * while the second line is the Light Status. Example:
 *
 * "Mode: On/Off"
 * " R: 0 Y: 0 G: 1 "
 */
void print_status() {
  print_mode();
  print_light_status();
}

/**
 * Method that processes the Mode selection input switch
 *
 * In order to change the Mode, the button has to be pushed
 * *and then* released to register the Mode change.
 */
void process_mode_switch() {
  // Read the state of the push-button
  switch_state = digitalRead(SWITCH_PIN);
  
  // Track if button has been released
  if(switch_state == LOW) {
    can_change_mode = true;  
  }
  
  // Activate on button push *and* allowance to change mode
  if(switch_state == HIGH && can_change_mode) {
    can_change_mode = false;  
    mode++;
   
    // Cycle back to beginning
    if(mode > MODE_CYCLE) {
      mode = MODE_ONOFF;
    } 
    
    turn_lights_off();
  }
}

/**
 * Method that simply turns off all of the lights as a reset
 */
void turn_lights_off() {
  state_red    = 0;
  state_yellow = 0;
  state_green  = 0; 
}
