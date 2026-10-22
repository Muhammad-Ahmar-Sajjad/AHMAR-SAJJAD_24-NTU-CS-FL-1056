
#include <Arduino.h>
#include <esp_arduino_version.h>

// Embedded IoT Systems - HOMEWORK 2_1056
// Task 1: Dual LED PWM Fading

#define LED1_PIN 18
#define LED2_PIN 19

#define LED1_FREQ 1000
#define LED2_FREQ 5000

#define PWM_RESOLUTION 8
#define MAX_DUTY 255

#define LED1_CHANNEL 0
#define LED2_CHANNEL 2

int duty1 = 0;
int duty2 = 255;

int direction1 = 1;
int direction2 = -1;

void setup() {
  Serial.begin(115200);

#if ESP_ARDUINO_VERSION_MAJOR >= 3

  bool ok1 = ledcAttach(LED1_PIN, LED1_FREQ,
                        PWM_RESOLUTION);
  bool ok2 = ledcAttach(LED2_PIN, LED2_FREQ,
                        PWM_RESOLUTION);

#else

  // Arduino-ESP32 2.x
  double freq1 = ledcSetup(LED1_CHANNEL,
                           LED1_FREQ,
                           PWM_RESOLUTION);
  double freq2 = ledcSetup(LED2_CHANNEL,
                           LED2_FREQ,
                           PWM_RESOLUTION);

  ledcAttachPin(LED1_PIN, LED1_CHANNEL);
  ledcAttachPin(LED2_PIN, LED2_CHANNEL);

  bool ok1 = freq1 > 0;
  bool ok2 = freq2 > 0;

#endif

  if (!ok1 || !ok2) {
    Serial.println("PWM setup failed!");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("Dual LED PWM Started");
  Serial.println("LED1: 1000 Hz");
  Serial.println("LED2: 5000 Hz");
}

void loop() {

#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWrite(LED1_PIN, duty1);
  ledcWrite(LED2_PIN, duty2);
#else
  ledcWrite(LED1_CHANNEL, duty1);
  ledcWrite(LED2_CHANNEL, duty2);
#endif

  Serial.print("LED1 Duty: ");
  Serial.print((duty1 * 100) / MAX_DUTY);
  Serial.print("% | LED2 Duty: ");
  Serial.print((duty2 * 100) / MAX_DUTY);
  Serial.println("%");

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
