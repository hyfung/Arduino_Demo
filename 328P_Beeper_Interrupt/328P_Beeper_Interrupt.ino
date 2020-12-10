#define BV(x) (1<<x)
#define set(reg,bit) reg |= bit
#define clear(reg,bit) reg &= ~bit

volatile static uint32_t milli = 0;
volatile uint8_t i = 0;
uint16_t interval[] = {500, 250, 100, 50};
//volatile uint16_t adcResult = 0;
volatile union {
  uint8_t bytes[2];
  uint16_t whole;
} adcResult;

void setup() {
  Serial.begin(115200);
  DDRB = BV(3) | BV(5);
  PORTB = BV(5);
  //PD2 input
  DDRD = ~BV(2);
  //PD2 input pullup
  PORTD = BV(2);
  SystickInit();
  AdcIntInit();

}

void loop() {

}

void SystickInit() {
  //Toggle OC2A on compare match
  //CTC mode on OCRA
  TCCR2A = BV(COM2A0) | BV(WGM01);

  TCCR2B = BV(CS22);

  //Compare match on 0 to 249

  OCR2A = 249;

  // OCR2B = 249;

  TIMSK2 = BV(OCIE2A);
  // TIFR2 = 0;

  //ISC01: Falling INT0 generates interrupt request
  EICRA = BV(ISC01);

  //Enable INT0
  EIMSK = BV(INT0);

}

void AdcIntInit() {
  //Description: Free runnung ADC at A0
  ADCSRA = BV(ADEN) | BV(ADATE) | BV(ADIE) | BV(ADPS2) | BV(ADPS1) | BV(ADPS0) ;
  ADMUX = BV(REFS0) | 0x0; //Select Channel: A0
  DIDR0 = 0x1; //Disable Digital Input on A0
  ADCSRA |= BV(ADSC);

}


volatile bool flip = false;
ISR(TIMER2_COMPA_vect) {
  milli++;

  if (adcResult.whole > 400) {
    i = 3;
    flip = true;
  } else flip = false;

  if (milli % interval[i] == 0) {
    //Serial.println(milli);
    PORTB ^= BV(5);
    if (flip) {
      TCCR2A ^= BV(COM2A0);
    } else TCCR2A &= ~BV(COM2A0);
  }

}

ISR(INT0_vect) {
  asm volatile("jmp 0");
}

ISR(ADC_vect) {
  //adcResult = (ADCH << 8 ) | ADCL;
  adcResult.bytes[1] = (uint8_t)ADCH;
  adcResult.bytes[0] = (uint8_t)ADCL;
  Serial.println((unsigned short)adcResult.whole);
}
