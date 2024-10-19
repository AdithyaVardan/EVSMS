#ifndef CSV_LOGGER_H
#define CSV_LOGGER_H

#include <SD.h>
#include "ADCReadings.h"
#include "SpeedAndRPM.h"
#include "TemperatureSensors.h"

// SD Card Chip Select Pin
const int chipSelect = 10;

void initCSVLogger() {
    // Initialize SD card
    if (!SD.begin(chipSelect)) {
        Serial.println("SD Card initialization failed!");
        while (true);  // Stop the program if SD card initialization fails
    }
    Serial.println("SD Card initialized.");

    // Create or open the CSV file and write the header row
    File dataFile = SD.open("evsms_data.csv", FILE_WRITE);
    if (dataFile) {
        dataFile.println("FrontInvV, FrontInvC, FrontInvPower, RearInvV, RearInvC, RearInvPower, MotorInvV, MotorInvC, MotorInvPower, FrontStatorTemp, RearStatorTemp, TransmissionTemp, BatteryInletTemp, BatteryTemp, Speed, RPM");
        dataFile.close();
    } else {
        Serial.println("Error opening evsms_data.csv file");
    }
}

void logDataToCSV() {
    // Collect all sensor data
    float frontinv = getFrontInvVoltage();    // Front inverter voltage from ADCReadings
    float frontinc = getFrontInvCurrent();    // Front inverter current from ADCReadings
    float rearinv = getRearInvVoltage();      // Rear inverter voltage from ADCReadings
    float rearinc = getRearInvCurrent();      // Rear inverter current from ADCReadings
    float motorinv = getMotorInvVoltage();    // Motor inverter voltage from ADCReadings
    float motorinc = getMotorInvCurrent();    // Motor inverter current from ADCReadings

    // Calculate power for each inverter
    float frontPower = frontinv * frontinc;
    float rearPower = rearinv * rearinc;
    float motorPower = motorinv * motorinc;

    // Get temperature readings
    float temps[5];
    getTemperatureReadings(temps);  // Temperature from TemperatureSensors

    // Get speed and RPM
    float speed = getSpeed();  // Speed from SpeedAndRPM
    int rpm = getRPM();        // RPM from SpeedAndRPM

    // Open the file on the SD card and append the data
    File dataFile = SD.open("evsms_data.csv", FILE_WRITE);
    if (dataFile) {
        // Write the sensor data in CSV format
        dataFile.print(frontinv);
        dataFile.print(",");
        dataFile.print(frontinc);
        dataFile.print(",");
        dataFile.print(frontPower);
        dataFile.print(",");
        dataFile.print(rearinv);
        dataFile.print(",");
        dataFile.print(rearinc);
        dataFile.print(",");
        dataFile.print(rearPower);
        dataFile.print(",");
        dataFile.print(motorinv);
        dataFile.print(",");
        dataFile.print(motorinc);
        dataFile.print(",");
        dataFile.print(motorPower);
        dataFile.print(",");
        
        // Log temperature values (front stator, rear stator, transmission, battery inlet, battery temp)
        for (int i = 0; i < 5; i++) {
            dataFile.print(temps[i]);
            if (i < 4) dataFile.print(",");
        }
        
        // Log speed and RPM
        dataFile.print(",");
        dataFile.print(speed);
        dataFile.print(",");
        dataFile.println(rpm);

        dataFile.close();  // Close the file after writing
    } else {
        Serial.println("Error opening evsms_data.csv file");
    }
}

#endif
