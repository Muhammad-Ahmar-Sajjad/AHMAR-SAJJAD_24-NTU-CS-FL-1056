

//Muhammad Ahmar Sajjad  //24-NTU-CS-FL-1056

#include <Arduino.h>
const int buttonPin = 36;                       // the number of the pushbutton pin
const int ledPin =  2;   
const int led2Pin =  5;                      // the number of the LED pin
int buttonState = 0;
                           // variable for reading the pushbutton status
void setup() {
    pinMode(ledPin, OUTPUT);  
    pinMode(led2Pin, OUTPUT);                 // initialize the LED pin as an output:
    pinMode(buttonPin, INPUT_PULLUP);          // initialize the pushbutton pin as an input:
}                                               
void loop() {
   buttonState = digitalRead(buttonPin);       // read the state of the pushbutton value:
   if (buttonState == HIGH) {                  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
       digitalWrite(ledPin, HIGH); 
       digitalWrite(led2Pin, LOW);            // turn LED on:
   } else {
       digitalWrite(ledPin, LOW);
       digitalWrite(led2Pin, HIGH);              // turn LED off:
   }
}