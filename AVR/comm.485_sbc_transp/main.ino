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
    PORTD |= B10000000;
    rsSerial.write(Serial.read());    // SBC > RS485
    PORTD &= B01111111;
    rsSerial.flush();                 // wait for the trasnmission of outgoing data
  }

  if (rsSerial.available()){
    Serial.write(rsSerial.read());    // RS485 > SBC
    Serial.flush();
  }
}