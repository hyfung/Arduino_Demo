volatile unsigned int ADC_RES = 0;

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADCSRB = 0;
  DIDR0 = (1 << ADC0D);
  ADCSRA |= (1 << ADSC);
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println(ADC_RES);
  delay(500);
}

ISR(ADC_vect) {
  
}
