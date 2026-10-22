# Embedded IoT Systems — Homework 2
## Dual-LED PWM Control with OLED Monitoring

**Student:** M. Ahmar Sajjad  
**Registration No.:** 24-NTU-CS-FL-1056  
**Course:** Embedded IoT Systems  
**Platform:** ESP32 DevKit | PlatformIO | Wokwi

---

## 1. Project Overview

In this homework, I used an ESP32 to control two LEDs using Pulse Width Modulation (PWM). Both LEDs gradually fade in opposite directions at different PWM frequencies.

I also added an SSD1306 OLED display to monitor the live duty-cycle percentages and configured frequencies of both LEDs.

The complete project was tested in Wokwi and on physical ESP32 hardware.

## 2. Components Used

- ESP32 DevKit
- Red LED and Blue LED
- Two 220Ω resistors
- SSD1306 OLED Display (128×64, I²C)
- Breadboard
- Jumper wires
- USB cable

## 3. Circuit Connections

The components were connected as follows:

- **Red LED:** GPIO 18
- **Blue LED:** GPIO 19
- **LED Resistors:** 220Ω each, connected in series
- **OLED SDA:** GPIO 21
- **OLED SCL:** GPIO 22
- **OLED VCC:** 3V3
- **OLED GND:** GND

Each LED has its own current-limiting resistor, and both LED cathodes are connected to GND.

## 4. Task 1 — Dual-LED PWM Fading

In Task 1, I configured two independent PWM outputs using the ESP32 LEDC peripheral.

**LED 1 (Red):**
- GPIO: 18
- PWM Frequency: 1000 Hz
- Resolution: 8-bit
- Duty-Cycle Range: 0–255
- Initial Duty: 0

**LED 2 (Blue):**
- GPIO: 19
- PWM Frequency: 5000 Hz
- Resolution: 8-bit
- Duty-Cycle Range: 0–255
- Initial Duty: 255

### Working Principle

Both LEDs fade in opposite directions. The red LED starts from minimum brightness while the blue LED starts from maximum brightness.

The duty-cycle values change by 5 every 20 milliseconds. When an LED reaches its minimum or maximum value, its fading direction reverses.

**Duty Cycle (%) = (PWM Value / 255) × 100**

For example, a PWM value of 128 produces approximately 50.2% duty cycle.

**Result:** Both LEDs successfully faded in opposite directions in Wokwi and on physical hardware.

## 5. Task 2 — OLED Monitoring

After completing Task 1, I connected an SSD1306 OLED display to the same project using I²C communication.

The OLED continuously displays:

- LED 1 live duty-cycle percentage
- LED 1 PWM frequency (1000 Hz)
- LED 2 live duty-cycle percentage
- LED 2 PWM frequency (5000 Hz)

### Example OLED Output

```text
PWM MONITOR
----------------
LED1: 25%
F: 1000 Hz

LED2: 75%
F: 5000 Hz
```

The duty-cycle percentages update continuously as the LEDs fade, while their configured PWM frequencies remain constant.

**Result:** The OLED successfully displayed the live PWM values without affecting the LED fading process.

## 6. Testing and Results

I tested both tasks in Wokwi simulation and on my physical ESP32 kit.

The following features worked successfully in both environments:

- Independent PWM control of two LEDs
- Smooth fading in opposite directions
- Different PWM frequencies (1000 Hz and 5000 Hz)
- Live duty-cycle monitoring on OLED
- Correct frequency display
- Continuous operation of both LEDs and OLED

The physical circuit produced the expected results, similar to the Wokwi simulation.

### Wokwi Simulation Link

https://wokwi.com/projects/478574157477086209

## 7. Project Files

The project contains:

- **src/main.cpp** — PWM fading and OLED monitoring code
- **platformio.ini** — ESP32 configuration and library dependencies
- **diagram.json** — Wokwi circuit connections
- **wokwi.toml** — Wokwi simulation configuration
- **screenshots/** — Wokwi and hardware evidence
- **README.md** — Project documentation

## 8. Tools and Libraries

**Development Tools:**
- Visual Studio Code
- PlatformIO
- Wokwi Simulator
- Git and GitHub

**Libraries:**
- Arduino.h
- Wire.h
- Adafruit GFX Library
- Adafruit SSD1306

## 9. GitHub Submission

Both tasks were completed within the same project and uploaded to my existing course repository.

**GitHub Repository:**

https://github.com/Muhammad-Ahmar-Sajjad/AHMAR-SAJJAD_24-NTU-CS-FL-1056

**Git Commit Messages:**

1. `task1 completed` — Dual-LED PWM fading
2. `complete homework` — OLED monitoring and final implementation

## 10. Conclusion

This homework helped me understand PWM-based LED brightness control using the ESP32 LEDC peripheral and real-time monitoring through an I²C OLED display.

Both LEDs successfully faded at different PWM frequencies, while the OLED displayed their changing duty-cycle percentages.

The project was successfully implemented and tested in both Wokwi and on physical ESP32 hardware.