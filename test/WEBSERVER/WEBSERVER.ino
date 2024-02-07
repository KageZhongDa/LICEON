#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

const char *ssid = "mihkuno";
const char *password = "helloworld";

// Create an instance of the server
AsyncWebServer server(80);

void setup() {
  // Start Serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());


  
  // Define a route for the API
  server.on("/api/data", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Create a JSON object
    DynamicJsonDocument jsonDoc(1024);
    
    // Add data to the JSON object
    jsonDoc["sensor"] = "ESP32";
    jsonDoc["value"] = analogRead(A0);

    // Serialize the JSON object to a string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    // Send the JSON response
    request->send(200, "application/json", jsonString);
  });

  // Start server
  server.begin();
}

void loop() {
  // Your code here
}
