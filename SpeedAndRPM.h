#ifndef SPEED_AND_RPM_H
#define SPEED_AND_RPM_H

#include <Wire.h>
#include <MPU6050.h>

MPU6050 accelgyro;

// Define the pin for the IR sensor and RPM variables
#define IR_SENSOR_PIN 3
volatile int pulseCount = 0;
unsigned long previousMillis = 0;
const unsigned long interval = 1000;
float accelX;
float velocity = 0;
unsigned long lastTime;
float timeStep;

void IR_interrupt() {
    pulseCount++;
}

void initSpeedAndRPM() {
    // Initialize IR sensor
    pinMode(IR_SENSOR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN), IR_interrupt, FALLING);

    // Initialize MPU6050 accelerometer
    Wire.begin();
    accelgyro.initialize();

    // Check connection
    if (!accelgyro.testConnection()) {
        Serial.println("MPU6050 connection failed");
        while (1);
    }

    lastTime = millis();
}

void printSpeedAndRPM() {
    // Calculate RPM
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        int rpm = pulseCount * 60;
        pulseCount = 0;
        Serial.print(" | RPM: ");
        Serial.println(rpm);
    }

    // Calculate speed from accelerometer
    accelX = accelgyro.getAccelerationX() / 16384.0;
    unsigned long currentTime = millis();
    timeStep = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;
    velocity += accelX * 9.81 * timeStep;

    Serial.print(" | Speed (m/s): ");
    Serial.println(velocity);
}

#endif
