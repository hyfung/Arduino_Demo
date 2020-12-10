#include <Numpad.h>
Numpad NumpadObj;
int ToneChart[] = {220};
unsigned char Speaker = 11;

void setup() {
  NumpadObj.col(); //0 to 2
  NumpadObj.row(); //0 to 3
  pinMode(Speaker, OUTPUT);
  digitalWrite(Speaker, LOW);
}

void loop() {
  int x = NumpadObj.getKey();
  if (x) {
    x--;
    if (x > 7) break;
    else {
      tone(Speaker, ToneChart[x]);
    }
  }
  //Let say we are doing 1 to 8 only
  //Handle debounce case
}

