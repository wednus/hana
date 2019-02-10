#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);	// Fast I2C / TWI 

int audioValue;
// Connect the MEMS AUD output to the Arduino A0 pin
int mic = A0;
// Variables to find the peak-to-peak amplitude of AUD output
const int sampleTime = 50; 
int micOut;
//previous VU value
int preValue = 0; 

void setup(void) {
  Serial.begin(9600);
}

// Find the Peak-to-Peak Amplitude Function
int findPTPAmp(){
// Time variables to find the peak-to-peak amplitude
   unsigned long startTime= millis();  // Start of sample window
   unsigned int PTPAmp = 0; 
// Signal variables to find the peak-to-peak amplitude
   unsigned int maxAmp = 0;
   unsigned int minAmp = 1023;
// Find the max and min of the mic output within the 50 ms timeframe
   while(millis() - startTime < sampleTime){
      micOut = analogRead(mic);
      if( micOut < 1023) //prevent erroneous readings
      {
        if (micOut > maxAmp)
        {
          maxAmp = micOut; //save only the max reading
        }
        else if (micOut < minAmp)
        {
          minAmp = micOut; //save only the min reading
        }
      }
   }
  PTPAmp = maxAmp - minAmp; // (max amp) - (min amp) = peak-to-peak amplitude
  double micOut_Volts = (PTPAmp * 3.3) / 1024; // Convert ADC into voltage
  //Uncomment this line for help debugging (be sure to also comment out the VUMeter function)
  //Serial.println(PTPAmp); d
  //Return the PTP amplitude to use in the soundLevel function. 
  // You can also return the micOut_Volts if you prefer to use the voltage level.
  return PTPAmp;   
}


// Volume Unit Meter function: map the PTP amplitude to a volume unit between 0 and 10.
int VUMeter(int micAmp){
  // Map the mic peak-to-peak amplitude to a volume unit between 0 and 10.
   // Amplitude is used instead of voltage to give a larger (and more accurate) range for the map function.
   // This is just one way to do this -- test out different approaches!
  int fill = map(micAmp, 23, 750, 0, 10); 

  // Only print the volume unit value if it changes from previous value
  while(fill != preValue)
  {
    Serial.println(fill);
    audioValue = fill;
    preValue = fill;
  }
}


void draw(void) {
  int micOutput = findPTPAmp();
  VUMeter(micOutput);
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 16, "-= ADMP401 =-");
  u8g.setPrintPos(0, 42); u8g.print("Audio: ");u8g.print(audioValue);
}


void loop(void) {
  // picture loop
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  // rebuild the picture after some delay
  delay(500);
}
