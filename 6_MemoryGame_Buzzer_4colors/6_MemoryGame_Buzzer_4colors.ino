/*This sketch is a simple version of the famous Simon Says game. You can  use it and improved it adding
levels and everything you want to increase the  diffuculty!

There are 4 LEDs conencted to pins 9 - 12 that pulse in a different order you have to remember
There are 4 buttons connected to pins 5 - 8 that you use to replicate the right sequence
One of the buttons is the start button

When you get the sequence right a happy beep will play
When a wrong sequence is inserted a sad tone will play

The original code and idea is from Arduino_Scuola on the Arduino Project Hub
https://projecthub.arduino.cc/Arduino_Scuola/a-simple-simon-says-game-6f7fef
It has been modified to have variables for pins and use for loops
And to use buzzers for each pin and winning/losing sounds
*/
//#include "pitches.h"
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_G4 392
#define NOTE_C5 523
#define NOTE_C3 131

// Notes to play from the "pitches" library
int notes[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4 };
//Pins used for buttons
const int buttonPins[] = { 5, 6, 7, 8 };
const int buttonCount = 4;//You could add more buttons and tones
const int actualSpeakerPin = 3;//Track speaker pin, but be able to turn it off
int speakerPin = actualSpeakerPin;
const int unusedPin = 2;
//Pins used for LEDs
const int ledPins[] = { 9, 10, 11, 12};//{12, 11, 10, 9}
//The wiring might have these flipped
//If so, reverse their order in this array

const int startSpeed = 1000;//If you think its too slow, start at 300-500
const int minSpeed = 50;//If you don't stop it here, it is too fast
const int playWinTone = 1;//If the win beep every time is annoying, change this to 0 and it wont play

const int MAX_LEVEL  = 100;
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level  = 1;

int velocity = startSpeed;

void setup() {
  //Using a for loop to set all the pins as input
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  //LED output pins
  for (int i = 0; i < buttonCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    //Start them off
    digitalWrite(ledPins[i], LOW);
  }
}

void loop()
{
  if  (level == 1)
  generate_sequence();//generate a sequence;

  if (digitalRead(buttonPins[3])  == LOW) //If first button is pressed or you're winning
  {
    //Start game normally with buzzer
    speakerPin = 3;
  show_sequence();    //show the sequence
  get_sequence();     //wait for your sequence
  }else if (digitalRead(buttonPins[2])  == LOW) //If 2nd butotn pressed
  {
    //Start game silently
    speakerPin = 2; //Disable speaker
  show_sequence();    //show the sequence
  get_sequence();     //wait for your sequence
  }else if (level != 1) //Or if winning
  {
  show_sequence();    //show the sequence
  get_sequence();     //wait for your sequence
  }
}

void show_sequence(){
  //Start off
  allLow();
  delay(100);
  //Show the sequence
  for (int i = 0; i < level; i++){
    digitalWrite(ledPins[sequence[i]], HIGH); // Use index, not pin number
    tone(speakerPin, notes[sequence[i]], 160);
    delay(velocity);
    digitalWrite(ledPins[sequence[i]], LOW);
    noTone(speakerPin);
    delay(200);
  }
  delay(100);
}

void get_sequence() {
  for (int i = 0; i < level; i++) {
    bool pressed = false;
    while (!pressed) {
      for (int j = 0; j < buttonCount; j++) {
        if (digitalRead(buttonPins[j]) == LOW) {
          delay(20); // debounce: wait for signal to settle
          if (digitalRead(buttonPins[j]) == LOW) { // confirm still pressed
            digitalWrite(ledPins[j], HIGH);
            tone(speakerPin, notes[j]);
            your_sequence[i] = j;
            delay(200); // LED/sound feedback
            digitalWrite(ledPins[j], LOW);
            noTone(speakerPin);
            // Wait for button release to avoid double press
            while (digitalRead(buttonPins[j]) == LOW) { delay(10); }
            delay(50); // debounce: wait after release
            pressed = true;
            if (your_sequence[i] != sequence[i]) {
              wrong_sequence();
              return;
            }
            break;
          }
        }
      }
    }
  }
  right_sequence();
}

void generate_sequence(){
  //Generate a random sequence
  randomSeed(millis());
  for (int i = 0; i < MAX_LEVEL; i++)
  {
    sequence[i]  = random(0, buttonCount); // Store index (0-3)
  }
}

void wrong_sequence()
{
  // Play a sad low note
  tone(speakerPin, NOTE_C3, 500); // C3 is a low note
  for (int i = 0; i < 3;  i++)
  {
    //Blink 3 times
    allHigh();
    delay(250);
    allLow();
    delay(250);
  }
  noTone(speakerPin);
  //Rest level
  level  = 1;
  velocity = startSpeed;
}

void right_sequence(){
  // // Play a happy melody: C-E-G-C
  // int melody[] = { NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5 };
  // int noteDurations[] = { 150, 150, 150, 300 };
  // for (int i = 0; i < 4; i++) {
  //   tone(speakerPin, melody[i], noteDurations[i]);
  //   delay(noteDurations[i]);
  //   noTone(speakerPin);
  //   delay(30);
  // }
  if (playWinTone)
    tone(speakerPin, NOTE_C5, 500); // C5 is a high note
  //Blink all
  allLow();
  delay(250);
  allHigh();
  delay(400);
  noTone(speakerPin);
  allLow();
  delay(40);

  if  (level < MAX_LEVEL);
  level++;

  velocity -= 50; //increase difficulty
  //But set minimum
  if (velocity < minSpeed){
    velocity = minSpeed;
  }
}
void allHigh(){
  for (int i = 0; i < buttonCount; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}
void allLow(){
  for (int i = 0; i < buttonCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}
