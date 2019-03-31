#include <SoftwareSerial.h>
#include <SimpleModbusSlaveSoftwareSerial.h>

const int rePin = 7;
const int baud = 9600;

//////////////// registers of your slave ///////////////////
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
                unsigned int holding registers size)
                
     The transmit enable pin is used in half duplex communication to activate a MAX485 or similar
     to deactivate this mode use any value < 2 because 0 & 1 is reserved for Rx & Tx
  */
  modbus_configure(baud, 1, rePin, TOTAL_REGS_SIZE);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  holdingRegs[TOTAL_ERRORS] = modbus_update(holdingRegs);
  // read the LED_STATE register value and set the onboard LED high or low with function 16
  digitalWrite(LED_BUILTIN, holdingRegs[LED_STATE]);
}

