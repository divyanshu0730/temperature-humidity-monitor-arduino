#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT22
#define BUZZER 8

const float TEMP_LIMIT = 35.0;  // is se upar buzzer bajega

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  pinMode(BUZZER, OUTPUT);
  lcd.print("Temp Monitor");
  delay(1500);
  lcd.clear();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    lcd.clear();
    lcd.print("Sensor error");
    noTone(BUZZER);
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t, 1);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum : ");
  lcd.print(h, 1);
  lcd.print(" %");

  if (t > TEMP_LIMIT) {
    tone(BUZZER, 1000);
  } else {
    noTone(BUZZER);
  }
}
