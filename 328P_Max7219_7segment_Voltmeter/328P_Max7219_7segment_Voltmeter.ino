const uint8_t DIN = 12;
const uint8_t CS = 11;
const uint8_t CLK = 10;

const uint8_t SENSE = A0;

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
  Serial.begin(115200);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);

  //Show only 2DP
  set_register(MAX7219_SCANLIMIT_REG, 2);

  //Brightest
  set_register(MAX7219_INTENSITY_REG, 0xF);

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

void show_float(float number, uint8_t mask = 8) {
}

void loop() {
  float voltage = analogRead(A0);
  Serial.print("Raw voltage: ");
  Serial.println(voltage);
  float normalizedVoltage = voltage * 5 / 1024;
  Serial.print("Normalized Voltage: ");
  Serial.println(normalizedVoltage);
  set_register(3, 0b10000000 | uint8_t(normalizedVoltage));

  int decimal = normalizedVoltage * 100;
  decimal %= 100;
  Serial.print("Decimal part: ");
  Serial.println(decimal);

  set_register(2, decimal / 10);
  set_register(1, decimal % 10);

  //  show_uint(voltage, 4);
  delay(400);
}
