#include <SimpleModbusSlave.h>

const int rePin = 1;  // ignore if <2
const int baud = 9600;

enum{     
  LED_STATE,
  TOTAL_ERRORS,
  // leave this one
  TOTAL_REGS_SIZE 
};

unsigned int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array

void setup(){
  /* parameters(long baudrate, 
                unsigned char ID, 
                unsigned char transmit enable pin, 
                unsigned int holding registers size,
                unsigned char low latency)
                
     The transmit enable pin is used in half duplex communication to activate a MAX485 or similar
     to deactivate this mode use any value < 2 because 0 & 1 is reserved for Rx & Tx.
     Low latency delays makes the implementation non-standard
     but practically it works with all major modbus master implementations.
  */
  
  modbus_configure(baud, 1, rePin, TOTAL_REGS_SIZE, 0);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  holdingRegs[TOTAL_ERRORS] = modbus_update(holdingRegs);
  // read the LED_STATE register value and set the onboard LED high or low with function 16
  digitalWrite(LED_BUILTIN, holdingRegs[LED_STATE]);
}

