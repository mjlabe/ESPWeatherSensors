#ifdef ESP32
    #include <WiFi.h>
#else
    #include <Arduino.h>
    #include <ESP8266WiFi.h>
    #include <Hash.h>
#endif

#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <Env.h>

// Data wire is connected to GPIO 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// Variables to store temperature values
String temperatureF = "";
String temperatureC = "";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Replace with your network credentials
const char *ssid = "REPLACE_WITH_YOUR_SSID";
const char *password = "REPLACE_WITH_YOUR_PASSWORD";

String readDSTemperatureC() {
    // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);

    if (tempC == -127.00) {
        Serial.println("Failed to read from DS18B20 sensor");
        return "--";
    } else {
        Serial.print("Temperature Celsius: ");
        Serial.println(tempC);
    }
    return String(tempC);
}

String readDSTemperatureF() {
    // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
    sensors.requestTemperatures();
    float tempF = sensors.getTempFByIndex(0);

    if (int(tempF) == -196) {
        Serial.println("Failed to read from DS18B20 sensor");
        return "--";
    } else {
        Serial.print("Temperature Fahrenheit: ");
        Serial.println(tempF);
    }
    return String(tempF);
}

void connectToWifi(){
    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    // Print ESP Local IP Address
    Serial.println(WiFi.localIP());
}

void setup() {
    // Serial port for debugging purposes
    Serial.begin(115200);
    Serial.println();

    // Start up the DS18B20 library
    sensors.begin();

    temperatureC = readDSTemperatureC();
    temperatureF = readDSTemperatureF();

    // Connect to Wi-Fi
    connectToWifi()
}

void loop() {
    // TODO: sleep for 10 min then
    // connectToWifi()
    if ((millis() - lastTime) > timerDelay) {
        WiFiClient client;
        HTTPClient http;

        http.begin(client, SERVER_URI + SERVER_ROUTE);

        temperatureC = readDSTemperatureC();
        temperatureF = readDSTemperatureF();
        lastTime = millis();

        // POST Data
        String httpRequestData = "{\"ds18B20\": {\"temp_c\":\"" + temperatureC + "\",\"temp_f\":\"" + temperatureF + "\"}}";
        int httpResponseCode = http.POST(httpRequestData);
        Serial.println(String(httpResponseCode));
    }
}
