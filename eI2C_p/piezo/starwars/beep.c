#include <wiringPi.h>
#include <stdio.h>

//Pin 11 on Raspberry Pi corresponds to BCM GPIO 17 and wiringPi pin 0
#define BeepPin 8

int main(void)
{
  if(-1 == wiringPiSetup())
  {
      printf("setup wiringPi failed!");
      return 1;
  }

  //Set GPIO pin
  pinMode(BeepPin, OUTPUT);

  //Play a sound until the user closes the app
  while(1)
  {
    digitalWrite(BeepPin, LOW);
    delay(2);
    digitalWrite(BeepPin, HIGH);
    delay(2);
  }

  return 0;
}
