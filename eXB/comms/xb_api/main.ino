// Waits for Zigbee packet and print the source address and payload

#include <XBee.h>
#include <AltSoftSerial.h>

AltSoftSerial  xbSerial;        // RX:8, TX:9, NA:10
XBee xbee = XBee();
XBeeResponse resp = XBeeResponse();
ZBRxResponse zb_rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();

void setup(){
  Serial.begin(9600);
  xbSerial.begin(9600);
  xbee.begin(xbSerial);
  Serial.println("(Waiting for API packet..)");
}


void loop(){
  xbee.readPacket();
  // getResponse returns an instance of XBeeResponse class
  resp = xbee.getResponse();
  if (resp.isError()){
    Serial.println("error code: "+ resp.getErrorCode());
    return; // do nothing
  }
  if (resp.isAvailable() && resp.getApiId() == ZB_RX_RESPONSE) {
    resp.getZBRxResponse(zb_rx);
    if (zb_rx.getOption() != ZB_PACKET_ACKNOWLEDGED) {
      Serial.println("error: unknown packet structure");
      return;  // do nothing
    }
    // FrameData: Starts with byte that follows API ID and
    // includes all bytes prior to the checksum
    Serial.print("[");
    uint8_t* data = resp.getFrameData();
    for (int i = 0; i < 8; i++) {
      Serial.print(data[i] < 16 ? "0" : "");
      Serial.print(data[i], HEX);
    }
    Serial.print("] ");
    // print payload
    data = zb_rx.getData();
    String msg;
    for (int i = 0; i < zb_rx.getDataLength(); i++) {
      msg += char(data[i]);
      Serial.print(data[i], HEX);
      Serial.print(' ');
    }
    Serial.println('('+ msg +')');
  }
}
