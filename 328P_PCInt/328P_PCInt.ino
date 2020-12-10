/*
  To be used with 7-Segment Development Shield
*/

#define PC1 A1 //PCINT9
#define PC2 A2 //PCINT10
#define PC3 A3 //PCINT11

volatile uint32_t last = 0;
bool states[3] = {false};
volatile uint8_t pinC = 0;

void setup() {
  Serial.begin(115200);

  //Enable Group 1 PCINT, 14...8
  PCICR = (1 << PCIE1);

  //Enable PCINT on pins
  PCMSK1 = (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);

  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  digitalWrite(13, states[0]);
  digitalWrite(12, states[1]);
  digitalWrite(11, states[2]);
}

ISR(PCINT1_vect) {
  if ((millis() - 200) < last) return;
  last = millis();

  pinC = PINC & 0b00001110;
  switch (pinC) {
    case 0b00001100:
      states[0] = !states[0];
      break;

    case 0b00001010:
      states[1] = !states[1];
      break;

    case 0b00000110:
      states[2] = !states[2];
      break;
  }

  //Check which pin is pulled low
  //  if (PINC | 0x1) {
  //    Serial.println("1");
  //  }
  //  if (PINC ^ 0x2) {
  //    Serial.println("2");
  //  }
  //  if (PINC | 0x4) {
  //    Serial.println("3");
  //  }

  Serial.print(digitalRead(A1));
  Serial.print(',');
  Serial.print(digitalRead(A2));
  Serial.print(',');
  Serial.print(digitalRead(A3));
  Serial.println();
}
