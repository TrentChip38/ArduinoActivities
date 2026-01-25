/*
  Read a push button and toggle an LED

  You should connect your LED in the correct direction to the specified pin with a 1k+ ohm resistor.
  Connect your button so one side is GND and the disconnected pin side is on the input pin (5)

  This sketch does not properly debounce the button, 
  for that see File->Examples->Digital->Debounce
*/
//Definitions are similar to variables, here these are aliases for the pin number
#define LEDPin 6
#define btnPin 5

//Setup function runs once when device is powered on
void setup() {
  //Initialize output pin
  pinMode(LEDPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
}

//Track on/off, start off
int LEDState = HIGH;
//Loop function runs over and over after setup
void loop() {

  delay(200);
  //Check the button every fith of a second
  int buttonState = digitalRead(btnPin);
  //This "if" statement executes if buttonState equals 0
  if (buttonState == LOW){
    //This assignment switches LEDState from HIGH to LOW and LOW to HIGH
    LEDState = ~LEDState;
    //Set LED state
    digitalWrite(LEDPin, LEDState);
  }
}
