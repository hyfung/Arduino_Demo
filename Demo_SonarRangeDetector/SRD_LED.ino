/*
  This file covers the function related to LEDs
*/
unsigned char intensity[7] = {0};
extern int distance; //:full deflection - 30cm
unsigned char led[7] = {2, 3, 4, 5, 6, 7, 8};
int unit_dist = 2, max_dist = 35;

//This function maps distance to pwm
unsigned char distToPwm(int x) {
  unsigned char pwm = 0;
  //Full-scale deflection occurs at x = max_dist
  pwm = x / max_dist * 255;
  return pwm;
}

void setup_led() {
  for (int i = 2; i < 2 + 7; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void all_off() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(led[i], LOW);
  }
}

void update_led() {
  all_off();
  for (int i = 0; i < 7; i++) {
    if (distance > unit_dist * (i + i) ) digitalWrite(led[i], HIGH);
  }
  /*
    if (distance > 35 ) digitalWrite(led[6], HIGH);
    if (distance > 30 ) digitalWrite(led[5], HIGH);
    if (distance > 25 ) digitalWrite(led[4], HIGH);
    if (distance > 20 ) digitalWrite(led[3], HIGH);
    if (distance > 15 ) digitalWrite(led[2], HIGH);
    if (distance > 10 ) digitalWrite(led[1], HIGH);
    if (distance > 5 ) digitalWrite(led[0], HIGH);
  */
}

void write_led() {
  for (int i = 0; i < 7; i++) {
    analogWrite(i, intensity[i]);
  }
}
