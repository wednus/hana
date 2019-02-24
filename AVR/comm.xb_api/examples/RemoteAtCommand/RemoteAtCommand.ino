/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 *
 * This file is part of XBee-Arduino.
 *
 * XBee-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XBee-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <XBee.h>
#include <AltSoftSerial.h>

/*
This example is for Series 1 (10C8 or later firmware) or Series 2 XBee
Sends two Remote AT commands to configure the remote radio for I/O line monitoring

This example uses the SoftSerial library to view the XBee communication.  I am using a
Modern Device USB BUB board (http://moderndevice.com/connect) and viewing the output
with the Arduino Serial Monitor.
*/


AltSoftSerial  xbSerial;        // RX:8, TX:9, RE:10 (orig. PWM)
XBee xbee = XBee();

// Turn on I/O sampling
uint8_t irCmd[] = {'I','R'};
// Set sample rate to 65 seconds (0xffff/1000)
uint8_t irValue[] = { 0xff, 0xff };

// Set DIO0 (pin 20) to Analog Input
uint8_t d0Cmd[] = { 'D', '0' };
uint8_t d0Value[] = { 0x2 };

// SH + SL of your remote radio
XBeeAddress64 remoteAddress = XBeeAddress64(0x0013a200, 0x40F7478B);
// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, irCmd, irValue, sizeof(irValue));

// Create a Remote AT response object
RemoteAtCommandResponse remoteAtResponse = RemoteAtCommandResponse();

void sendRemoteAtCommand() {
  Serial.println("Sending command to the XBee");

  // send the command
  xbee.send(remoteAtRequest);

  // wait up to 5 seconds for the status response
  if (xbee.readPacket(5000)) {
    // got a response!

    // should be an AT command response
    if (xbee.getResponse().getApiId() == REMOTE_AT_COMMAND_RESPONSE) {
      xbee.getResponse().getRemoteAtCommandResponse(remoteAtResponse);

      if (remoteAtResponse.isOk()) {
        Serial.print("Command [");
        Serial.print(remoteAtResponse.getCommand()[0]);
        Serial.print(remoteAtResponse.getCommand()[1]);
        Serial.println("] was successful!");

        if (remoteAtResponse.getValueLength() > 0) {
          Serial.print("Command value length is ");
          Serial.println(remoteAtResponse.getValueLength(), DEC);

          Serial.print("Command value: ");

          for (int i = 0; i < remoteAtResponse.getValueLength(); i++) {
            Serial.print(remoteAtResponse.getValue()[i], HEX);
            Serial.print(" ");
          }

          Serial.println("");
        }
      } else {
        Serial.print("Command returned error code: ");
        Serial.println(remoteAtResponse.getStatus(), HEX);
      }
    } else {
      Serial.print("Expected Remote AT response but got ");
      Serial.print(xbee.getResponse().getApiId(), HEX);
    }
  } else if (xbee.getResponse().isError()) {
    Serial.print("Error reading packet.  Error code: ");
    Serial.println(xbee.getResponse().getErrorCode());
  } else {
    Serial.print("No response from radio");
  }
}


void setup() {
  Serial.begin(9600);
  xbSerial.begin(9600);
  xbee.begin(xbSerial);

 // When powered on, XBee radios require a few seconds to start up
 // and join the network.
 // During this time, any packets sent to the radio are ignored.
 // Series 2 radios send a modem status packet on startup.

 // it took about 4 seconds for mine to return modem status.
 // In my experience, series 1 radios take a bit longer to associate.
 // Of course if the radio has been powered on for some time before the sketch runs,
 // you can safely remove this delay.
 // Or if you both commands are not successful, try increasing the delay.

 delay(5000);
}

void loop() {
  sendRemoteAtCommand();

  // now reuse same object for DIO0 command
  remoteAtRequest.setCommand(d0Cmd);
  remoteAtRequest.setCommandValue(d0Value);
  remoteAtRequest.setCommandValueLength(sizeof(d0Value));

  sendRemoteAtCommand();

  // it's a good idea to clear the set value so that the object can be reused for a query
  remoteAtRequest.clearCommandValue();

  Serial.println();
}
