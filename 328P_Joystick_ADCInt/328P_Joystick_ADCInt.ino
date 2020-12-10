#define BV(x) (1<<x)
volatile uint8_t currentAdc = 0;
volatile unsigned short adcResult[2] = {0};

void setup() {
  adcInit();
  Serial.begin(115200);
}

void loop() {
  delay(1000);
  Serial.println((ADCH<<8) | ADCL);
}

void adcInit() {
  //Ref AVcc
  ADMUX = (1 << REFS0);
  ADCSRA = BV(ADEN) | BV(ADATE) | BV(ADIE);// | BV(ADPS2) | BV(ADPS1) | BV(ADPS0);
  //Disable Input on 2 pin
  //DIDR0 = BV(ADC0D) | BV(ADC1D);

  ADCSRA |= BV(ADSC);
}

ISR(ADC_vect) {
  ADCSRA = BV(ADEN) | BV(ADATE) | BV(ADIE) | BV(ADPS2) | BV(ADPS1) | BV(ADPS0);
  ADCSRA |= BV(ADSC);
}
//ADCSRA |= BV(ADSC);
