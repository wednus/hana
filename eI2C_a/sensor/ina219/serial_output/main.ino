#include "Wire.h"
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

float voltage;
float current;
float power;

void setup()   {     
  Serial.begin(9600);
}


void printOutput() {
  Serial.print("Voltage: "); Serial.print(voltage, 3); Serial.println(" V");
  Serial.print("Ampere: "); Serial.print(current, 3); Serial.println(" mA");
  Serial.print("Power: "); Serial.print(power, 3); Serial.println(" mW");
}


void measure() {
  float shuntV = ina219.getShuntVoltage_mV();
  voltage = ina219.getBusVoltage_V();
  current = ina219.getCurrent_mA();
  float loadV = voltage + (shuntV / 1000);
  if (current < 0) {
    current = 0.0;
  }
  power = current * loadV;
}


void loop() {
  measure();
  printOutput();
  delay(1000);
}