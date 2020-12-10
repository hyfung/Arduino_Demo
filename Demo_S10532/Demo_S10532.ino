#include <S10532.h>
S10532 keypad;
void setup(){
  keypad.col(A11,A10,A9,A8);
  keypad.row(A15,A14,A13,A12);
  Serial.begin(9600);
}

void loop(){
  int x = keypad.getKey();
  if(x) Serial.println(x);
}


