#include <SevenSeg.h>
SevenSeg mySeg;
#include <SR04.h>
SR04 radar(6,9);

float Normalized = 90;
int Threshold = 20;
void setup() {
  pinMode(5, OUTPUT);
}

void loop() {
  int Raw = radar.getDistance();
  Normalized = Normalized * 0.999 + (1 - 0.999) * Raw;
  mySeg.writeNumber( (int) Normalized );
  if (Normalized > Threshold) {
    digitalWrite(5, HIGH);
  }
  else {
    digitalWrite(5, LOW);
  }

}

