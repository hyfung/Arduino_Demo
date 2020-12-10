#include <SevenSeg.h>
volatile int x = 0;
SevenSeg myPad;
ISR(TIMER1_COMPA_vect) {
  x++;
}

void setup() {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 156;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  pinMode(A1, INPUT_PULLUP);
  sei();
}

void loop() {
  if (digitalRead(A1) == 0 ) x = 0;
  myPad.writeNumber(x);
}

