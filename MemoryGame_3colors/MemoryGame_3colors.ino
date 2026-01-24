/*This sketch is a simple version of the famous Simon Says game. You can  use it and improved it adding
levels and everything you want to increase the  diffuculty!

There are 3 LEDs conencted to pins 8 - 10 that pulse in a different order you have to remember
There are 3 buttons connected to pins 4 - 6 that you use to replicate the right sequence
One of the buttons is the start button

The original code and idea is from Arduino_Scuola on the Arduino Project Hub
https://projecthub.arduino.cc/Arduino_Scuola/a-simple-simon-says-game-6f7fef
It has been modified to have variables for pins and use for loops
*/

//Pins used for buttons
const int buttonPins[] = { 4, 5, 6};
const int buttonCount = 3;//You could add more buttons and tones

//Pins used for LEDs
const int ledPins[] = {8, 9, 10};//{ 10, 9, 8}
//The wiring might have these flipped
//If so, reverse their order in this array

const int startSpeed = 1000;//If you think its too slow, start at 300-500
const int minSpeed = 50;//If you don't stop it here, it is too fast

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

  if (digitalRead(buttonPins[buttonCount - 1])  == LOW || level != 1) //If first button is pressed or you're winning
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
    delay(velocity);
    digitalWrite(ledPins[sequence[i]], LOW);
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
            your_sequence[i] = j;
            delay(200); // LED/sound feedback
            digitalWrite(ledPins[j], LOW);
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
  for (int i = 0; i < 3;  i++)
  {
    //Blink 3 times
    allHigh();
    delay(250);
    allLow();
    delay(250);
  }
  //Rest level
  level  = 1;
  velocity = startSpeed;
}

void right_sequence(){
  //Blink all
  allLow();
  delay(250);
  allHigh();
  delay(400);
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
