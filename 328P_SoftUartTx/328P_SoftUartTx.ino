#define TX_PIN 13
#define BAUD 9600
#define BAUD_INV 100
/*
  BAUD 9600 = 104 microseconds

*/

const char str[] = "helloworld\r\n";

volatile uint8_t state = 0;

void setup() {
  pinMode(TX_PIN, OUTPUT);

}

void loop() {
  //Hold line high
  digitalWrite(TX_PIN, HIGH);
  delay(1000);

  for (int i = 0; i < strlen(str); i++) {
    //Start Bit
    digitalWrite(TX_PIN, LOW);
    delayMicroseconds(BAUD_INV);

    for (int j = 0; j < 8; j++) {
      digitalWrite(TX_PIN, (str[i] & (1 << j) ) ? HIGH : LOW);
      delayMicroseconds(BAUD_INV);
    }

    //Stop Bit
    digitalWrite(TX_PIN, HIGH);
    delayMicroseconds(BAUD_INV);
  }


  //  digitalWrite(TX_PIN, LOW);
  //  delayMicroseconds(BAUD_INV);
  //
  //  digitalWrite(TX_PIN, HIGH);
  //  delayMicroseconds(BAUD_INV);
  //
  //  digitalWrite(TX_PIN, LOW);
  //  delayMicroseconds(5 * BAUD_INV);
  //
  //  digitalWrite(TX_PIN, HIGH);
  //  delayMicroseconds(BAUD_INV);
  //
  //  digitalWrite(TX_PIN, LOW);
  //  delayMicroseconds(BAUD_INV);
  //
  //  digitalWrite(TX_PIN, HIGH);
  //  delayMicroseconds(BAUD_INV);

}

void timer0Init() {

}

ISR(TIMER0_COMPA_vect) {

}
