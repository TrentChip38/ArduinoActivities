/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/
//Global variables to use
const int mDelay = 200;
//Setup runs once
void setup() {
  //Initialize output pin
  pinMode(LED_BUILTIN, OUTPUT);
}
//Loop runs over and over
void loop() {
  //Turn the LED on (HIGH voltage)
  digitalWrite(LED_BUILTIN, HIGH);
  delay(mDelay); //Wait for a 200 milis
  //Turn the LED off with voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
  delay(mDelay); //Wait for a 200 milis
}
