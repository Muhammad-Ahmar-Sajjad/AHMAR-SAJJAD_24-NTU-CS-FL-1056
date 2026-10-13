#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

//AHMAR_1056

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C
#define DHT_PIN 18

// Real hardware = DHT11 (default). Sirf Wokwi build me DHT22 use hota hai.
#ifdef WOKWI_SIM
  #define DHT_TYPE DHT22
#else
  #define DHT_TYPE DHT11
#endif

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHT_PIN, DHT_TYPE);

const unsigned long READ_INTERVAL_MS = 2000;
unsigned long lastReadTime = 0;
bool firstRead = true;

// Layout (128x64):
//  y 0-15  : header (yellow zone on 2-colour OLEDs)
//  y 18-33 : temperature row
//  y 42-57 : humidity row
const int VALUE_X = 46;  // values start here, labels stay on the left

// Text ko horizontally center karta hai
void printCentered(const char* text, int y, uint8_t size) {
  int16_t x1, y1;
  uint16_t w, h;
  display.setTextSize(size);
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - w) / 2, y);
  display.print(text);
}

void showMessage(const char* line1, const char* line2) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  printCentered(line1, 16, 1);
  printCentered(line2, 32, 1);
  display.display();
}

void showMeasurements(float humidity, float temperature) {
  char buf[16];

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Header
  printCentered("ENVIRONMENT MONITOR", 2, 1);
  display.drawLine(0, 12, SCREEN_WIDTH - 1, 12, SSD1306_WHITE);

  // Temperature row
  display.setTextSize(1);
  display.setCursor(0, 22);
  display.print("TEMP");
  display.setTextSize(2);
  display.setCursor(VALUE_X, 18);
  snprintf(buf, sizeof(buf), "%.1f", temperature);
  display.print(buf);
  display.write(247);  // degree symbol
  display.print("C");

  // Humidity row
  display.setTextSize(1);
  display.setCursor(0, 46);
  display.print("HUM");
  display.setTextSize(2);
  display.setCursor(VALUE_X, 42);
  snprintf(buf, sizeof(buf), "%.1f%%", humidity);
  display.print(buf);

  display.display();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("ERROR: OLED initialization failed. Check power, SDA/SCL, and I2C address.");
    while (true) { delay(100); }
  }

  dht.begin();
  showMessage("ESP32 ENVIRONMENT", "Starting sensor...");
  Serial.print("ESP32 monitor started. Sensor type: ");
  Serial.println(DHT_TYPE == DHT11 ? "DHT11" : "DHT22");
  delay(1500);  // sensor ko stable hone ka time
}

void loop() {
  const unsigned long now = millis();
  if (firstRead || (now - lastReadTime >= READ_INTERVAL_MS)) {
    firstRead = false;
    lastReadTime = now;

    const float humidity = dht.readHumidity();
    const float temperature = dht.readTemperature();

    // NaN ya impossible values ko reject karo (galat sensor type / noise)
    const bool invalid = isnan(humidity) || isnan(temperature) ||
                         humidity < 0 || humidity > 100 ||
                         temperature < -40 || temperature > 80;

    if (invalid) {
      Serial.println("DHT read failed or out of range! Check DATA pin, power, GND, sensor type.");
      showMessage("SENSOR ERROR", "Check DHT wiring");
      return;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity, 1);
    Serial.print(" %   Temperature: ");
    Serial.print(temperature, 1);
    Serial.println(" C");
    showMeasurements(humidity, temperature);
  }
}