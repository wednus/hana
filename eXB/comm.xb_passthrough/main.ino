#include <AltSoftSerial.h>
AltSoftSerial  xbSerial;        // RX:8, TX:9, RE:10 (orig. PWM)

void setup(){
  Serial.begin(9600);
  xbSerial.begin(9600);
}


void loop(){
  if (Serial.available()) xbSerial.write(Serial.read());
  if (xbSerial.available()) Serial.write(xbSerial.read());
}