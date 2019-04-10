int audioValue;
const int mic = A5; // ADC5 (or SCL)
const int sampleTime = 50; 
int micOut;
int preValue = 0; 

void setup(void) {
  Serial.begin(9600);
}

// Find the Peak-to-Peak Amplitude
int findPTPAmp(){
   unsigned long startTime= millis();  // Start of sample window
   unsigned int PTPAmp = 0; 
   // Signal variables to find the peak-to-peak amplitude
   unsigned int maxAmp = 0;
   unsigned int minAmp = 1023;
   // Find the max and min of the mic output within the 50 ms timeframe
   while(millis() - startTime < sampleTime){
      micOut = analogRead(mic);
      if( micOut < 1023){  // limit input (exclude out-of-range input)
        if (micOut > maxAmp){
          maxAmp = micOut;
        }else if (micOut < minAmp){
          minAmp = micOut;
        }
      }
   }
  PTPAmp = maxAmp - minAmp;
  double micOut_Volts = (PTPAmp * 3.3) / 1024; // Convert ADC into voltage
  return PTPAmp;   
}


// Volume Unit Meter function: map the PTP amplitude to a volume unit between 0 and 10.
int VUMeter(int micAmp){
  // Map the mic peak-to-peak amplitude to a volume unit between 0 and 10.
   // Amplitude is used instead of voltage to give a larger (and more accurate) range for the map function.
   // This is just one way to do this -- test out different approaches!
  int fill = map(micAmp, 23, 750, 0, 10); 

  // Only print the volume unit value if it changes from previous value
  while(fill != preValue){
    Serial.println(fill);
    audioValue = fill;
    preValue = fill;
  }
}


void loop(void) {
  VUMeter(findPTPAmp());
  delay(10);
}
