// Week3-Lecture2
// Timer Interrupt + Button Debounce
// Embedded IoT System Fall-2026

//Muhammad Ahmar Sajjad     //24-NTU-CS-FL-1056

#include <Arduino.h>

#define LED 4
#define BUTTON_PIN 32

hw_timer_t *My_timer=NULL;
hw_timer_t *debounceTimer=NULL;

volatile bool debounceActive=false;
volatile bool ledState=false;

void ARDUINO_ISR_ATTR onTimer()
{
    ledState=!ledState;
    digitalWrite(LED,ledState);
}

void ARDUINO_ISR_ATTR onDebounceTimer()
{
    debounceActive=false;
}

void ARDUINO_ISR_ATTR onButtonISR()
{
    if(!debounceActive)
    {
        debounceActive=true;
        ledState=!ledState;
        digitalWrite(LED,ledState);
        timerWrite(debounceTimer,0);
    }
}

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    My_timer = timerBegin(0, 80, true);
    timerAttachInterrupt(My_timer, &onTimer, true);
    timerAlarmWrite(My_timer, 1000000, true);
    timerAlarmEnable(My_timer);

    debounceTimer = timerBegin(1, 80, true);
    timerAttachInterrupt(debounceTimer, &onDebounceTimer, true);
    timerAlarmWrite(debounceTimer, 50000, false);
    timerAlarmEnable(debounceTimer);

    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonISR, FALLING);
}

void loop()
{
}
