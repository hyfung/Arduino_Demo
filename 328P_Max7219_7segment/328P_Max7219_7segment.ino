const int DIN = 12;
const int CS = 11;
const int CLK = 10;

#define MAX7219_OFF (0x0)
#define MAX7219_ON  (0x1)

#define MAX7219_DECODE_REG      (0x09)
#define MAX7219_DIGIT_REG(pos)  ((pos) + 1)
#define MAX7219_INTENSITY_REG   (0x0A)
#define MAX7219_SCANLIMIT_REG   (0x0B)
#define MAX7219_SHUTDOWN_REG    (0X0C)
#define MAX7219_DISPLAYTEST_REG (0x0F)

void set_register(byte address, byte value)
{
  digitalWrite(CS, LOW);
  shiftOut(DIN, CLK, MSBFIRST, address);
  shiftOut(DIN, CLK, MSBFIRST, value);
  digitalWrite(CS, HIGH);
}

void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  // Only Digit 0 are turned on
  set_register(MAX7219_SCANLIMIT_REG, 0);
  // Only Digit 0 ~ Digit 4 are turned on
  set_register(MAX7219_SCANLIMIT_REG, 4);
  // All digits (Digit 0 ~ Digit 7) are turned on
  set_register(MAX7219_SCANLIMIT_REG, 7);

  //Intensity setting from 0x0 to 0xF
  // Dimmest
  set_register(MAX7219_INTENSITY_REG, 0x0);
  // Brightest
  set_register(MAX7219_INTENSITY_REG, 0xF);

  //Binary Mode: 0
  //BCD    Mode: 1
  set_register(0x09, 0xFF);

  //Setting individual digit
  set_register(0x1, 6);
  set_register(0x2, 2);
  set_register(0x3, 8);
  set_register(0x4, 2);
  set_register(0x5, 4);
  set_register(0x6, 0);
  set_register(0x7, 2);
  set_register(0x8, 10);

  // Enter test mode. No matter what data bytes of each digit register are, all display segments are on
  set_register(MAX7219_DISPLAYTEST_REG, MAX7219_ON);
  // Non-test mode. Display segments according to the data byte and decode mode for each digit
  set_register(MAX7219_DISPLAYTEST_REG, MAX7219_OFF);

}

void show_uint(unsigned int number, uint8_t mask = 8) {
  set_register(MAX7219_SCANLIMIT_REG, mask - 1);
  set_register(0x1, number % 10);
  set_register(0x2, number % 100 / 10);
  set_register(0x3, number % 1000 / 100);
  set_register(0x4, number % 10000 / 1000);
  set_register(0x5, number % 100000 / 10000);
  set_register(0x6, number % 1000000 / 100000);
  set_register(0x7, number % 10000000 / 1000000);
  set_register(0x8, number % 100000000 / 10000000);
}

void show_float(float number, mask = 8) {
}

void loop() {
  //  set_register(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
  //  delay(500);
  //
  set_register(MAX7219_SHUTDOWN_REG, MAX7219_ON);
  //  delay(500);

  show_number(34, 7);




}
