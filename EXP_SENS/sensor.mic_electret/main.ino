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

int micPin = A0;
int getValue(int numSamples){  // returns 0 to 1023
  int avg = 0;
  for(int i = 0; i < numSamples; i++){
    avg += analogRead(micPin);
  }
  avg = avg / numSamples;
  return avg;
}


int ambientLevel = 0;
int fadeStepSize = 0;
int addedSensitivity = 0;
void setup() {
  AnyPWM::init();       // initialize the PWM timer
  pinMode(LED, OUTPUT); // declare LED pin to be an output
  ambientLevel = getValue(1000);
  fadeStepSize = (1024 - ambientLevel - addedSensitivity) / PERIOD;
}


byte brightness = 0;    // how bright the LED is
byte fadeAmount = 5;    // how many points to fade the LED by
byte fadeStep = 0;


void loop() {
  int level = getValue(100) - ambientLevel;
  AnyPWM::analogWrite(LED, level / fadeStepSize);

/*
  brightness = sumSamples / PERIOD;  // 256-step
  fadeStep = brightness / 5;

  for (int i = 0; i < fadeStep; i++){
    AnyPWM::analogWrite(LED, fadeStep * i);
    delay(30);
  }
*/
  //delay(10);
}