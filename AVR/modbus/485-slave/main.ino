#include <SoftwareSerial.h>
#include <SimpleModbusSlaveSoftwareSerial.h>

#define baud 9600
#define re_pin 7
#define slave_id 1

enum{
  LED_NEXT,
  LED_NOW,
  TOTAL_ERRORS,
  // leave this one
  TOTAL_REGS_SIZE 
};

unsigned int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array

void setup(){
  modbus_configure(baud, slave_id, re_pin, TOTAL_REGS_SIZE);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  holdingRegs[TOTAL_ERRORS] = modbus_update(holdingRegs);
  // read the LED_STATE register value and set the onboard LED high or low with function 16
  digitalWrite(LED_BUILTIN, holdingRegs[LED_NOW]);
  holdingRegs[LED_NEXT] = !holdingRegs[LED_NOW];
}
