/* [How to Test]
1. Make XBee connection (one-on-one; transparent)
2. [XCTU] Open the Console menu and make connection
3. [shell] Run 'serial_read.py' 
*/
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
    rsSerial.write(Serial.read());    // SBC > 485
    rsSerial.flush();
  }
  if (rsSerial.available()){
    Serial.write(rsSerial.read());  // 485 > SBC
    Serial.flush();
  }
}