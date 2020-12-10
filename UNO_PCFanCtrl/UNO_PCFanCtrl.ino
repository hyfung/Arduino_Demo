const unsigned char PWM_CH[] = {3, 5, 6, 9, 10, 11};
unsigned char PWM_V[6] = {0};
String inString = "";

void setup() {
  Serial.begin(115200);
  inString.reserve(64);
  for (int i = 0; i < 6; i++) {
    pinMode(PWM_CH[i], OUTPUT);
    digitalWrite(PWM_CH[i], LOW);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char buf = Serial.read();
    if (buf != '\n') {
      if (buf != '\r') inString += buf;
    }
    else {
      if (inString.length() == 2) {
        unsigned char myIndex = inString[0] - 48;
        unsigned char Level = inString[1] + 1;
        Level -= 48;
        PWM_V[myIndex] = Level;
      }
    }
  }
  for (int i = 0; i < 6; i++) {
    analogWrite(PWM_CH[i], PWM_V[i] * 25);
  }
}

