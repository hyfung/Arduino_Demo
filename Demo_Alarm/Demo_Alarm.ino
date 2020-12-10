void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT_PULLUP);
  GTCCR = 0;
  TCCR1 = 0;
  TCCR1 |= CTC1 << 1; //ENABLE CTC
  TCCR1 |= COM1A0 << 1; //TOGGLE OC1A ON MATCH
  TCCR1 |= CS13<<1;
  TCCR1 |= CS12<<1; //Prescaler:2048, Running at 3906.25Hz
  OCR1C = 255;//This is our upper limit, equal to 0.5*Period 
}

void loop() {
  if (digitalRead(2) == 0 ) alarm();
}

void alarm() {
  for (int i = 0; i < 256; i++) {
    tone(1, i << 3);
    delay(10);
  }
  for (int i = 255; i > 0 ; i -= 2) {
    tone(1, i << 3);
    delay(10);
  }
}

