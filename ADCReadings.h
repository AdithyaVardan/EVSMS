#ifndef ADC_READINGS_H
#define ADC_READINGS_H

// Define the ADC pins for the voltage and current sensors
int sensor1Pin = A0;
int sensor2Pin = A1;
int sensor3Pin = A2;
int sensor4Pin = A3;
int sensor5Pin = A4;
int sensor6Pin = A5;

void printADCReadings() {
    // Read raw ADC values (0 to 1023 for 0-5V input)
    int adcValue1 = analogRead(sensor1Pin);
    int adcValue2 = analogRead(sensor2Pin);
    int adcValue3 = analogRead(sensor3Pin);
    int adcValue4 = analogRead(sensor4Pin);
    int adcValue5 = analogRead(sensor5Pin);
    int adcValue6 = analogRead(sensor6Pin);

    // Convert ADC values to voltage and current ranges
    float frontinv = (adcValue1 / 1023.0) * 500.0;
    float frontinc = (adcValue2 / 1023.0) * 100.0;
    float rearinv  = (adcValue3 / 1023.0) * 500.0;
    float rearinc  = (adcValue4 / 1023.0) * 100.0;
    float motorinv = (adcValue5 / 1023.0) * 500.0;
    float motorinc = (adcValue6 / 1023.0) * 100.0;

    // Print the readings
    Serial.print("FRONT INVERTER VOLTAGE(V): ");
    Serial.println(frontinv, 2);
    Serial.print("FRONT INVERTER CURRENT(A): ");
    Serial.println(frontinc, 2);
    Serial.print("FRONT INVERTER POWER(kW): ");
    Serial.println((frontinv * frontinc), 2);

    Serial.print("REAR INVERTER VOLTAGE(V): ");
    Serial.println(rearinv, 2);
    Serial.print("REAR INVERTER CURRENT(A): ");
    Serial.println(rearinc, 2);
    Serial.print("REAR INVERTER POWER(kW): ");
    Serial.println((rearinv * rearinc), 2);

    Serial.print("MOTOR INVERTER VOLTAGE(V): ");
    Serial.println(motorinv, 2);
    Serial.print("MOTOR INVERTER CURRENT(A): ");
    Serial.println(motorinc, 2);
    Serial.print("MOTOR INVERTER POWER(kW): ");
    Serial.println((motorinv * motorinc), 2);
}

#endif
