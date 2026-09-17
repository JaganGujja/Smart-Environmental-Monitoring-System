# ThingSpeak Setup

1. Create a ThingSpeak channel.
2. Add four fields:
   - Field 1: Temperature
   - Field 2: Humidity
   - Field 3: Air Quality ADC
   - Field 4: Light Level ADC
3. Copy the channel Write API Key.
4. Open `src/smart_environmental_monitor.ino`.
5. Replace:
   - `YOUR_WIFI_SSID`
   - `YOUR_WIFI_PASSWORD`
   - `1234567`
   - `YOUR_WRITE_API_KEY`
6. Upload the sketch to the ESP32.
7. Open Serial Monitor at 115200 baud.
8. Confirm the upload response and check the channel charts.

Never commit real Wi-Fi passwords or private API keys to GitHub.
Use placeholders in the repository.
