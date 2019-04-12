#include <AltSoftSerial.h>
#define baud 57600
AltSoftSerial  xbSerial;        // RX:8, TX:9

void setup(){
  Serial.begin(baud);
  xbSerial.begin(baud);
}


void loop(){
  if (Serial.available()) xbSerial.write(Serial.read());
  if (xbSerial.available()) Serial.write(xbSerial.read());
}