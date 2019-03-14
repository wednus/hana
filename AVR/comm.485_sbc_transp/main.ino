#include <SoftwareSerial.h>

SoftwareSerial rsSerial(3, 4);  // RX:3, TX:4, RE:7
int rePin = 7;

void setup(){
  Serial.begin(9600);
  rsSerial.begin(9600);
  pinMode(rePin, OUTPUT); // RE for RS485
  pinMode(2, OUTPUT);     // RE for SBC   
}


void loop(){
  if (Serial.available()){
    digitalWrite(rePin, HIGH);
    rsSerial.write(Serial.read());    // SBC > RS485
    rsSerial.flush();                 // wait for the trasnmission of outgoing data
    digitalWrite(rePin, LOW);
  }
  if (rsSerial.available()){
    Serial.write(rsSerial.read());    // RS485 > SBC
    Serial.flush();
  }
}