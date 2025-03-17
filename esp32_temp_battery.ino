#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFiClientSecure.h>
#include <esp_sleep.h>

// network credentials
const char* ssid = "";
const char* password = "";
const char* serverName = "";

// dallas temperature sensor pin
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// duration for deep sleep
#define SLEEP_TIME 60e6  // 60 seconds

void setup() {
  Serial.begin(115200);
  sensors.begin();

  // connecting to wireless network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // get temperature from sensor
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  String tempString = (temperatureC != DEVICE_DISCONNECTED_C) ? String(temperatureC) : "error";
  
  // check connectivity to wifi
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    IPAddress serverIP;

    // resolve IP address
    if (WiFi.hostByName(serverName, serverIP)) {
      String serverPath = "https://" + serverIP.toString() + "/?temperature=" + tempString;
      Serial.println("Request URL: " + serverPath);

      // send HTTP request
      if (https.begin(client, serverPath)) {
        int httpResponseCode = https.GET();
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        https.end();
      } else {
        Serial.println("HTTPS connection failed.");
      }
    } else {
      Serial.println("DNS resolution failed.");
    }
  }

  Serial.println("Entering deep sleep...");
  esp_sleep_enable_timer_wakeup(SLEEP_TIME);
  esp_deep_sleep_start();
}

void loop() {}
