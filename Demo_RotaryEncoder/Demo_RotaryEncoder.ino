/*
Demo code for Rotary Encoder
*/
int val;
int encoder0PinA = A0;
int encoder0PinB = A1;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

void setup() {
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  Serial.begin (9600);
}

void loop() {
  n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos++;
    } else {
      encoder0Pos--;
    }
    Serial.print (encoder0Pos);
    Serial.print ("\n");
  }
  encoder0PinALast = n;
}
