#include "LedControl.h" 
LedControl lc=LedControl(12,11,10,2); 
int x = 0; //row
int y = 0; //col
int c = 8; // counter
void setup() {

lc.shutdown(0,false);
lc.setIntensity(0,16);
}

void loop() {
  /*
lc.setLed(0,a,b,true);
delay(25);
lc.setLed(0,a,b,false);
a=a+1;
if (a == 8){
  a=0;
  b=b+1;
}
if (b == 8){
  b=0;
  a=0;
}
*/

if (y != c && x==0) {
  y=y+1;
}

if (y == c && x!=c) {
  x=x+1;
}

if (y != 0 && x == c) {
  y=y-1;
}

if (y == 0 && x !=1){
  x=x-1;
}

lc.setLed(0, x, y, true);
delay(75);
lc.setLed(0 ,x, y,false);

}
