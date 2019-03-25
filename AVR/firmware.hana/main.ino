/*
HackIoT Hana Official Firmware
 - Sundew Shin - sundew@wednus.com
 - 3/25/2019 (v032519)
 - http://flat.wednus.com/forum
*/

#include <AltSoftSerial.h>
#include <SoftwareSerial.h>
#include <FlexiTimer2.h>
#define PERIOD 256

AltSoftSerial  xbSerial;        // RX:8, TX:9, RE:10 (orig. PWM)
SoftwareSerial spSerial(3, 4);  // RX:3, TX:4, RE:7
const int rePin = 7;
const int baud = 9600;
const int maxBufSize = 100;     // must be bigger than max packet size
char buf[maxBufSize];
int index = 0;
bool isStarted = false;

namespace AnyPWM {
  extern volatile byte pinLevel[12];
  void pulse();
  void analogWrite(byte pin, byte level);
  void init();
}

// Variables to keep track of the pin states
volatile byte AnyPWM::pinLevel[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Set a digital out pin to a specific level
void AnyPWM::analogWrite(byte pin, byte level) {
  if (pin > 1 && pin < 14 && level >= 0 && level < PERIOD) {
    pin -= 2;
    AnyPWM::pinLevel[pin] = level;
    if (level == 0) {
      digitalWrite(pin + 2, LOW);
    }
  }
}

// Initialize the timer routine; must be called before calling
// AnyPWM::analogWrite!
void AnyPWM::init() {
  // (PERIOD * 64) Hertz seems to be a high enough frequency to produce
  // a steady PWM signal on all 12 output pins
  FlexiTimer2::set(1, 1.0/(PERIOD * 64), AnyPWM::pulse);
  FlexiTimer2::start();
}

// Routine to emit the PWM on the pins
void AnyPWM::pulse() {
  static int counter = 0;
  for(int i = 0; i < 12; i += 1) {
    if (AnyPWM::pinLevel[i]) {
      digitalWrite(i + 2, AnyPWM::pinLevel[i] > counter);
    }
  }
  counter = ++counter > PERIOD ? 0 : counter;
}


byte brightness = 0;    // how bright the LED is
byte fadeAmount = 5;    // how many points to fade the LED by
void fade() {
  // set the brightness of the LED:
  AnyPWM::analogWrite(LED_BUILTIN, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}


void setup(){
  Serial.begin(baud);
  xbSerial.begin(baud);   // Comm for XB
  spSerial.begin(baud);   // Comm for RS485
  pinMode(rePin, OUTPUT); // RE for RS485
  pinMode(LED_BUILTIN, OUTPUT); // Comm Status indicator
  
  AnyPWM::init();         // initialize the PWM timer
  for (int i = 0; i < 307; i++){
    fade();
  }
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(60);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(60);
  digitalWrite(LED_BUILTIN, LOW);
  delay(60);
  digitalWrite(LED_BUILTIN, HIGH);
}


void loop(){
  if (spSerial.available()){  // 485 > XB
    if(!isStarted){
      digitalWrite(LED_BUILTIN, HIGH);  // RESPOND SENT [SUCCESS]
      isStarted = true;
    }
    xbSerial.write(spSerial.read());
  }

  delay(1);  // [IMPORTANT] adjust delay per the response timing

  if(xbSerial.available()){   // XB > 485
    if(index < maxBufSize){   // prevent out-of-boundary error
      buf[index++] = xbSerial.read();
    }else{
      index = 0;
    }
  }else if(index != 0){
    //Serial.write((const uint8_t*)buf, index);
    //Serial.flush();
    PORTD |= B10000000;
    spSerial.write((const uint8_t*)buf, index);
    spSerial.flush();
    PORTD &= B01111111;

    digitalWrite(LED_BUILTIN, LOW);  // COMMAND RECEIVED [SUCCESS]
    isStarted = false;
    delay(100);
    index = 0;
  }
}