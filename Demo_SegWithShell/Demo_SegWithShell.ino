#include <SevenSeg.h>
volatile int x = 0;
SevenSeg mySeg;
String inPacket = "";

void setup() {
  Serial.begin(9600);
  inPacket.reserve(64);
  Serial.println("Serial Shell for ATMega328P series");
  print_help();
  pinMode(5, OUTPUT);
  pinMode(A4, INPUT_PULLUP);
  digitalWrite(3, LOW);
  for (int i = 10; i < 14; i++) {
      digitalWrite(i, HIGH);
    }
}

void loop() {
  if (digitalRead(A4) == 1) {
    for (int i = 10; i < 14; i++) {
      digitalWrite(i, HIGH);
    }
    WaitForPacket();
    mySeg.writeNumber(x);
  }
  else {
    for (int i = 10; i < 14; i++) {
      digitalWrite(i, LOW);
    }
    x = analogRead(A5) >> 2;
    mySeg.writeNumber(x);
    analogWrite(5, x);
  }
}

void nop() {
  return;
}


