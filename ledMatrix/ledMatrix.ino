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

// Set animation speed
const int animationMultiplier = 100;

// Set up a timer
int timer = 0;

// Set up a list for each key pressed
char keys[10] = {'0','0','0','0','0','0','0','0','0','0'};

// Set up a list for animation step for each key
int steps[10] = {0,0,0,0,0,0,0,0,0,0};

void setup() {

  // Activate console logging
  Serial.begin(9600);
  
  /*
  The MAX72XX is in power-saving mode on startup,
  we have to do a wakeup call
  */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,1);
  /* and clear the display */
  lc.clearDisplay(0);

}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypd.getKey();
  
  if (key == '3') {
    addKey(key);
  }

  for (int i = 0; i < 10; i++) {
    if (keys[i] == '1') {
      laserIn(steps[i], keys[i]);
    }
    
    else if (keys[i] == '2') {
      laserOut(steps[i], keys[i]);
    }
    
    else if (keys[i] == '3') {
      crossIn(steps[i], keys[i]);
    }
    
    else if (keys[i] == '4') {
      crossOut(steps[i], keys[i]);
    }
  }

  delay(100);

  lc.clearDisplay(0);

  timer++;
  /*
  if(key)  // Check for a valid key.
  {
    Serial.println(key);

    switch (key){
      case '1':
        laserIn(animationMultiplier);
        break;
        
      case '2':
        laserOut(animationMultiplier);
        break;

      case '3':
        crossIn(animationMultiplier);
        break;

      case '4':
        crossOut(animationMultiplier);
        break;

      default:
        break;
    }

    lc.clearDisplay(0);
  }*/
}

void addKey(char key) {
  // Iterates through all instances in the active animations list
  for (int i = 0; i < 10; i++) {
    
    if (keys[i] != '0') {
      
      keys[i] = key;
      // If the instance in the keys list is not being used, assign a key to that list
      
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
  if (aniStep == 8) {
    keys[keysId] = '0';
    steps[keysId] = 0;
  }
  
}

void crossOut(int aniStep, int keysId){
  lc.setLed(0, aniStep, aniStep, true);
  lc.setLed(0, 7-aniStep, aniStep, true);
  lc.setLed(0, aniStep, 7-aniStep, true);
  lc.setLed(0, 7-aniStep,7-aniStep, true);

    // Adds to the frame count
  steps[keysId] += 1;

  // If the the frame count reaches the end of the animation, reset everything
  if (aniStep == 8) {
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
  if (aniStep == 8) {
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
  lc.setLed(0, 3, aniStep, true);
  lc.setLed(0, 4, aniStep, true);

  //Vertical Down
  lc.setLed(0, 3, 7-aniStep, true);
  lc.setLed(0, 4, 7-aniStep, true);

  //Left in
  lc.setLed(0, aniStep, aniStep, true);
  lc.setLed(0, aniStep, aniStep, true);

  //Vertical Up
  lc.setLed(0, 7-aniStep, aniStep, true);
  lc.setLed(0, 7-aniStep, aniStep, true);

  // Adds to the frame count
  steps[keysId] += 1;

  // If the the frame count reaches the end of the animation, reset everything
  if (aniStep == 8) {
    keys[keysId] = '0';
    steps[keysId] = 0;
  }
  
}
