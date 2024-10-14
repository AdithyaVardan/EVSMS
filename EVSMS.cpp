//VERSION-1.3.0
#include "TemperatureSensors.h"
#include "ADCReadings.h"
#include "SpeedAndRPM.h"

void setup() {
    Serial.begin(9600);
    
    // Initialize all modules
    initTemperatureSensors();
    initSpeedAndRPM();
}

void loop() {
    // Print temperature readings
    printTemperatureReadings();

    // Print ADC sensor readings
    printADCReadings();

    // Print speed and RPM readings
    printSpeedAndRPM();

    delay(1000);  // Wait for a second before the next loop
}
