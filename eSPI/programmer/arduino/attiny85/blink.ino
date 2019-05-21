const int led = 3;
const int sleep = 1000;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever
void loop() {
  digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(sleep);            // wait for a second
  digitalWrite(led, LOW);  // turn the LED off by making the voltage LOW
  delay(sleep);            // wait for a second
}