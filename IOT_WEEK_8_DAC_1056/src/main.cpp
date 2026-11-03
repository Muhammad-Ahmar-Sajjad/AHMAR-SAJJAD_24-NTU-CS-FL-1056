#include <Arduino.h> 
  
#define DAC_PIN 25 
  
void setup() 
{ 
    Serial.begin(115200); 
    Serial.println("DAC LED Fade Test"); 
} 
  
void loop() 
{ 
    // Increase DAC output 
    for (int value = 0; value <= 255; value++) 
    { 
        dacWrite(DAC_PIN, value); 
        delay(20); 
    } 
  
    // Decrease DAC output 
    for (int value = 255; value >= 0; value--) 
    { 
        dacWrite(DAC_PIN, value); 
        delay(20); 
    } 
} 