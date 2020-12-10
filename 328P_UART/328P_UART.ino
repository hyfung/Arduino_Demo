#define F_MCU 16000000L
volatile static int i = 0;
const static uint8_t data[] = "Hello from ATmega328p\r\n";


void setup() {
  serialInit();
}

void loop() {
  while (1) /* Loop the messsage continously */
  {
    i = 0;
    while (data[i] != 0) /* print the String  "Hello from ATmega328p" */
    {
      serialSend(data[i]);
      i++;                             /* increment counter           */
    }
  }
}

void serialInit() {
  unsigned int ubrr = 8;

  /* Set Baudrate  */
  UBRR0H = (ubrr >> 8);
  UBRR0L = (ubrr);

  /* Set frame format: 8data, 1stop bit  */
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  /* Enable  transmitter                 */
  UCSR0B = (1 << TXEN0);

}

void serialSend(uint8_t ch) {
  while (!( UCSR0A & (1 << UDRE0))); /* Wait for empty transmit buffer*/
  UDR0 = ch;

}
