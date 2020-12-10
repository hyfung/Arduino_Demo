#define LED 13
#define F_MCU 16000000L

volatile uint8_t led = 0;
volatile uint8_t rxRingBufferPointer = 0;
volatile uint8_t rxRingBuffer[32] = {0};

void setup() {
  uint32_t UBRRn = 8;

  //Baud rate 115200, no double data rate
  UBRR0H = (UBRRn & 0xff00) >> 8;
  UBRR0L = (UBRRn & 0xff);

  UCSR0B = (1 << RXCIE0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //8-bit
}

void loop() {


}

ISR(USART_RX_vect) {
  rxRingBuffer[rxRingBufferPointer++] = UDR0;
  rxRingBufferPointer &= 0x20;
}
