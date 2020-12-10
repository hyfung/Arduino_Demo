#include <Wire.h>
#include <ESP8266WiFi.h>
#include "DFRobot_LCD.h"

DFRobot_LCD lcd(16, 2);

const char* AP_SSID = "xxxx";
const char* AP_PW = "xxxx";

bool displayOn = true;

void setup() {
  ESP.wdtDisable();
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("Connecting");

  //Initialize WiFi Connection
  WiFi.begin(AP_SSID, AP_PW);

  // Wait for the Wi-Fi to connect
  while (WiFi.status() != WL_CONNECTED) {

    delay(250);
    displayOn = displayOn ? false : true;
    if (displayOn) {
      lcd.display();
    } else {
      lcd.noDisplay();
    }
    Serial.print('.');
  }
  lcd.display();
  lcd.clear();

  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  lcd.setPWM(REG_ONLY, 255);
  lcd.blinkLED();
}


void loop() {
  ESP.wdtFeed();
  delay(100);
}
