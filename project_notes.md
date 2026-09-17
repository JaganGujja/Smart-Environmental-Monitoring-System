# Project Notes

## Objective
Build an ESP32-based embedded system that acquires environmental parameters,
displays them locally, and uploads the readings to an IoT dashboard.

## Parameters
- Temperature: DHT22
- Humidity: DHT22
- Air-quality sensor reading: MQ-135 analog output
- Light level: LDR voltage-divider analog reading

## Embedded Concepts
- GPIO
- ADC
- I2C
- Sensor interfacing
- Periodic sampling using `millis()`
- Wi-Fi connectivity
- HTTP-based cloud upload

## Important measurement note
The MQ-135 value in this starter project is an ADC reading, not a calibrated
ppm concentration. A calibrated gas-concentration measurement requires
sensor-specific calibration and environmental compensation.

## Suggested validation
1. Verify DHT22 values against a known thermometer/hygrometer if available.
2. Check LDR ADC response under different light conditions.
3. Observe MQ-135 ADC changes only as a relative sensor indication unless calibrated.
4. Verify OLED values match Serial Monitor.
5. Verify ThingSpeak fields receive the same values.

## ThingSpeak fields
Field 1: Temperature
Field 2: Humidity
Field 3: Air Quality ADC
Field 4: Light Level ADC
