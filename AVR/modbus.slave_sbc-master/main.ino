#include <SimpleModbusSlave.h>

#define baud 9600
#define re_pin 1  // ignore if <2
#define slave_id 1

enum{     
  LED_STATE,
  TOTAL_REGS_SIZE 
};

unsigned int holdingRegs[TOTAL_REGS_SIZE];

void setup(){
  modbus_configure(baud, slave_id, re_pin, TOTAL_REGS_SIZE, 0); // '0' for low latency
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  modbus_update(holdingRegs);
  digitalWrite(LED_BUILTIN, holdingRegs[LED_STATE]);
}

