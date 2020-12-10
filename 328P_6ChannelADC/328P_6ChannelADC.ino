#define BV(x) (1<<x)
#define set(REG,BIT) REG |= BV(BIT)
#define clear(REG,BIT) REG &= ~BV(BIT)
#define toggle(REG,BIT) REG ^= BV(BIT)

volatile static uint8_t channel = 0;
volatile static uint16_t adcResult[6] = {0};
volatile uint8_t low, high;

void setup() {
  adcInit();
  Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < 6; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(adcResult[i]);
  }
  delay(50);
}

void adcInit() {
  ADMUX = (1 << REFS0);
  ADCSRA |= (1 << ADEN);
  ADCSRA |= 0b00000111;
  DIDR0 = 0b00111111;
  ADCSRA |= (1 << ADIE);
  ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect) {
  low = ADCL;
  high = ADCH;
  adcResult[channel] = (high << 8) | low;
  channel ++;
  channel %= 6;

  //channel = channel == 0 ? 1 : 0;

  ADMUX &= ~0b00001111; //Reset ADMUX channel
  ADMUX |= (1 << REFS0) | channel;

  ADCSRA |= (1 << ADSC); //Start conversion

}
