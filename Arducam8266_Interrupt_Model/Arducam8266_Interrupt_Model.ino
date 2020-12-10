#define BTN_A 13
#define BTN_B 14
#define ISR_A 0
#define ISR_B 1
#define ISR_C 2
#define ISR_D 3
#define ISR_E 4
#define ISR_F 5
#define ISR_G 6
#define ISR_H 7

volatile uint8_t interrupt_flag = 0;

void setup() {
  attachInterrupt(digitalPinToInterrupt(BTN_A), BTN_A_Handler, FALLING);

}

void loop() {
  if (interrupt_flag) {
    //Has pending interrupt
    //Turn on signal lamp
  }

  if (interrupt_flag && (1 << ISR_A)) {
    interrupt_flag &= ! (1 << ISR_A);
  }

  if (interrupt_flag && (1 << ISR_B)) {
    //Callback function
    interrupt_flag &= ! (1 << ISR_B);
  }

}

void foo() {
}



ICACHE_RAM_ATTR void BTN_A_Handler() {
  interrupt_flag |= (1 << ISR_A);
}
