/*
  Read a push button and play a tone

  Connect your button so one side is GND and the disconnected pin side is on the input pin (6)
  Connect a piezo buzzer to GND and to pin (3)
*/
//Definitions are similar to variables, here these are aliases for the pin number
#define btnPin 5
#define buzzerPin 3

//Setup function runs once when device is powered on
void setup() {
  //Initialize pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
}

//Loop function runs over and over after setup
void loop() {
  delay(10);
  if (digitalRead(btnPin) == LOW){
    //While button pressed, make tone at 440Hz
    tone(buzzerPin, 440, 20);
  }
}
