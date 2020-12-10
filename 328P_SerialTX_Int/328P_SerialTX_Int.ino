#define F_MCU 16000000L
volatile static int i = 0;
const static uint8_t data[] = "Hello from ATmega328p\r\n";


void setup() {
  serialInit();
  UDR0 = data[0];
}

void loop() {
}

void serialInit() {
  unsigned int ubrr = 8;

  /* Set Baudrate  */
  UBRR0H = (ubrr >> 8);
  UBRR0L = (ubrr);

  /* Set frame format: 8data, 1stop bit  */
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  /* Enable  transmitter                 */
  UCSR0B = (1 << TXCIE0) | (1 << TXEN0);

}

ISR(USART_TX_vect) {
  if (data[i] == 0) i = 0;
  while (!( UCSR0A & (1 << UDRE0)));
  UDR0 = data[i];
  i++;
}
