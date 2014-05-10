const int SENSOR_PIN = A0;
const float BASELINE_TEMP = 20.0;
const float RANGE_1_TEMP  = BASELINE_TEMP + 2.0;
const float RANGE_2_TEMP  = RANGE_1_TEMP + 2.0;
const float RANGE_3_TEMP  = RANGE_2_TEMP + 2.0;

void setup() {
  Serial.begin(9600);
  
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
}

void loop() {
  // Read the data from the sensor
  int tmpSensorValue = analogRead(SENSOR_PIN);
  
  // Convert it to voltage + Celsisus reading
  float voltage     = getVoltage(tmpSensorValue);
  float temperature = getCelsiusDegFromVoltage(voltage);
  
  // Print out the values for debugging
  printData(tmpSensorValue, voltage, temperature);
  
  if(temperature < RANGE_1_TEMP) {
    ledOff(3);
    ledOff(4);
    ledOff(5);  
  } 
  
  if (temperature > RANGE_1_TEMP) {
    ledOn(3);
    ledOff(4);
    ledOff(5);
  } 
  
  if (temperature > RANGE_2_TEMP) {
    ledOn(3);
    ledOn(4);
    ledOff(5);
  } 
  
  if (temperature > RANGE_3_TEMP) {
    ledOn(3);
    ledOn(4);
    ledOn(5); 
  }
  
  
  delay(1000);
}

float getVoltage(int sensorValue) {
  return (sensorValue/1024.0) * 5.0; 
}

float getCelsiusDegFromVoltage(float voltage) {
  return (voltage - 0.5) * 100.0; 
}

void ledOn(int pin) {
  digitalWrite(pin, HIGH); 
}

void ledOff(int pin) {
  digitalWrite(pin, LOW);
} 

void printData(int sensorValue, float voltage, float celsius) {
  Serial.print("Sensor value: "); Serial.print(sensorValue);
  Serial.print(" | Voltage: "); Serial.print(voltage);
  Serial.print(" | Celsius: "); Serial.println(celsius);
}
