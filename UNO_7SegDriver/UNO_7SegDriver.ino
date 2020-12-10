#include <Wire.h>

volatile short MyNumber = 0;
const unsigned char CharMapping = {0};

void updateNumber(int numBytes) {
  MyNumber = 0;
  while (Wire.available() > 0) {
    MyNumber = MyNumber << 8 + Wire.read();
  }
}

void setup() {
  cli();
  Wire.begin(0x37);
  Wire.onReceive(updateNumber);
  //----ISR config
  //----16Mhz Clk, 8-bit timer
  TCNT2 = 0;
  TCCR2A = 0; //(1 << WGM21); //WGM mode, reset on OCR2A
  TCCR2B = (1 + 2 + 4); //Prescaler 1024, increment at 15625hz
  OCR2A = 0;
  OCR2B = 0;
  TIMSK2 = (1 << TOV2); //Overflow interrupt
  sei();
}

void loop() {
}



ISR(TIMER2_OVF_vect) {

}

