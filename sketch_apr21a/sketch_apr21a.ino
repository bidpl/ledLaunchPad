#include <LedControl.h>
LedControl lc=LedControl(12,11,10,2); 
int x = 0; //row
int y = 0; //col
int cmax = 7; // counter max
int cmin = 0; //counter min
int big = 0;

void setup() {

lc.shutdown(0,false);
lc.setIntensity(0,8);
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

if (y != 7 && x==0) {
  y=y+1;
  }

if (y == 7 && x!=7) {
  x=x+1;
  }

if (y != 0 && x == 7) {
  y=y-1;
}

if (y == 0 && x !=1){
  x=x-1;
}

//8 is done

if (y != 6 && x==1) {
  y=y+1;
  }

if (y == 6 && x!=6) {
  x=x+1;
}

if (y != 1 && x == 6) {
  y=y-1;
}

if (y == 1 && x !=2){
  x=x-1;
}

lc.setLed(0, x, y, true);
delay(100);
lc.setLed(0, x, y, false);
delay(100);

}
