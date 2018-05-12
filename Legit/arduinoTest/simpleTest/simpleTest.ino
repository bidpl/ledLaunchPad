byte clockPin = 6;
byte dataPin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 4; i++){
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
  }

  shiftOut(dataPin, clockPin, MSBFIRST, 0b11111111);
  
  shiftOut(dataPin, clockPin, MSBFIRST, 255);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);

  
  shiftOut(dataPin, clockPin, MSBFIRST, 0b11111111);

  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 255);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);

  for(int i = 0; i < 4; i++){
    shiftOut(dataPin, clockPin, MSBFIRST, 0b11111111);
  }
  delay(200);
}
