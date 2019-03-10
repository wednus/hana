// This program demonstrates 3-way communication. (XBee <-> SBC <-> RS485)

#include <stddef.h>
#include <AltSoftSerial.h>
#include <SoftwareSerial.h>
AltSoftSerial  xbSerial;        // RX:8, TX:9, RE:10 (orig. PWM)
SoftwareSerial spSerial(3, 4);  // RX:3, TX:4, RE:7
int rePin = 7;

// define the status request string
const byte stx = 0x02;
const byte etx = 0x03;
const byte maxNumBytes = 25;
byte statReq[] = {0x02, 0x00, 0x00, 0x01, 0x0A, 0x63, 0x06, 0x20, 0x00, 0x00, 0x00, 0xEC, 0xC3, 0x03};

// buffer for skipping unchanged responses
String packet_old;
String packetXB_old = NULL;
String packetSP_old = NULL;

void setup() {
  Serial.begin(9800);     // Comm for SBC
  xbSerial.begin(9800);   // Comm for XB
  spSerial.begin(9800);   // Comm for RS485
  pinMode(rePin, OUTPUT); // RE for RS485
  pinMode(2, OUTPUT);     // RE for SBC
  Serial.print("<HackIoT is ready>");
}


void getStatus(Stream &port, String label){
  byte rb;
  String packet = "\n";
  bool recvInProgress = false;
  int charCount = 0;
  int numRetries = 1000;

  for (int n = 0; n < numRetries; n++) {
    if (charCount > maxNumBytes) return;
    while (port.available() > 0) {
      charCount++;
      rb = port.read();
      if (!recvInProgress) {
        if (rb != stx){
          charCount = 0;
          continue; // skip before STX beginning
        }else
          recvInProgress = true;
      }
      if (rb < 16) packet += '0';  // add appending '0' for 1-digit hexa values
      packet += String (rb, HEX) + " ";
      if (charCount == maxNumBytes && rb == etx && packet != packetXB_old && packet != packetSP_old){
        Serial.print(packet + "(" + label + ")");
        if (label == "XB"){
           packetXB_old = packet;
        }else if(label == "SP"){
           packetSP_old = packet;
        }
        return;
      }
    } // end of while
    delay(1);
  } // end of for
}


void loop() {
  // [Stat Req through XB]
  //xbSerial.write(statReq, sizeof(statReq));
  // Readout possibly returned stat.
  //getStatus(xbSerial, "XB");

  // [Stat Req through RS485]
  // 1. Prep
  //spSerial.listen();  // not required if it's the only SoftwareSerial instance
  while (spSerial.available() != 0) spSerial.read();  // flush late packets
  // 2. Write the Status Req Code
  digitalWrite(rePin, HIGH);
  spSerial.write(statReq, sizeof(statReq));
  digitalWrite(rePin, LOW);
  // 3. Readout
  getStatus(spSerial, "SP");
}