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
LedControl lc=LedControl(12,11,10,1);


const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3', '4'},
  {'5','6','7', '8'},
  {'9','0','A', 'B'},
  {'C','D','E', 'F'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 7, 6, 8, 9 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 3, 2 }; 

// Create the Keypad
Keypad keypd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


const int animationMultiplier = 100;

void setup() {
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
  }
}

void crossIn(int aniSpeed){
  for(int i = 0; i < 4; i++){
    lc.clearDisplay(0);
    lc.setLed(0, i, i, true);
    lc.setLed(0, 7-i, i, true);
    lc.setLed(0, i, 7-i, true);
    lc.setLed(0, 7-i,7-i, true);
    
    delay(aniSpeed);
  }
}

void crossOut(int aniSpeed){
  for(int i = 3; i >= 0; i--){
    lc.clearDisplay(0);
    lc.setLed(0, i, i, true);
    lc.setLed(0, 7-i, i, true);
    lc.setLed(0, i, 7-i, true);
    lc.setLed(0, 7-i,7-i, true);
    
    delay(aniSpeed);
  }
}

void laserIn(int aniSpeed){
  for(int i = 0; i < 4; i++){
    lc.clearDisplay(0);
    //Vertical Up
    lc.setLed(0, 3, i, true);
    lc.setLed(0, 4, i, true);

    //Vertical Down
    lc.setLed(0, 3, 7-i, true);
    lc.setLed(0, 4, 7-i, true);

    //Left in
    lc.setLed(0, i, 3, true);
    lc.setLed(0, i, 4, true);

    //Vertical Up
    lc.setLed(0, 7-i, 3, true);
    lc.setLed(0, 7-i, 4, true);

    delay(aniSpeed);
  }
}


void laserOut(int aniSpeed){
  for(int i = 4; i >= 0; i--){
    lc.clearDisplay(0);
    //Vertical Up
    lc.setLed(0, 3, i, true);
    lc.setLed(0, 4, i, true);

    //Vertical Down
    lc.setLed(0, 3, 7-i, true);
    lc.setLed(0, 4, 7-i, true);

    //Left in
    lc.setLed(0, i, 3, true);
    lc.setLed(0, i, 4, true);

    //Vertical Up
    lc.setLed(0, 7-i, 3, true);
    lc.setLed(0, 7-i, 4, true);

    delay(aniSpeed);
  }
}
