#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#define MQ135_PIN 34   // Analog pin for gas sensor
#define DHTPIN 35      // Analog pin for DHT22
#include "DHT.h"
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "ESP32-AP";
const char* password = "12345678";

AsyncWebServer server(80);

float readAirQuality() {
  int raw = analogRead(MQ135_PIN);
  float airQuality = map(raw, 0, 4095, 0, 500); // Rough AQI estimation
  return airQuality;
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", webpage);
  });

  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    float air = readAirQuality();
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    StaticJsonDocument<200> doc;
    doc["airQuality"] = air;
    doc["temperature"] = temp;
    doc["humidity"] = hum;

    String json;
    serializeJson(doc, json);
    request->send(200, "application/json", json);
  });

  server.begin();
}

void loop() {
  // async server handles everything
}

const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Air Quality Monitor</title>
<style>
body { font-family: Arial; text-align: center; background-color: #111; color: #0ff; }
h1 { margin-bottom: 20px; }
div.data { font-size: 24px; margin: 15px; }
</style>
</head>
<body>
<h1>Air Quality Dashboard</h1>
<div class="data">Air Quality Index: <span id="aqi">0</span></div>
<div class="data">Temperature: <span id="temp">0</span> °C</div>
<div class="data">Humidity: <span id="hum">0</span> %</div>

<script>
function fe
