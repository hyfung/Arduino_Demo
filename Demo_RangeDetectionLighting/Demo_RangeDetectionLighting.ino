#include <SR04.h>
#include <SevenSeg.h>
int pointer = 0;
SevenSeg Seg;
SR04 radar(6, 9); //Echo Trig
unsigned long old_x = 0;
unsigned long x = 0;
unsigned long sum = 0;
float damped_sum = 0;
unsigned long array[8] = {0};
void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
}

void loop() {
  sum = 0;
  unsigned long foo = radar.getDistance();
  array[pointer] = foo ? foo : array[pointer];
  for (int i = 0; i < 8; i++) {
    sum += array[i];
  }
  sum >>= 3;
  damped_sum = damped_sum * 0.998 + sum * 0.002; //Beta-method
  Seg.writeNumber((int)damped_sum);
  if(damped_sum > 255) damped_sum = 254;
  analogWrite(5, 5 * ( (int)damped_sum - 2) );
  pointer++;
  pointer &= ~(0b11111000);
}

