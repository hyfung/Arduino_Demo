#include <SevenSeg.h>
//SevenSeg mySeven(8,7,4);
SevenSeg mySeven;
/*
  Demo code for Rotary Encoder
  With
*/
int val;
int encoder0PinA = 6;
int encoder0PinB = 9;
int encoder0Pos = 30;
int encoder0PinALast = LOW;
int n = LOW;

void setup() {
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  pinMode(5, OUTPUT);
   encoder0Pos = 0;
}

void loop() {
  n = digitalRead(encoder0PinA);
  if ( (encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos+= 2;
    } else {
      encoder0Pos-=2;
    }
  }
  encoder0PinALast = n;
//--------
//encoder0Pos &= ~(1 << 31);
encoder0Pos *= ( (encoder0Pos < 0 ) ?  -1 : 1 );
encoder0Pos -= (encoder0Pos > 255) ? 1 : 0;
analogWrite(5, encoder0Pos);
mySeven.writeNumber(encoder0Pos);
}

void nop(){
  return;
}

