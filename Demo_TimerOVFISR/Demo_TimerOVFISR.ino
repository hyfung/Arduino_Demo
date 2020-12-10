volatile bool x = HIGH;
volatile bool y = LOW;
volatile int counter = 0;
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  cli(); //Disable Interrupt
  TCNT2 = 0;
  TCCR2A = 0;
  TCCR2B = 0x07; //CS[2:0] = '111'
  TIMSK2 = 0x1; //Overflow Vector Enable
  sei();//Enable Interrupt
  Serial.println("Hello world!");
}

void loop() {
}

ISR(TIMER2_OVF_vect) {
  if (counter == (61) ) {
    Serial.println("Flipping!");
    digitalWrite(13, x ? HIGH : LOW);
    x = !x;
    counter = 0;
  }
  else counter++;
}
