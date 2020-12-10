/*
  LY-S0024 Rotary Encoder Demo

  Pin Description
  LY-S0024  UNO
  A         A0(PCINT8)
  B         A1(PCINT9)
  Key       2(EINT0)

*/

#define PA A0 //PCINT8
#define PB A1 //PCINT9
#define KEY 2 //EINT0

int val;
const uint8_t encoder0PinA = PA;
const uint8_t encoder0PinB = PB;
volatile uint8_t encoder0Pos = 0;
volatile uint8_t encoder0PinALast = LOW;
volatile uint8_t n = LOW;
volatile uint8_t encoderStateLast = 0x0;
volatile uint8_t encoderStateNow = 0x0;

volatile uint8_t ledState = LOW;

void setup() {

  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(KEY, INPUT_PULLUP);
  Serial.begin(115200);

  //Enable PCINT on 8,9
  PCMSK1 = 0b00000011;

  //Enable PCINT1
  PCICR = (1 << PCIE1);

  EIMSK = (1 << INT0);
  EICRA =  (1 << ISC01) | (1 << ISC00);

  sei();
}

void loop() {
  digitalWrite(13, ledState);

  if (encoder0Pos > 180) {
    encoder0Pos = 180;
  }

}

//Version 1
//ISR(PCINT1_vect) {
//  n = digitalRead(encoder0PinA);
//  if ((encoder0PinALast == LOW) && (n == HIGH)) {
//    if (digitalRead(encoder0PinB) == LOW) {
//      encoder0Pos++;
//    } else {
//      encoder0Pos--;
//    }
//    Serial.println(encoder0Pos);
//  }
//  encoder0PinALast = n;
//}

//Version 2
ISR(PCINT1_vect) {
  encoderStateNow = (digitalRead(encoder0PinA) << 1) | digitalRead(encoder0PinB);
  switch (encoderStateNow) {
    case 0x0:
      if (encoderStateLast == 0x2) encoder0Pos--;
      if (encoderStateLast == 0x1) encoder0Pos++;
      break;
    case 0x1:
      if (encoderStateLast == 0x0) encoder0Pos--;
      if (encoderStateLast == 0x3) encoder0Pos++;
      break;
    case 0x2:
      if (encoderStateLast == 0x3) encoder0Pos--;
      if (encoderStateLast == 0x0) encoder0Pos++;
      break;
    case 0x3:
      if (encoderStateLast == 0x1) encoder0Pos--;
      if (encoderStateLast == 0x2) encoder0Pos++;
      break;
  }
  encoderStateLast = encoderStateNow;
}


ISR(INT0_vect) {
  Serial.println("EINT0");
  if (ledState == HIGH) ledState = LOW;
  else ledState = HIGH;
}
