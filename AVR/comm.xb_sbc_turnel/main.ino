#include <AltSoftSerial.h>
AltSoftSerial  xbSerial;        // RX:8, TX:9, RE:10 (orig. PWM)
const int baud = 9600;

void setup(){
  Serial.begin(baud);
  xbSerial.begin(baud);
}


void loop(){
  if (Serial.available()) xbSerial.write(Serial.read());
  if (xbSerial.available()) Serial.write(xbSerial.read());
}