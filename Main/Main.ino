#include <Adafruit_NeoPixel.h>

#include <Keypad.h>
#include <LedControl.h>

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc = LedControl(12,11,10,1);

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char buttons[ROWS][COLS] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','0','A','B'},
  {'C','D','E','F'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 7, 6, 8, 9 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 3, 2 };

// Create the Keypad
Keypad keypd = Keypad( makeKeymap(buttons), rowPins, colPins, ROWS, COLS );

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            A0

// How many NeoPixels are attached to the Arduino?
#define NUM_LED      30

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LED, PIN, NEO_GRB + NEO_KHZ800);

// Set animation speed
const int animationMultiplier = 100;

// Set up a timer
int timer = 0;

//
#define QUEUE_LEN 20

// Set up a list for each key pressed
char keys[QUEUE_LEN];

// Set up a list for animation step for each key
int steps[QUEUE_LEN];

int spiralArray[64][2] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}, {7, 7}, {7, 6}, {7, 5}, {7, 4}, {7, 3}, {7, 2}, {7, 1}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {6, 5}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {5, 4}, {5, 3}, {5, 2}, {4, 2}, {3, 2}, {3, 3}, {3, 4}, {4, 4}, {4, 3}};

void setup() {
  // Activate console logging
  Serial.begin(9600);

  for (int i = 0; i < QUEUE_LEN; i++){
    keys[i] = '0';
  }

  for(int i = 0; i < QUEUE_LEN; i++){
    steps[i] = 0;
  }
  
  /*
  The MAX72XX is in power-saving mode on startup,
  we have to do a wakeup call
  */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,1);
  /* and clear the display */
  lc.clearDisplay(0);

  strip.setBrightness(50);
  strip.begin();
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypd.getKey();
  
  if (key) {
    //Add to display engine
    addKey(key);
  }

  if (timer % 100 == 0) {
    lc.clearDisplay(0);
    // Iterates throughout the list and goes frame by frame
    for (int i = 0; i < QUEUE_LEN; i++) {
      if (keys[i] == '1' ) {
        laserIn(steps[i], i);
        
      }else if (keys[i] == '2') {
        laserOut(steps[i], i);
        
      }else if (keys[i] == '3') {
        crossIn(steps[i], i);
        
      }else if (keys[i] == '4') {
        crossOut(steps[i], i);
        
      }else if (keys[i] == '5') {
        spiralIn(steps[i], i);
        
      }else if (keys[i] == '9'){
        conoways(steps[i], i);
      }
  
      // To add more keys, add an else if statement, then feed in steps[i] and i
    }
  }

  if (timer % 50 == 0) {
    clearStrip();
    strip.show();
    for(int i = 0; i < QUEUE_LEN; i++){
      if (keys[i] == '6') {
        stripComet(steps[i], i);
        
      }else if (keys[i] == '7'){
        stripColorChase(steps[i], i);
        
      }else if (keys[i] == '8'){
        stripWhiteFill(steps[i], i);
      }
    }
  }

  delay(1);
  timer++;
}

void addKey(char key) {
  // Iterates through all instances in the active animations list
  for (int i = 0; i < QUEUE_LEN; i++) {
    
    if (keys[i] == '0') {
      
      keys[i] = key;
      // If the instance in the keys list is not being used, assign a key to that list

      break;
      
    }
    
  }
}

void crossIn(int aniStep, int keysId){
  lc.setLed(0, aniStep, aniStep, true);
  lc.setLed(0, 7-aniStep, aniStep, true);
  lc.setLed(0, aniStep, 7-aniStep, true);
  lc.setLed(0, 7-aniStep,7-aniStep, true);

    // Adds to the frame count
  steps[keysId] += 1;

  // If the the frame count reaches the end of the animation, reset everything
  if (aniStep == 3) {
    keys[keysId] = '0';
    steps[keysId] = 0;
  }
  
}

void crossOut(int aniStep, int keysId){
  lc.setLed(0, 4+aniStep, 4+aniStep, true);
  lc.setLed(0, 3-aniStep, 3-aniStep, true);
  lc.setLed(0, 4+aniStep, 3-aniStep, true);
  lc.setLed(0, 3-aniStep, 4+aniStep, true);

    // Adds to the frame count
  steps[keysId] += 1;

  // If the the frame count reaches the end of the animation, reset everything
  if (aniStep == 4) {
    keys[keysId] = '0';
    steps[keysId] = 0;
  }
  
}

void laserIn(int aniStep, int keysId){
  //Vertical Up
  lc.setLed(0, 3, aniStep, true);
  lc.setLed(0, 4, aniStep, true);

  //Vertical Down
  lc.setLed(0, 3, 7-aniStep, true);
  lc.setLed(0, 4, 7-aniStep, true);

  //Left in
  lc.setLed(0, aniStep, 3, true);
  lc.setLed(0, aniStep, 4, true);

  //Vertical Up
  lc.setLed(0, 7-aniStep, 3, true);
  lc.setLed(0, 7-aniStep, 4, true);

  // Adds to the frame count
  steps[keysId] += 1;

  // If the the frame count reaches the end of the animation, reset everything
  if (aniStep == 3) {
    keys[keysId] = '0';
    steps[keysId] = 0;
  }
  
}


void laserOut(int aniStep, int keysId){
  /*
   * Takes in a step and an ID
   * The step is for positioning and frame count
   * The ID is for knowing what is going on
   */
  
  //Vertical Up
  lc.setLed(0, 3-aniStep, 3, true);
  lc.setLed(0, 3-aniStep, 4, true);

  //Vertical Down
  lc.setLed(0, 4+aniStep, 3, true);
  lc.setLed(0, 4+aniStep, 4, true);

  //Left in
  lc.setLed(0, 3, 4+aniStep, true);
  lc.setLed(0, 4, 4+aniStep, true);

  //Right in
  lc.setLed(0, 3, 3-aniStep, true);
  lc.setLed(0, 4, 3-aniStep, true);

  // Adds to the frame count
  steps[keysId] += 1;

  // If the the frame count reaches the end of the animation, reset everything
  if (aniStep == 4) { // The number here should correlate to the end of the frame loop
    keys[keysId] = '0';
    steps[keysId] = 0;
    // Resets list
  }
  
}

void spiralIn(int aniStep, int keysId) {
  Serial.print(spiralArray[aniStep][0]);
  Serial.print(", ");
  Serial.println(spiralArray[aniStep][1]);
  lc.setLed(0, spiralArray[aniStep][0], spiralArray[aniStep][1], true);
    
  // Adds to the frame count
  steps[keysId] += 1;

  // If the the frame count reaches the end of the animation, reset everything
  if (aniStep == 63) { // The number here should correlate to the end of the frame loop
    keys[keysId] = '0';
    steps[keysId] = 0;
    // Resets list
  }
}

void stripComet(int aniStep, int keysId){
  for(int i = 0; i < 3; i++){
    strip.setPixelColor(aniStep-1, 255, 255, 255);
  }

  strip.show();
  
  // Adds to the frame count
  steps[keysId] += 1;

  // If the the frame count reaches the end of the animation, reset everything
  if (aniStep == NUM_LED-1) { // The number here should correlate to the end of the frame loop
    keys[keysId] = '0';
    steps[keysId] = 0;
    // Resets list
  }
}

void stripColorChase(int aniStep, int keysId){
  //Paints the green
  for(int i = 0; i <= aniStep && i < NUM_LED; i++){
    strip.setPixelColor(i, 0, 0, 255);
  }

  //Paints the blue
  for(int i = 0; i <= aniStep-NUM_LED && i < NUM_LED; i++){
    strip.setPixelColor(i, 0, 255, 0);
  }

  //Paints red
  for(int i = 0; i <= aniStep-2*NUM_LED && i < NUM_LED; i++){
    strip.setPixelColor(i, 255, 0, 0);
  }

  //Clears tail
  for(int i = 0; i <= aniStep-3*NUM_LED && i < NUM_LED; i++){
    strip.setPixelColor(i, 0, 0, 0);
  }

  //Shows colors
  strip.show();
  
  // Adds to the frame count
  steps[keysId] += 1;

  // If the the frame count reaches the end of the animation, reset everything
  if (aniStep == 4*NUM_LED-1) { // The number here should correlate to the end of the frame loop
    keys[keysId] = '0';
    steps[keysId] = 0;
    // Resets list
  }
}

void stripWhiteFill(int aniStep, int keysId){
  for(int i = 0; i <= aniStep; i++){
    strip.setPixelColor(i, 255, 250, 245);
  }

  strip.show();
  
  // Adds to the frame count
  steps[keysId] += 1;

  // If the the frame count reaches the end of the animation, reset everything
  if (aniStep == NUM_LED-1) { // The number here should correlate to the end of the frame loop
    keys[keysId] = '0';
    steps[keysId] = 0;
    // Resets list
  }
}

void conoways (int aniStep, int keysId){
  int rowMatrix[8][8] = {{0,0,16,8,56,0,0,0},{0,0,0,40,24,16,0,0},{0,0,0,8,40,24,0,0},{0,0,0,16,12,24,0,0},{0,0,0,8,4,28,0,0},{0,0,0,0,20,12,8,0},{0,0,0,0,4,20,12,0},{0,0,0,0,4,2,14,0}};
  
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, rowMatrix[aniStep][i]);
  }
  
  steps[keysId] += 1;
  
  if (aniStep == 7) {
    keys[keysId] = '0';
    steps[keysId] = 0;
  }
}

void clearStrip(){
  for(int i = 0; i < NUM_LED; i++){
    strip.setPixelColor(i, 0, 0, 0);
  }
}

