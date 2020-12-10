#include <LiquidCrystal.h>
String inString;
String DisplayString;
#define LCD_RS 11
#define LCD_RW 12
#define LCD_E 13
LiquidCrystal LCD(LCD_RS, LCD_RW, LCD_E, 3, 4, 5, 6, 7, 8, 9, 10);

void setup() {
  Serial.begin(115200);
  inString.reserve(64);
  LCD.begin(16, 2); //2 row of 16 column
  LCD.noAutoscroll();
  LCD.print("LCD Serial");
  LCD.setCursor(0, 1);
  LCD.noCursor();
  LCD.print("Awaiting");
  while ( !Serial.available() );
  LCD.clear();
}

void loop() {
  while (Serial.available() > 0) {
    char buf = Serial.read();
    switch (buf) {
      case '\0':
        LCD.clear();
        LCD.home();
        break;
      case '\r':
      case '\n':
        LCD.setCursor(0, 1);
        break;
      default:
        LCD.write(buf);
        break;
    }
  }
}
