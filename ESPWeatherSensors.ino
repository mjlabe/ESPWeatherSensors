#include <HTTPClient.h>
#include <Sensors.h>
#include <WiFiManagement.h>
#include <Resources.h>
#include <Env.h>


// Timer variables
unsigned long sleepTime = 3e6;

void setup() {
    delay(1000)

    // Serial port for debugging purposes
    Serial.begin(115200);
    Serial.println();
}

void loop() {
    connectToWifi()
    enableSensors()

    if DEBUG == true {
        String temperatureC = "readDSTemperatureC()";
        String temperatureF = "readDSTemperatureF()";
    }
    else {
        String temperatureC = readDSTemperatureC();
        String temperatureF = readDSTemperatureF();
    }

    // POST Data
    String httpRequestData = "{\"ds18B20\": {\"temp_c\":\"" + temperatureC + "\",\"temp_f\":\"" + temperatureF + "\"}}";
    int httpResponseCode = http.POST(httpRequestData);
    Serial.println(String(httpResponseCode));

    disconnectWiFi()
    sleep(sleepTime);
}
