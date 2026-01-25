/*
  Read 4 push buttons and play notes

  Connect 3 buttons to ground and to input pins (4-7)
  Connect a piezo buzzer to GND and to output pin (3)
*/
#include "pitches.h"

// Notes to play from the "pitches" library
int notes[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4 };
const int buttonPins[] = { 4, 5, 6, 7 };
const int buttonCount = 4;//You could add more buttons and tones
const int speakerPin = 3;

void setup() {
  //Using a for loop to set all the pins as input
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  bool buttonPressed = false;
  for (int i = 0; i < buttonCount; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      tone(speakerPin, notes[i]);
      buttonPressed = true;
      break; // Only play one tone at a time
    }
  }
  if (!buttonPressed) {
    noTone(speakerPin);
  }
}
