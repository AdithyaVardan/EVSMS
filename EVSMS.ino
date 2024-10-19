//VERSION-1.4.1
#include "TemperatureSensors.h"
#include "ADCReadings.h"
#include "SpeedAndRPM.h"
#include "CSVLogger.h"

void setup() {
    Serial.begin(9600);
    // Initialize all modules
    initADCReadings();
    initTemperatureSensors();
    initSpeedAndRPM();
    initCSVLogger();
}

void loop() {
    printTemperatureReadings();// Print temperature readings
    printADCReadings();// Print ADC sensor readings
    printSpeedAndRPM();// Print speed and RPM readings
    logDataToCSV();// Log data to CSV file
    delay(1000);  // Wait for a second before the next loop
}
