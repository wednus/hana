// AnyPWM by Nick Borko  
// This work is licensed under a Creative Commons  
// Attribution-ShareAlike 3.0 Unported License  
// http://nicks-liquid-soapbox.blogspot.com/2011/02/pwm-on-any-digital-pin-on-arduino.html
#include <FlexiTimer2.h>

// LED to pulse (non-PWM pin)
#define LED 13

// Period of the PWM wave (and therefore the number of levels)
#define PERIOD 256

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

void setup() {
  AnyPWM::init();       // initialize the PWM timer
  pinMode(LED, OUTPUT); // declare LED pin to be an output
}

byte brightness = 0;    // how bright the LED is
byte fadeAmount = 5;    // how many points to fade the LED by

void loop() {
  // set the brightness of the LED:
  AnyPWM::analogWrite(LED, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}