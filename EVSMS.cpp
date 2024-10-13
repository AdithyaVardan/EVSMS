#include <OneWire.h>
#include <DallasTemperature.h>

// Define the digital pin for the DS18B20 sensors
#define ONE_WIRE_BUS 2

// Create a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

// Define the ADC pins for the two sensors
int sensor1Pin = A0;  // Sensor 1: 0-500 range
int sensor2Pin = A1;  // Sensor 2: 0-100 range
int sensor3Pin = A2;  // Sensor 3: 0-500 range
int sensor4Pin = A3;  // Sensor 4: 0-100 range
int sensor5Pin = A4;  // Sensor 5: 0-500 range
int sensor6Pin = A5;  // Sensor 6: 0-100 range


void setup() {
  Serial.begin(9600);  // Initialize serial communication

  // Start the DS18B20 sensor library
  sensors.begin();
}

void loop() {
  // Read raw ADC values (0 to 1023 for 0-5V input)
  int adcValue1 = analogRead(sensor1Pin);  // Read from sensor 1 (0-500)
  int adcValue2 = analogRead(sensor2Pin);  // Read from sensor 2 (0-100)
  int adcValue3 = analogRead(sensor3Pin);  // Read from sensor 1 (0-500)
  int adcValue4 = analogRead(sensor4Pin);  // Read from sensor 2 (0-100)
  int adcValue5 = analogRead(sensor5Pin);  // Read from sensor 1 (0-500)
  int adcValue6 = analogRead(sensor6Pin);  // Read from sensor 2 (0-100)

  // Convert sensor 1's ADC value to a 0-500 range with 2 decimal places
  float frontinv = (adcValue1 / 1023.0) * 500.0;
  float frontinc = (adcValue2 / 1023.0) * 100.0;
  float rearinv  = (adcValue3 / 1023.0) * 500.0;
  float rearinc  = (adcValue4 / 1023.0) * 100.0;
  float motorinv = (adcValue5 / 1023.0) * 500.0;
  float motorinc = (adcValue6 / 1023.0) * 100.0;
  // Request temperature readings from the DS18B20 sensors
  sensors.requestTemperatures();

  // Print the analog sensor values
  Serial.print("FRONT INVERTER VOLTAGE(v): ");
  Serial.print(frontinv, 2);  // Print with 2 decimal points
  Serial.print("FRONT INVERTER CURRENT(A): ");
  Serial.print(frontinc, 2);  // Print with 2 decimal points
  Serial.print("FRONT INVERTER POWER(kw):");
  Serial.print((frontinv*frontinc));

  // Print the temperature values from each DS18B20 sensor separately
  float temp1 = sensors.getTempCByIndex(0);  // Get temperature from sensor 1
  float temp2 = sensors.getTempCByIndex(1);  // Get temperature from sensor 2
  float temp3 = sensors.getTempCByIndex(2);  // Get temperature from sensor 3
  float temp4 = sensors.getTempCByIndex(3);  // Get temperature from sensor 4
  float temp5 = sensors.getTempCByIndex(4);  // Get temperature from sensor 5

  // Print each temperature value with error checking
  Serial.print(" | FRONT STATOR: ");
  if (temp1 == DEVICE_DISCONNECTED_C) {
    Serial.print("Error");
  } else {
    Serial.print(temp1, 2);
    Serial.print("°C");
  }

  Serial.print(" | REAR  STATOR: ");
  if (temp2 == DEVICE_DISCONNECTED_C) {
    Serial.print("Error");
  } else {
    Serial.print(temp2, 2);
    Serial.print("°C");
  }

  Serial.print(" | TRANSMISSION: ");
  if (temp3 == DEVICE_DISCONNECTED_C) {
    Serial.print("Error");
  } else {
    Serial.print(temp3, 2);
    Serial.print("°C");
  }

  Serial.print(" | BATTERYINLET: ");
  if (temp4 == DEVICE_DISCONNECTED_C) {
    Serial.print("Error");
  } else {
    Serial.print(temp4, 2);
    Serial.print("°C");
  }

  Serial.print(" | BATTERYTEMP: ");
  if (temp5 == DEVICE_DISCONNECTED_C) {
    Serial.print("Error");
  } else {
    Serial.print(temp5, 2);
    Serial.print("°C");
  }

  Serial.println();  // End of line for readability
  delay(1000);  // Wait for a second before the next reading
}
