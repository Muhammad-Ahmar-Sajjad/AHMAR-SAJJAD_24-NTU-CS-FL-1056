// Week3-Lecture2
// Timer Interrupt (Internal)
// Embedded IoT System Fall-2026

//Muhammad Ahmar Sajjad     //24-NTU-CS-FL-1056


#include <Arduino.h>

#define LED 2

hw_timer_t *My_timer = NULL;

void ARDUINO_ISR_ATTR onTimer() {           // ARDUINO_ISR_ATTR == IRAM_ATTR
  digitalWrite(LED, !digitalRead(LED));     // safe in ISR on ESP32
}

void setup() {
  pinMode(LED, OUTPUT);

  // 1 MHz timer tick (1 tick = 1 µs)
  My_timer=timerBegin(0,80,true);
timerAttachInterrupt(My_timer,&onTimer,true);
timerAlarmWrite(My_timer,1000000,true);
timerAlarmEnable(My_timer);
}
void loop() {
  // nothing needed, all handled by interrupts
}