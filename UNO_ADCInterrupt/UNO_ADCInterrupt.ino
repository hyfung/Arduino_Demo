volatile uint16_t ADC_Result[6] = {0};
volatile unsigned char Current_ADC = 0; //Index Tracker
void setup() {
  cli();
  for (int i = A0; i < A5 + 1; i++) pinMode(i, INPUT);
  ADCSRA |= 1 << ADEN; //Enable ADC
  ADCSRA |= 1 << ADIE; //ADIE interrupt enable
  ADCSRA |= 0b111;//Prescaler 2:0, 128 of I/O clk
  sei();
  ADCSRA |= 1 << ADSC; //Start new conversion
  //----Don't modify above code
}

void loop() {

}

ISR(ADC_vect) {
  ADC_Result[Current_ADC] = (uint16_t)( (ADCH << 8) | ADCL );
  Current_ADC++; //Switch channel
  Current_ADC %= 6; //Channel 0 to 5 only
  ADMUX = 0b0100000 | Current_ADC; //Channel Selector MUX[3:0] => ADC0 to 7
  ADCSRA |= 1 << ADSC; //Start new conversion
}
