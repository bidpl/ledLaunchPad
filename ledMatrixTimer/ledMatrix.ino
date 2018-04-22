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

const int animationMultiplier = 100;

void setup() {
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
  
  laserIn(animationMultiplier);
  crossOut(animationMultiplier);
  crossIn(animationMultiplier);
  laserOut(animationMultiplier);
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
