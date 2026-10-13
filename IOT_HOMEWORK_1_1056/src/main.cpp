
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_SDA 21
#define OLED_SCL 22
#define BUTTON_PIN 18
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,OLED_RESET);

unsigned long lastDebounceTime=0;
const unsigned long debounceInterval=50;

int lastButtonReading=HIGH;
int stableButtonState=HIGH;

unsigned long pressCount=0;
bool displayNeedsUpdate=true;

void updateDisplay()
{
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(1);
    display.setCursor(15,0);
    display.println("56-68_ESP32 STATUS");

    display.drawLine(0,12,127,12,SSD1306_WHITE);

    display.setCursor(0,20);
    display.print("Button: ");
    if(stableButtonState==LOW)
    {
        display.println("PRESSED");
    }
    else
    {
        display.println("RELEASED");
    }

    display.setCursor(0,38);
    display.print("Press Count: ");
    display.println(pressCount);

    display.setCursor(0,54);
    display.println("Debounce: 50ms");

    display.display();
}

void setup()
{
    Serial.begin(115200);

    pinMode(BUTTON_PIN,INPUT_PULLUP);
    Wire.begin(OLED_SDA,OLED_SCL);

    if(!display.begin(SSD1306_SWITCHCAPVCC,OLED_ADDRESS))
    {
        Serial.println("OLED initialization failed!");
        while(true)
        {
            yield();
        }
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("ESP32 OLED Project");
    display.println("Initializing...");
    display.display();

    Serial.println("ESP32 OLED Status Display");
    Serial.println("Press counter initialized to 0");

    updateDisplay();
}

void loop()
{
    int buttonReading=digitalRead(BUTTON_PIN);

    // Restart the debounce timer whenever the raw input changes.
    if(buttonReading!=lastButtonReading)
    {
        lastDebounceTime=millis();
        lastButtonReading=buttonReading;
    }

    // Accept a new button state only after it remains stable for 50 ms.
    if(millis()-lastDebounceTime>=debounceInterval)
    {
        if(buttonReading!=stableButtonState)
        {
            stableButtonState=buttonReading;
            displayNeedsUpdate=true;

            // Count only the transition to the pressed state.
            if(stableButtonState==LOW)
            {
                pressCount++;
                Serial.print("Accepted press count: ");
                Serial.println(pressCount);
            }
        }
    }

    // Refresh the OLED only when the accepted state changes.
    if(displayNeedsUpdate)
    {
        updateDisplay();
        displayNeedsUpdate=false;
    }
}
