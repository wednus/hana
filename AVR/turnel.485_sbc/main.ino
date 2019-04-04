#include <SoftwareSerial.h>

#define baud 9600
#define re_pin 7

SoftwareSerial rsSerial(3, 4);  // RX:3, TX:4, RE:7

void setup(){
  Serial.begin(baud);
  rsSerial.begin(baud);
  pinMode(re_pin, OUTPUT); // RE for RS485
}


void loop(){
  if (Serial.available()){
    PORTD |= B10000000;
    rsSerial.write(Serial.read());    // SBC > RS485
    // [IMPORTANT]: rsSerial.read will read-back ('00') immediatly without it.
    rsSerial.flush();
    PORTD &= B01111111;
  }

  if (rsSerial.available()){
    Serial.write(rsSerial.read());    // RS485 > SBC
    Serial.flush();
  }
}


/*
// For packetized rx/tx
void loop(){
  if (Serial.available()){
    PORTD |= B10000000;
    while (Serial.available()){
      rsSerial.write(Serial.read());    // SBC > RS485
    }
    rsSerial.flush();
    PORTD &= B01111111;
  }

  if (rsSerial.available()){
    while (rsSerial.available()){
      Serial.write(rsSerial.read());    // RS485 > SBC
    }
    Serial.flush();
  }
}
*/