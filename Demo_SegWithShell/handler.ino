/*
Obsolete function, left behind just in case
*/
String inString = "";

int GetInt() {
  while (Serial.available() == 0);
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    delay(1);
    if (isDigit(inChar)) {
      inString += (char)inChar;
    }
    if (inChar == '\n') {
      int foo = inString.toInt();
      inString = "";
      foo == 0 ? foo = -1 : NULL;
      return foo;
    }
  }
}

char GetChar() {
  while (Serial.available() == 0);
  int inChar = Serial.read();
  inString = "";
  while (Serial.available() > 0){
    Serial.read(); //Flushing Buffer
    delay(1);
  }
  return inChar;
}


