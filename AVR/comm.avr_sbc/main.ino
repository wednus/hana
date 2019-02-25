void setup(){
  Serial.begin(9600);
}

String line = "";
void loop(){
  while (Serial.available()) {
    delay(3);  //delay to allow buffer to fill 
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer
      line += c;
    }
  }
  
  if (line.length() > 0){
    Serial.print("copycat: "+ line);
    line = "";
  }
}