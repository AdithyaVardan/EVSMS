#ifndef TEMPERATURE_SENSORS_H
#define TEMPERATURE_SENSORS_H

#include <OneWire.h>
#include <DallasTemperature.h>

// Define the digital pin for the DS18B20 sensors
#define ONE_WIRE_BUS 2

// Create a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void initTemperatureSensors() {
    sensors.begin();
}

void printTemperatureReadings() {
    // Request temperature readings from the DS18B20 sensors
    sensors.requestTemperatures();

    float temp[5] = {sensors.getTempCByIndex(0),
                    sensors.getTempCByIndex(1),
                    sensors.getTempCByIndex(2),
                    sensors.getTempCByIndex(3),
                    sensors.getTempCByIndex(4)};
    
    String sensor_names[5] = {"FRONT STATOR",
                              "REAR STATOR",
                              "TRANSMISSION",
                              "BATTERY INLET",
                              "BATTERY TEMP"};

    for (int i = 0; i <= 4; i++) {
        Serial.print(sensor_names[i] + ":-");
        Serial.println((temp[i] == DEVICE_DISCONNECTED_C) ? "Error" : String(temp[i], 2) + "°C");
    }
}

#endif
