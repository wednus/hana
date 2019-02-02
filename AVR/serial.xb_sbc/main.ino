/* [How to Test]
1. Make XBee connection (one-on-one; transparent)
2. [XCTU] Open the Console menu and make connection
3. [shell] Run 'serial_read.py' 
*/
#include <AltSoftSerial.h>

AltSoftSerial  xbSerial;        // RX:8, TX:9, RE:10 (orig. PWM)

void setup(){
   Serial.begin(9600);
   xbSerial.begin(9600);
}

int i = 0;
void loop(){
  xbSerial.print(i);
  Serial.print(i);
  if (i == 9){
    i = 0;
  }else{
    i++;
  }
  delay(1000);
}