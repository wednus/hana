/* Arduino 7 Segment scoreboard 
 * Using the MAX7219CNG LED Driver
 
Created by Yvan / https://Brainy-Bits.com

This code is in the public domain...

You can: copy it, use it, modify it, share it or just plain ignore it!
Thx!

*/

#include "LedControl.h"  // Library used for communcation with 7 segment
LedControl lc=LedControl(A5,A3,A4,1);  //  (DIN, CLK, LOAD, number of Max7219 chips)

// Variable to hold current scores
int displayone=0;
int displaytwo=0;

// Variables to split whole number into single digits
int rightdigit;
int leftdigit;

// Switches pin connection to Arduino UNO
#define switchone 2
#define switchtwo 3


void setup(){
  pinMode(switchone,INPUT_PULLUP);
  pinMode(switchtwo,INPUT_PULLUP);
  lc.shutdown(0,false);  // Wake up MAX7219
  lc.setIntensity(0,7);  // Set brightness to medium
  lc.clearDisplay(0);  // Clear all displays connected to MAX7219 chip #
// Put zeros on both displays at startup
  lc.setDigit(0,0,0,false);  // (Max7219 chip #, Digit, value, DP on or off)
  lc.setDigit(0,1,0,false);
  lc.setDigit(0,2,0,false);
  lc.setDigit(0,3,0,false);
}


void loop(){ 
  // If switch 1 is clicked
  if (!digitalRead(switchone)) {
    displayone++;  // Increase score by 1
    // convert whole number to single digits
    rightdigit=displayone%10;
    leftdigit=displayone%100/10;
    // Display extracted digits on the display
    lc.setDigit(0,0,leftdigit,false);
    lc.setDigit(0,1,rightdigit,false);

    // Wait until switch is released to continue
    while (!digitalRead(switchone)) {}
    delay(5);  // Small delay to debounce the switch
  }

    if (!digitalRead(switchtwo)) {
    displaytwo++;
    rightdigit=displaytwo%10;
    leftdigit=displaytwo%100/10;
    lc.setDigit(0,2,leftdigit,false);
    lc.setDigit(0,3,rightdigit,false);
    while (!digitalRead(switchtwo)) {}    
    delay(5);
  }
}