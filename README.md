# Smart Environmental Monitoring System

An ESP32-based embedded and IoT system for real-time monitoring of temperature,
humidity, relative air-quality sensor level, and light intensity.

## Features

- Real-time temperature and humidity acquisition using DHT22
- Analog air-quality sensor acquisition using MQ-135
- Analog light-level acquisition using an LDR voltage divider
- Local OLED display using I2C
- ESP32 Wi-Fi connectivity
- ThingSpeak cloud monitoring
- Periodic sensor sampling without blocking `delay()` in the main loop
- Serial monitoring for debugging

## Hardware

- ESP32 development board
- DHT22
- MQ-135 module
- LDR
- 10 kΩ resistor for LDR voltage divider
- 0.96-inch SSD1306 OLED
- Breadboard and jumper wires
- USB cable

## Pin Mapping

| Component | ESP32 |
|---|---|
| DHT22 DATA | GPIO 4 |
| MQ-135 AO | GPIO 34 |
| LDR divider output | GPIO 35 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |
| DHT22 VCC | 3.3V |
| OLED VCC | 3.3V |
| Common GND | GND |

### MQ-135 safety note

Do not connect a potentially 5 V MQ-135 analog output directly to an ESP32 ADC
input. Use a suitable voltage divider/level-shifting circuit so the ESP32 ADC
input remains within its allowed voltage range.

## Software

- Arduino IDE
- ESP32 board package
- DHT sensor library
- Adafruit GFX Library
- Adafruit SSD1306 library
- ThingSpeak channel

## How to Run

1. Install the required Arduino libraries.
2. Open `src/smart_environmental_monitor.ino`.
3. Select the correct ESP32 board and COM port.
4. Enter your Wi-Fi credentials and ThingSpeak Write API Key.
5. Upload the program.
6. Open Serial Monitor at 115200 baud.
7. Observe sensor readings on the OLED.
8. Open the ThingSpeak channel to view cloud graphs.

## Repository Structure

```text
Smart_Environmental_Monitoring_System/
├── src/
│   └── smart_environmental_monitor.ino
├── include/
│   └── pin_configuration.txt
├── docs/
│   ├── block_diagram.txt
│   └── project_notes.md
├── config/
│   └── thingSpeak_setup.md
└── README.md
```

## Project Architecture

```text
DHT22 ───────┐
MQ-135 ──────┼──> ESP32 ──> OLED
LDR ─────────┘       |
                     |
                    Wi-Fi
                     |
                     v
                ThingSpeak
                     |
                     v
               IoT Dashboard
```

## Resume Description

**Smart Environmental Monitoring System | Arduino, ESP32, Sensors, IoT, Embedded C**

Developed an ESP32-based environmental monitoring system to acquire
temperature, humidity, air-quality sensor levels, and light intensity in
real time. Integrated DHT22, MQ-135, LDR, and I2C OLED peripherals and
implemented Wi-Fi-based data transmission to a ThingSpeak IoT dashboard.

## Future Improvements

- Add threshold-based alerts
- Add MQTT support
- Add rechargeable battery operation
- Add data logging to an SD card
- Calibrate the MQ-135 for a defined measurement application
- Add a web/mobile dashboard
