/*
  Blink an external LED
  You should connect your LED in the correct direction to the specified pin with a 1k+ ohm resistor.
*/

//Global variables to use
const int mDelay = 500;//You can change this value
//mDelay is a variable that will set how long the LED blinks for
const int ledPin = 2;
//From now on "LEDPin" will be an alias for pin 10 on the Arduino Nano

//Setup function runs once when device is powered on
void setup() {
  //Initialize output pin
  pinMode(ledPin, OUTPUT);
}

//Loop function runs over and over after setup
void loop() {
  //Turn the LED on (HIGH voltage)
  digitalWrite(ledPin, HIGH);
  //Wait for set delay time
  delay(mDelay);
  //Turn the LED off with voltage LOW
  digitalWrite(ledPin, LOW);
  //Wait for set delay time
  delay(mDelay);
}
