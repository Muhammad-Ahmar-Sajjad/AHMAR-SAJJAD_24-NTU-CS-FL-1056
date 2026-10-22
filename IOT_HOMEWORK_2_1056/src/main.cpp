
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <esp_arduino_version.h>

// Embedded IoT Systems - HOMEWORK_2_1056
// Task 2: Dual LED PWM with OLED Monitoring

#define LED1_PIN 18
#define LED2_PIN 19

#define LED1_FREQ 1000
#define LED2_FREQ 5000

#define PWM_RESOLUTION 8
#define MAX_DUTY 255

#define LED1_CHANNEL 0
#define LED2_CHANNEL 2

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1
);

// PWM variables
int duty1 = 0;
int duty2 = 255;

int direction1 = 1;
int direction2 = -1;

// Display actual values applied to PWM
void updateOLED() {
  int percent1 = (duty1 * 100) / MAX_DUTY;
  int percent2 = (duty2 * 100) / MAX_DUTY;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("PWM MONITOR");
  display.println("---------------------");

  display.print("LED1: ");
  display.print(percent1);
  display.println("%");

  display.print("F: ");
  display.print(LED1_FREQ);
  display.println(" Hz");

  display.println();

  display.print("LED2: ");
  display.print(percent2);
  display.println("%");

  display.print("F: ");
  display.print(LED2_FREQ);
  display.println(" Hz");

  display.display();
}

void setup() {
  Serial.begin(115200);

  // Initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED initialization failed!");
    while (true) {
      delay(1000);
    }
  }

#if ESP_ARDUINO_VERSION_MAJOR >= 3

  bool ok1 = ledcAttach(
    LED1_PIN, LED1_FREQ, PWM_RESOLUTION
  );

  bool ok2 = ledcAttach(
    LED2_PIN, LED2_FREQ, PWM_RESOLUTION
  );

#else

  double freq1 = ledcSetup(
    LED1_CHANNEL, LED1_FREQ, PWM_RESOLUTION
  );

  double freq2 = ledcSetup(
    LED2_CHANNEL, LED2_FREQ, PWM_RESOLUTION
  );

  ledcAttachPin(LED1_PIN, LED1_CHANNEL);
  ledcAttachPin(LED2_PIN, LED2_CHANNEL);

  bool ok1 = freq1 > 0;
  bool ok2 = freq2 > 0;

#endif

  if (!ok1 || !ok2) {
    Serial.println("PWM initialization failed!");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("Dual LED PWM + OLED Started");
}

void loop() {

  // Apply PWM duty cycles
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWrite(LED1_PIN, duty1);
  ledcWrite(LED2_PIN, duty2);
#else
  ledcWrite(LED1_CHANNEL, duty1);
  ledcWrite(LED2_CHANNEL, duty2);
#endif

  // Update OLED with current duty cycles
  updateOLED();

  // Serial monitor output
  Serial.print("LED1: ");
  Serial.print((duty1 * 100) / MAX_DUTY);
  Serial.print("% @ ");
  Serial.print(LED1_FREQ);
  Serial.print("Hz | LED2: ");
  Serial.print((duty2 * 100) / MAX_DUTY);
  Serial.print("% @ ");
  Serial.print(LED2_FREQ);
  Serial.println("Hz");

  // Change brightness for next iteration
  duty1 += direction1 * 5;
  duty2 += direction2 * 5;

  if (duty1 >= MAX_DUTY) {
    duty1 = MAX_DUTY;
    direction1 = -1;
  }
  else if (duty1 <= 0) {
    duty1 = 0;
    direction1 = 1;
  }

  if (duty2 >= MAX_DUTY) {
    duty2 = MAX_DUTY;
    direction2 = -1;
  }
  else if (duty2 <= 0) {
    duty2 = 0;
    direction2 = 1;
  }

  delay(20);
}
