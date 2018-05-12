byte clockPin = 6;
byte dataPin = 5;

const byte X_LEN = 1;
const byte Y_LEN = 2;

const byte BRIGHTNESS_INDEX = 0;
const byte RED_INDEX = 1;
const byte GREEN_INDEX = 2;
const byte BLUE_INDEX = 3;

byte matrix[X_LEN][Y_LEN][4];

byte defualtBrightness = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //Sets up matrix array
  for(int x = 0; x < X_LEN; x++){
    for(int y = 0; Y_LEN; y++){
      for(int i = 0; i < 4; i++){
        matrix[x][y][i] = 0;
      }

      matrix[x][y][3] = defualtBrightness;
    }
  }

  showMatrix();
}

void loop() {
  setPixel(0, 0, 255, 0, 0);
  setPixel(0, 1, 0, 255, 0, 10);
  showMatrix();
  delay(2500);
//
//  setPixel(0, 0, 0, 255, 0);
//  setPixel(0, 1, 255, 0, 0, 10);
//  showMatrix();
//  delay(2500);
}

//Sets Pixel Color in array w/o brightness
void setPixel(int ledX, int ledY, int red, int green, int blue){
  matrix[ledX][ledY][RED_INDEX] = red;
  matrix[ledX][ledY][GREEN_INDEX] = green;
  matrix[ledX][ledY][BLUE_INDEX] = blue;
  matrix[ledX][ledY][BRIGHTNESS_INDEX] = defualtBrightness;  
}

//Sets Pixel Color in array w/ brightness
void setPixel(int ledX, int ledY, int red, int green, int blue, int brightness){
  matrix[ledX][ledY][RED_INDEX] = red;
  matrix[ledX][ledY][GREEN_INDEX] = green;
  matrix[ledX][ledY][BLUE_INDEX] = blue;
  matrix[ledX][ledY][BRIGHTNESS_INDEX] = brightness;  
}

void showMatrix(){
  //Opening Frame
  for(int i = 0; i < 4; i++){
    shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000);
  }

  //Goes through each led
  for(int x = 0; x < X_LEN; x++){
    for(int y = 0; y < Y_LEN; y++){
      //Sends LED start bits and brightness bits
      shiftOut(dataPin, clockPin, MSBFIRST, (0b11100000 | matrix[x][y][BRIGHTNESS_INDEX]));

      //Sends out Red, BLUE, and GREEN bits in that order (LEDs have RBG bitstream, not RGB)
      shiftOut(dataPin, clockPin, MSBFIRST, matrix[x][y][RED_INDEX]);
      shiftOut(dataPin, clockPin, MSBFIRST, matrix[x][y][BLUE_INDEX]);
      shiftOut(dataPin, clockPin, MSBFIRST, matrix[x][y][GREEN_INDEX]);
    }
  }

  //End frame
  for(int i = 0; i < 4; i++){
    shiftOut(dataPin, clockPin, MSBFIRST, 0b11111111);
  }
}

/*void setColor(byte red, byte green, byte blue, byte brightness){
  //Start Frame
  for(int i = 0; i < 4; i++){
    shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000);
  }

  //LED Frame
  //Brightness Framw
  shiftOut(dataPin, clockPin, MSBFIRST, (0b11100000 | brightness));

  //Red Frame
  
  shiftOut(dataPin, clockPin, MSBFIRST, red);
  
  //Blue Frame
  shiftOut(dataPin, clockPin, MSBFIRST, blue);
  
  //Green Frame
  shiftOut(dataPin, clockPin, MSBFIRST, green);

  //End Frame
  for(int i = 0; i < 4; i++){
    shiftOut(dataPin, clockPin, MSBFIRST, 255);
  }
}*/

