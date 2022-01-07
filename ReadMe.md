# ESP Weather Station

This project captures sensor data and posts it to a remote endpoint using an ESP8266 or ESP32 and the following the
sensors:

- [x] DS18B20 (water temperature)
- [ ] AM2320 (air temperature and humidity)

## Setup

Create `Env.h` file at project root containing:

- SERVER_URI (base URL for endpoint, i.e. `"https://www.example.com"`)
- SERVER_ROUTE (route of endpoint (i.e. `"/weather"`))

## Schema

```json
{
  "ds18B20": {
    "temp_c": "temperatureC",
    "temp_f": "temperatureF"
  }
}
```
