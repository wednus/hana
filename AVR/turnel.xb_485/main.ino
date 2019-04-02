#include <AltSoftSerial.h>
#include <SoftwareSerial.h>

AltSoftSerial  xbSerial;        // RX:8, TX:9, RE:10 (orig. PWM)
SoftwareSerial spSerial(3, 4);  // RX:3, TX:4, RE:7
const int rePin = 7;
const int baud = 9600;
const int maxBufSize = 100;     // must be bigger than max packet size
char buf[maxBufSize];
int index = 0;

void setup(){
  Serial.begin(baud);
  xbSerial.begin(baud);   // Comm for XB
  spSerial.begin(baud);   // Comm for RS485
  pinMode(rePin, OUTPUT); // RE for RS485
}


void loop(){
  if (spSerial.available()){
    xbSerial.write(spSerial.read());  // 485 > XB
  }

  delay(1);  // [IMPORTANT] adjust delay per the response timing

  if(xbSerial.available()){
    if(index < maxBufSize){  // prevent out-of-boundary error
      buf[index++] = xbSerial.read();
    }else{
      index = 0;
    }
  }else if(index != 0){
    //Serial.write((const uint8_t*)buf, index);
    //Serial.flush();
    PORTD |= B10000000;
    spSerial.write((const uint8_t*)buf, index);
    spSerial.flush();
    PORTD &= B01111111;
    index = 0;
  }
}