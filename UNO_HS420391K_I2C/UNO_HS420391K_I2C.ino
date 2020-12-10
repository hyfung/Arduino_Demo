#include <Wire.h>
unsigned char MY_ADDR = 0x30; //Less than 127
int numByte = 2;
volatile unsigned int Display = 0;
String inString = "";

void setup() {
  inString.reserve(64);
  DDRB = 0xFF; //Output
  PORTD = 0x0; //Pull-low
  DDRC = 0xF;//C[0:3] Input
  PORTC = 0x0;//Pull-low
  Wire.begin(MY_ADDR);
  Wire.onReceive(I2C_Handler);
}

void loop() {

}

void I2C_Handler(int numByte) {
  inString = "";
  while ( Wire.available() > 0) {
    char c = Wire.read();
    inString += c;
  }
  Display = inString.toInt();
}

void Display_digit(int x) {

}

