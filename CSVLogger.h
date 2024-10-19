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

    // Create or open the CSV file and write the header row with value names
    File dataFile = SD.open("evsms_data.csv", FILE_WRITE);
    if (dataFile) {
        // Write the header row with descriptive value names
        dataFile.println("Front Inverter Voltage (V), Front Inverter Current (A), Front Inverter Power (kW), "
                         "Rear Inverter Voltage (V), Rear Inverter Current (A), Rear Inverter Power (kW), "
                         "Motor Inverter Voltage (V), Motor Inverter Current (A), Motor Inverter Power (kW), "
                         "Front Stator Temperature (°C), Rear Stator Temperature (°C), Transmission Temperature (°C), "
                         "Battery Inlet Temperature (°C), Battery Temperature (°C), Speed (m/s), RPM");
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
        dataFile.print(frontinv);     // Front inverter voltage
        dataFile.print(",");
        dataFile.print(frontinc);     // Front inverter current
        dataFile.print(",");
        dataFile.print(frontPower);   // Front inverter power
        dataFile.print(",");
        dataFile.print(rearinv);      // Rear inverter voltage
        dataFile.print(",");
        dataFile.print(rearinc);      // Rear inverter current
        dataFile.print(",");
        dataFile.print(rearPower);    // Rear inverter power
        dataFile.print(",");
        dataFile.print(motorinv);     // Motor inverter voltage
        dataFile.print(",");
        dataFile.print(motorinc);     // Motor inverter current
        dataFile.print(",");
        dataFile.print(motorPower);   // Motor inverter power
        dataFile.print(",");

        // Log temperature values (front stator, rear stator, transmission, battery inlet, battery temp)
        for (int i = 0; i < 5; i++) {
            dataFile.print(temps[i]);
            if (i < 4) dataFile.print(",");
        }

        // Log speed and RPM
        dataFile.print(",");
        dataFile.print(speed);        // Vehicle speed
        dataFile.print(",");
        dataFile.println(rpm);        // RPM value

        dataFile.close();  // Close the file after writing
    } else {
        Serial.println("Error opening evsms_data.csv file");
    }
}

#endif
