#include <AltSoftSerial.h>
#include <SimpleModbusMasterAltSoftSerial.h>

#define baud 9600
#define timeout 1000
#define polling 200       // the scan rate
#define retry_count 1000  // for demo purpose; 10 is recommended
#define re_pin 1          // <2 to disable

enum{
  PACKET1,
  PACKET2,
  TOTAL_NO_OF_PACKETS
};

Packet packets[TOTAL_NO_OF_PACKETS];
packetPointer packet1 = &packets[PACKET1];
packetPointer packet2 = &packets[PACKET2];

unsigned int regs[2];

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  
  packet1->id = 1;
  packet1->function = READ_HOLDING_REGISTERS;
  packet1->address = 0;
  packet1->no_of_registers = 1;
  packet1->register_array = regs;

  packet2->id = 1;
  packet2->function = PRESET_MULTIPLE_REGISTERS;
  packet2->address = 1;
  packet2->no_of_registers = 1;
  packet2->register_array = regs;

  modbus_configure(baud, timeout, polling, retry_count, re_pin, packets, TOTAL_NO_OF_PACKETS);
}


unsigned int pre_succ;
unsigned long pre_err;

void loop(){
  modbus_update(packets);
  unsigned int successes = packet2->successful_requests;
  unsigned long errors = packet2->total_errors;

  if (successes != pre_succ && errors == pre_err){   // == no new error
    digitalWrite(LED_BUILTIN, regs[0]);
    regs[1] = !regs[0];
  }else{
    pre_err = errors;
    pre_succ = successes;
    digitalWrite(LED_BUILTIN, LOW);
  }
}
