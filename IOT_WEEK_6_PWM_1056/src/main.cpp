
#include <Arduino.h>

constexpr uint8_t LED_PIN=4;
constexpr uint8_t PWM_CHANNEL=0;
constexpr uint32_t PWM_FREQUENCY=5000;
constexpr uint8_t PWM_RESOLUTION=8;
constexpr uint16_t PWM_MAX_DUTY=255;

void setup()
{
    Serial.begin(115200);
    ledcSetup(PWM_CHANNEL,PWM_FREQUENCY,PWM_RESOLUTION);
    ledcAttachPin(LED_PIN,PWM_CHANNEL);
    ledcWrite(PWM_CHANNEL,0);
    Serial.println("ESP32 PWM LED Fade Started");
}

void loop()
{
    for(int duty=0;duty<=PWM_MAX_DUTY;duty++)
    {
        ledcWrite(PWM_CHANNEL,duty);
        delay(10);
    }

    for(int duty=PWM_MAX_DUTY;duty>=0;duty--)
    {
        ledcWrite(PWM_CHANNEL,duty);
        delay(10);
    }
}
