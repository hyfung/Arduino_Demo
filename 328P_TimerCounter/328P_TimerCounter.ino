volatile struct {
  uint32_t second = 0;
  uint16_t milli = 0;
} MasterClock;

// volatile unsigned int milli = 0;
volatile uint8_t led = 0;

void setup() {
  pinMode(13, OUTPUT);
  //  //Prescaler 64
  TCCR0A = (1 << WGM01);
  TCCR0B = (1 << CS01) | (1 << CS00);
  //
  //  //OCR1A 0-249
  OCR0A = 249;
  TIMSK0 = (1 << OCIE0A);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  //  delay(500);


  //  Serial.println(TCNT0/);

}

ISR (TIMER0_COMPA_vect) {

  MasterClock.milli++;
  
  if (MasterClock.milli % 999 == 0) {
    MasterClock.milli = 0;
    MasterClock.second++;
    Serial.println(MasterClock.milli);
    digitalWrite(13, led ? HIGH : LOW);

    led = led ? 0 : 1;
  }
}
