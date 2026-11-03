#include <Arduino.h>

#define DAC_PIN 25   // DAC1
#define PWM_PIN 26   // PWM (any output pin works)
#define PWM_CH  0

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("DAC (GPIO25) vs PWM (GPIO26)");

    ledcSetup(PWM_CH, 5000, 8);
    ledcAttachPin(PWM_PIN, PWM_CH);
}

void loop()
{
    for (int v = 0; v <= 255; v++)
    {
        dacWrite(DAC_PIN, v);   // true analog voltage
        ledcWrite(PWM_CH, v);   // PWM duty cycle
        delay(20);
    }
    for (int v = 255; v >= 0; v--)
    {
        dacWrite(DAC_PIN, v);
        ledcWrite(PWM_CH, v);
        delay(20);
    }
}