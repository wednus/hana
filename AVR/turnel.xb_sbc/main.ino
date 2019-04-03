#include <AltSoftSerial.h>

#define baud 9600

AltSoftSerial  xbSerial;

void setup(){
  Serial.begin(baud);
  xbSerial.begin(baud);
}


void loop(){
  if (Serial.available()) xbSerial.write(Serial.read());
  if (xbSerial.available()) Serial.write(xbSerial.read());
}