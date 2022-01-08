#ifdef ESP32
    #include <WiFi.h>
#else
    #include <Arduino.h>
    #include <ESP8266WiFi.h>
    #include <Hash.h>
#endif

#include <Env.h>


void connectToWifi(){
    // Connect to Wi-Fi
    WiFi.begin(SSID, PASSWORD);
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    // Print ESP Local IP Address
    Serial.println(WiFi.localIP());

    WiFiClient client;
    HTTPClient http;

    http.begin(client, SERVER_URI + SERVER_ROUTE);
}

void disconnectWiFi() {
    WiFi.disconnect()
}

