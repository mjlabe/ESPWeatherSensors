#include <OneWire.h>
#include <DallasTemperature.h>


// Data wire is connected to GPIO 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

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

void enableSensors() {
    sensors.begin();
}