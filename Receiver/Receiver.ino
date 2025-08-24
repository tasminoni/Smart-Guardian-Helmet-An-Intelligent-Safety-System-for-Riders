/*
  Smart Helmet Receiver Code (with Temperature Monitoring)
  - Receives "H,A,S,T"
  - Controls engine relay
  - Displays Helmet, Alcohol, Sleep, Engine, Temperature
  - Warns if too hot
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RH_ASK.h>
#include <SPI.h>

// ==== CONFIG ====
#define ACTIVE_LOW_RELAY 1   // 1 = LOW turns relay ON; 0 = HIGH turns relay ON
// =================

LiquidCrystal_I2C lcd(0x27, 16, 2);
RH_ASK rf_driver(2000, 11, 12, 0);

const int ignitionRelay = 4;
const int buzzerPin     = 5;

String str_helmet = "0", str_alcohol = "0", str_sleep = "0", str_temp = "0";
int helmetStatus = 0, alcoholLevel = 0, sleepStatus = 0, tempValue = 0;
bool engineState = false;

unsigned long lastReceivedTime = 0;
const unsigned long timeout = 5000;

int page = 0, lastPage = -1;
unsigned long lastPageSwitch = 0;
const unsigned long pageInterval = 3000;

void setEngineOutput(bool on) {
#if ACTIVE_LOW_RELAY
  digitalWrite(ignitionRelay, on ? LOW : HIGH);
#else
  digitalWrite(ignitionRelay, on ? HIGH : LOW);
#endif
}

void setup() {
  Serial.begin(115200);
  rf_driver.init();

  pinMode(ignitionRelay, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Safe defaults: engine OFF, buzzer OFF
#if ACTIVE_LOW_RELAY
  digitalWrite(ignitionRelay, HIGH);
#else
  digitalWrite(ignitionRelay, LOW);
#endif
  digitalWrite(buzzerPin, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Helmet");
  delay(1000);
  lcd.clear();
}

void loop() {
  uint8_t buf[30];
  uint8_t buflen = sizeof(buf) - 1;

  // === Receive RF Data ===
  if (rf_driver.recv(buf, &buflen)) {
    buf[buflen] = 0;
    String str_out = String((char*)buf);
    lastReceivedTime = millis();

    int c1 = str_out.indexOf(',');
    int c2 = str_out.indexOf(',', c1 + 1);
    int c3 = str_out.indexOf(',', c2 + 1);

    if (c1 > 0 && c2 > c1 && c3 > c2) {
      str_helmet  = str_out.substring(0, c1);
      str_alcohol = str_out.substring(c1 + 1, c2);
      str_sleep   = str_out.substring(c2 + 1, c3);
      str_temp    = str_out.substring(c3 + 1);

      helmetStatus = str_helmet.toInt();
      alcoholLevel = str_alcohol.toInt();
      sleepStatus  = str_sleep.toInt();
      tempValue    = str_temp.toInt();

      // Engine ON only if helmet=1, alcohol=0, sleep=0
      engineState = (helmetStatus == 1) && (alcoholLevel == 0) && (sleepStatus == 0);
      setEngineOutput(engineState);

      Serial.print("RX: ");
      Serial.println(str_out);
    }
  }

  // === Timeout Handling ===
  bool timeoutActive = (millis() - lastReceivedTime > timeout);
  if (timeoutActive) {
    digitalWrite(buzzerPin, HIGH);
    if (page != 99) {
      lcd.clear();
      lcd.print("No Data Received");
      lcd.setCursor(0, 1);
      lcd.print("System Offline");
      page = 99;
    }
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  // === Page Switching ===
  if (!timeoutActive && millis() - lastPageSwitch > pageInterval) {
    lastPageSwitch = millis();
    page = (page + 1) % 3; // 3 pages now
    delay(200);
  }

  if (!timeoutActive && page != lastPage) {
    lcd.clear();
    lastPage = page;
  }

  // === Display Pages ===
  if (!timeoutActive) {
    switch (page) {
      case 0:  // Helmet & Alcohol
        lcd.setCursor(0, 0);
        lcd.print("Helmet: ");
        lcd.print(helmetStatus ? "Yes" : "No ");

        lcd.setCursor(0, 1);
        lcd.print("Alcohol: ");
        lcd.print(alcoholLevel ? "Yes" : "No ");
        break;

      case 1:  // Sleep & Engine
        lcd.setCursor(0, 0);
        lcd.print("Sleep: ");
        lcd.print(sleepStatus ? "Yes" : "No ");

        lcd.setCursor(0, 1);
        lcd.print("Engine: ");
        lcd.print(engineState ? "ON " : "OFF");
        break;

      case 2:  // Temperature Page
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(tempValue);
        lcd.print((char)223); // degree symbol
        lcd.print("C");

        lcd.setCursor(0, 1);
        if (tempValue >= 35) {
          lcd.print("WARNING: HOT! ");
        } else {
          lcd.print("Normal        ");
        }
        break;
    }
  }
}
