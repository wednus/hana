#include <SimpleModbusMaster.h>
#define baud 9600
#define timeout 1000
#define polling 200 // the scan rate
#define retry_count 10
#define TxEnablePin 2 

enum{
  PACKET1,
  PACKET2,
  // leave this last entry
  TOTAL_NO_OF_PACKETS
};

Packet packets[TOTAL_NO_OF_PACKETS];
packetPointer packet1 = &packets[PACKET1];
packetPointer packet2 = &packets[PACKET2];

unsigned int regs[1];

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);

  // access the Slave #1
  // These addressing should be matched to the slave's register mapping.
  packet1->id = 1;
  packet1->function = READ_HOLDING_REGISTERS;
  packet1->address = 0;
  packet1->no_of_registers = 1;
  packet1->register_array = regs;
  
  // write the 1 register to the PLC starting at address 0
  packet2->id = 1;
  packet2->function = PRESET_MULTIPLE_REGISTERS;
  packet2->address = 0;
  packet2->no_of_registers = 1; // set LED_STATE value
  packet2->register_array = regs;

  modbus_configure(baud, timeout, polling, retry_count, TxEnablePin, packets, TOTAL_NO_OF_PACKETS);
}

unsigned int pre_successe;
unsigned long pre_errors;

void loop(){
  // connection_status method doesn't represent most up to date state.
  // unsigned int connection_status = modbus_update(packets);
  modbus_update(packets);
  unsigned int successes = packet2->successful_requests;
  unsigned long errors = packet2->total_errors;
  
  // we use status counters instead.
  if (successes != pre_successe && errors == pre_errors){   // == no new error
    byte ledState = packet1->register_array[0];
    digitalWrite(LED_BUILTIN, ledState);
    regs[0] = !ledState;  // send toggled led state
    delay(800);
  }else{
    pre_errors = errors;
    pre_successe = successes;
    digitalWrite(LED_BUILTIN, LOW);
  }
}
