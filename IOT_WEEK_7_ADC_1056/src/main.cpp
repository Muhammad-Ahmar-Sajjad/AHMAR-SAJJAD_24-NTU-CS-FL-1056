#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LDR_PIN 34
#define SDA_PIN 21
#define SCL_PIN 22
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int adcValue = analogRead(LDR_PIN);
  float voltage = (adcValue / 4095.0) * 3.3;

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,10);
  display.print("LDR ADC: "); display.println(adcValue);
  display.print("Voltage: "); display.print(voltage, 2); display.println(" V");
  display.display();

  Serial.printf("ADC: %d  |  Voltage: %.2f V\n", adcValue, voltage);
  delay(1000);
}