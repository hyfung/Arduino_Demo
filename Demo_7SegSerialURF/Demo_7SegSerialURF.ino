#include <SR04.h>
#include <SevenSeg.h>
int pointer = 0;
SevenSeg Seg;
SR04 radar(6,9); //Echo Trig
String inPacket = "";
int State = 0;
unsigned long old_x = 0;
unsigned long x = 0;
unsigned long sum = 0;
unsigned long array[8] = {0};
void setup() {
  Serial.begin(9600);
  inPacket.reserve(64);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  x = 0;

  if (digitalRead(A1) == 0) {
    State = 0;
    while ( digitalRead(A1) == 0);
  }
  if (digitalRead(A2) == 0) {
    State = 1;
    while (digitalRead(A2) == 0);
  }
  if (digitalRead(A3) == 0) {
    State = 2;
    while (digitalRead(A3) == 0);
  }

  //Single-shot measurement
  if (State == 0) {
    x = radar.getDistance(50000);
    Seg.writeNumber(x);
  }

  //Average-of-8 measurement
  if (State == 1) {
    sum = 0;
    unsigned long foo = radar.getDistance(50000);
    array[pointer] = foo ? foo : array[pointer];
    for (int i = 0; i < 8; i++) {
      sum += array[i];
    }
    sum >>= 3;
    Seg.writeNumber(sum);
    analogWrite(5, 3*sum);
    pointer++;
    pointer &= ~(0b11111000);
  }

  //
  if (State == 2) {
    WaitForPacket();
    Seg.writeNumber(x);
  }

  if(x){
    Serial.println(x);
  }
}

