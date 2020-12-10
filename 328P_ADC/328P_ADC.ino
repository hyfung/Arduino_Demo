volatile uint8_t low, high = 0;
volatile uint8_t channel = 0;
volatile unsigned int val[2] = {0};

void setup() {
  Serial.begin(115200);
  ADMUX = (1 << REFS0);
  ADCSRA |= (1 << ADEN);
  ADCSRA |= 0b00000111;
  DIDR0 = 0b00111111;
  ADCSRA |= (1 << ADIE);
  ADCSRA |= (1 << ADSC);
}

void loop() {
  //ADCSRA |= (1 << ADSC);
  //while (bit_is_set(ADCSRA, ADSC));
  //low  = ADCL;
  //high = ADCH;
  //Serial.println( (high << 8) | low);
  Serial.print(val[0]);
  Serial.print(",");
  Serial.println(val[1]);
  delay(10);
}


ISR(ADC_vect) {
  low = ADCL;
  high = ADCH;
  val[channel] = (high << 8 ) | low;
  channel = channel == 0 ? 1 : 0;
  //Set channel
  ADMUX = (1 << REFS0) | (channel);
  //Start ADC
  ADCSRA |= (1 << ADSC);
}
