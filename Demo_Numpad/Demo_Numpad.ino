#include <Numpad.h>
Numpad myPad;

void setup(){
  myPad.col(13,12,9);
  myPad.row(8,10,11,7);
  Serial.begin(9600);
  pinMode(13, LOW);
  digitalWrite(13, LOW);
}

void loop(){
  if(myPad.getKey() != 255){
    Serial.println(myPad.getKey());
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
  }
}

