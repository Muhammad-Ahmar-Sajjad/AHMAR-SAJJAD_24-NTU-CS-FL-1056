#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C
#define DHT_PIN 19
#define DHT_TYPE DHT11

Adafruit_SSD1306 display(
    SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1
);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    Serial.begin(115200);
    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("OLED initialization failed!");
        while (true) { delay(100); }
    }

    dht.begin();

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("ESP32 Environment");
    display.println("Initializing...");
    display.display();

    delay(2000);
}

void loop() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("DHT11 read failed!");

        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.println("Sensor Error");
        display.println("Check DHT11");
        display.display();

        delay(2000);
        return;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity, 1);
    Serial.print(" %   Temperature: ");
    Serial.print(temperature, 1);
    Serial.println(" C");

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("ENVIRONMENT MONITOR");
    display.drawLine(0, 12, 127, 12, SSD1306_WHITE);

    display.setCursor(0, 20);
    display.print("Humidity: ");
    display.print(humidity, 1);
    display.println(" %");

    display.setCursor(0, 36);
    display.print("Temp: ");
    display.print(temperature, 1);
    display.println(" C");

    display.display();
    delay(2000);
}