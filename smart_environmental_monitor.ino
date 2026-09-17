/*
  Smart Environmental Monitoring System
  Hardware: ESP32 + DHT22 + MQ-135 + LDR + SSD1306 OLED
  IoT: ThingSpeak

  Libraries:
  - DHT sensor library
  - Adafruit GFX Library
  - Adafruit SSD1306

  Before uploading:
  1. Select your ESP32 board in Arduino IDE.
  2. Enter Wi-Fi SSID/password.
  3. Enter ThingSpeak Channel ID and Write API Key.
  4. Ensure MQ-135 analog output is voltage-divided to <= 3.3 V before GPIO34.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHT_PIN       4
#define DHT_TYPE      DHT22
#define MQ135_PIN     34
#define LDR_PIN       35

#define OLED_WIDTH    128
#define OLED_HEIGHT   64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

// ---------- USER CONFIGURATION ----------
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

const unsigned long THINGSPEAK_CHANNEL_ID = 1234567;
const char* THINGSPEAK_WRITE_API_KEY = "YOUR_WRITE_API_KEY";
// ----------------------------------------

const unsigned long SENSOR_INTERVAL_MS = 2000;
const unsigned long CLOUD_INTERVAL_MS = 15000;

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

unsigned long lastSensorRead = 0;
unsigned long lastCloudUpload = 0;

float temperature = 0.0;
float humidity = 0.0;
int airQuality = 0;
int lightLevel = 0;

void connectWiFi()
{
  Serial.print("Connecting to Wi-Fi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 15000)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Wi-Fi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("Wi-Fi connection failed");
  }
}

void readSensors()
{
  float newTemperature = dht.readTemperature();
  float newHumidity = dht.readHumidity();

  if (!isnan(newTemperature))
    temperature = newTemperature;

  if (!isnan(newHumidity))
    humidity = newHumidity;

  airQuality = analogRead(MQ135_PIN);
  lightLevel = analogRead(LDR_PIN);
}

void updateOLED()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("ENVIRONMENT MONITOR");

  display.setCursor(0, 14);
  display.print("Temp: ");
  display.print(temperature, 1);
  display.println(" C");

  display.setCursor(0, 26);
  display.print("Hum : ");
  display.print(humidity, 1);
  display.println(" %");

  display.setCursor(0, 38);
  display.print("Air : ");
  display.println(airQuality);

  display.setCursor(0, 50);
  display.print("Light: ");
  display.println(lightLevel);

  display.display();
}

void uploadToThingSpeak()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    connectWiFi();
    return;
  }

  HTTPClient http;

  String url = "http://api.thingspeak.com/update?api_key=";
  url += THINGSPEAK_WRITE_API_KEY;
  url += "&field1=";
  url += String(temperature, 2);
  url += "&field2=";
  url += String(humidity, 2);
  url += "&field3=";
  url += String(airQuality);
  url += "&field4=";
  url += String(lightLevel);

  http.begin(url);

  int responseCode = http.GET();

  Serial.print("ThingSpeak response: ");
  Serial.println(responseCode);

  http.end();
}

void setup()
{
  Serial.begin(115200);

  dht.begin();

  analogReadResolution(12);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
  {
    Serial.println("OLED initialization failed");
  }
  else
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println("System Starting...");
    display.display();
  }

  connectWiFi();
}

void loop()
{
  unsigned long currentTime = millis();

  if (currentTime - lastSensorRead >= SENSOR_INTERVAL_MS)
  {
    lastSensorRead = currentTime;

    readSensors();
    updateOLED();

    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity, 1);
    Serial.println(" %");

    Serial.print("Air Quality ADC: ");
    Serial.println(airQuality);

    Serial.print("Light Level ADC: ");
    Serial.println(lightLevel);

    Serial.println("-------------------------");
  }

  if (currentTime - lastCloudUpload >= CLOUD_INTERVAL_MS)
  {
    lastCloudUpload = currentTime;
    uploadToThingSpeak();
  }
}
