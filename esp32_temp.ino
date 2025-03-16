#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFiClientSecure.h>

// network credentials
const char* ssid = "";
const char* password = "";
const char* serverName = "";

// dallas temperature sensor pin
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();

  // static dns config
  IPAddress primaryDNS(1, 1, 1, 1);    // cloudflare dns
  IPAddress secondaryDNS(8, 8, 8, 8);  // google dns
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, primaryDNS, secondaryDNS);

  // connecting to wireless network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // get temp from sensor
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  String tempString = (temperatureC != DEVICE_DISCONNECTED_C) ? String(temperatureC) : "error";
  
  // check connectivity to wifi
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    IPAddress serverIP;

    // resolve ip address
    if (WiFi.hostByName(servername, serverIP)) {
      String serverPath = "https://" + serverIP.toString() + "/?temperature=" + tempString;
      Serial.println("Request URL: " + serverPath);
      
	  // send http request
      if (https.begin(client, serverPath)) {
        int httpResponseCode = https.GET();
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        if (httpResponseCode > 0) {
          String response = https.getString();
          Serial.println("Response: " + response);
        } else {
          Serial.print("Error: ");
          Serial.println(https.errorToString(httpResponseCode).c_str());
        }

        https.end();
      } else {
        Serial.println("HTTPS connection failed.");
      }
    } else {
      Serial.println("DNS resolution failed.");
    }
  }

  delay(10000);
}
