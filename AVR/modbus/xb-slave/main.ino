#include <AltSoftSerial.h>
#include <SimpleModbusSlaveAltSoftSerial.h>

#define baud 9600
#define re_pin 1    // <2 to disable
#define slave_id 1

enum{
  LED_NEXT,
  LED_NOW,
  TOTAL_REGS_SIZE 
};

unsigned int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array

void setup(){
  modbus_configure(baud, slave_id, re_pin, TOTAL_REGS_SIZE);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  modbus_update(holdingRegs);
  // read the LED_STATE register value and set the onboard LED high or low with function 16
  digitalWrite(LED_BUILTIN, holdingRegs[LED_NOW]);
  holdingRegs[LED_NEXT] = !holdingRegs[LED_NOW];
}
