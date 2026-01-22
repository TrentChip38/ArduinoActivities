/*
  Read a push button and toggle an LED

  You should connect your LED in the correct direction to the specified pin with a 1k+ ohm resistor.
  Connect your button so one side is GND and the disconnected pin side is on the input pin (8)

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

//Loop function runs over and over after setup
void loop() {
  //Track on/off, start off
  int LEDState = 0;

  delay(300);
  //Check the button every tenth second
  int buttonState = digitalRead(btnPin);
  //This "if" statement executes if buttonState equals 0
  if (buttonState == 0){
    //This assignment makes LEDState switch 0 to 1 and 1 to 0
    LEDState != LEDState;
  }

  //Set LED to be high or low
  if (LEDState == HIGH){
    digitalWrite(LEDPin, HIGH);
  }else{
    digitalWrite(LEDPin, LOW);
  }
}
