#include <SoftwareSerial.h>
#include <AltSoftSerial.h>

AltSoftSerial  xbSerial;        // RX:8, TX:9, RE:10 (orig. PWM)
SoftwareSerial spSerial(3, 4);  // RX:3, TX:4, RE:7
int rePin = 7;

void setup(){
  xbSerial.begin(9600);   // Comm for XB
  spSerial.begin(9600);   // Comm for RS485
  pinMode(rePin, OUTPUT); // RE for RS485
  pinMode(2, OUTPUT);     // RE for SBC
}


void loop(){
  if (spSerial.available()){
    digitalWrite(rePin, HIGH);
    spSerial.write(xbSerial.read());  // XB > 485
    spSerial.flush();                 // wait for the trasnmission of outgoing data
    digitalWrite(rePin, LOW);
  }
  if (spSerial.available()){
    xbSerial.write(spSerial.read());  // 485 > XB
    xbSerial.flush();
  }
}