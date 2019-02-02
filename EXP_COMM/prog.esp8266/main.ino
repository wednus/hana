#include <AltSoftSerial.h>
AltSoftSerial  xbSerial;        // RX:8, TX:9, RE:10 (orig. PWM)

int baud = 19200;
void setup(){
  pinMode(13, OUTPUT);
  Serial.begin(baud);
  xbSerial.begin(baud);
}


void loop(){
  if (Serial.available()){
    xbSerial.write(Serial.read());    // SBC > XB
    xbSerial.flush();
  }
  if (xbSerial.available()){
    Serial.write(xbSerial.read());  // XB > SBC
    Serial.flush();
  }
}