#include "LedControl_HackIoT.h"
LedControl lc = LedControl(A5,A3,A4,1);  //  (DIN, CLK, LOAD, number of Max7219 chips)

void setup(){
  lc.shutdown(0,false);
  lc.setIntensity(0,15);  // brightness (0 ~ 15)
  lc.clearDisplay(0);
}


void loop(){
  lc.print("kidding??");
}