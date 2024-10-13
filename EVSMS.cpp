#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MPU6050.h>

// Define the digital pin for the DS18B20 sensors
#define ONE_WIRE_BUS 2
#define IR_SENSOR_PIN 3  // IR module connected to digital pin 3 (Interrupt pin)

// Create a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
MPU6050 accelgyro;

// Define the ADC pins for the two sensors voltage and current
int sensor1Pin = A0;
int sensor2Pin = A1;
int sensor3Pin = A2;
int sensor4Pin = A3;
int sensor5Pin = A4;
int sensor6Pin = A5;

// Variables for IR sensor RPM counting
volatile int pulseCount = 0;
unsigned long previousMillis = 0;
const unsigned long interval = 1000;  // Time interval for RPM calculation (1 second)

// Variables for speed estimation
float accelX;            // X-axis acceleration from accelerometer
float velocity = 0;       // Current velocity of the vehicle
unsigned long lastTime;   // To keep track of time between updates
float timeStep;           // Time interval for speed calculation (in seconds)

// ISR to count pulses
void IR_interrupt() {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);  // Initialize serial communication

  // Start the DS18B20 sensor library
  sensors.begin();

  // Initialize IR sensor input and attach interrupt
  pinMode(IR_SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN), IR_interrupt, FALLING);  // Detect falling edge

  // Initialize accelerometer
  Wire.begin();
  accelgyro.initialize();
  
  // Check connection
  if (!accelgyro.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  lastTime = millis();
}

void loop() {
  // Read raw ADC values (0 to 1023 for 0-5V input)
  int adcValue1 = analogRead(sensor1Pin);  // Read from sensor 1 V(0-500)
  int adcValue2 = analogRead(sensor2Pin);  // Read from sensor 2 A(0-100)
  int adcValue3 = analogRead(sensor3Pin);  // Read from sensor 3 V(0-500)
  int adcValue4 = analogRead(sensor4Pin);  // Read from sensor 4 A(0-100)
  int adcValue5 = analogRead(sensor5Pin);  // Read from sensor 5 V(0-500)
  int adcValue6 = analogRead(sensor6Pin);  // Read from sensor 6 A(0-100)

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

  // Print temperature values
  float temp1 = sensors.getTempCByIndex(0);
  float temp2 = sensors.getTempCByIndex(1);
  float temp3 = sensors.getTempCByIndex(2);
  float temp4 = sensors.getTempCByIndex(3);
  float temp5 = sensors.getTempCByIndex(4);

  Serial.print(" | FRONT STATOR: ");
  Serial.print((temp1 == DEVICE_DISCONNECTED_C) ? "Error" : String(temp1, 2) + "°C");

  Serial.print(" | REAR STATOR: ");
  Serial.print((temp2 == DEVICE_DISCONNECTED_C) ? "Error" : String(temp2, 2) + "°C");

  Serial.print(" | TRANSMISSION: ");
  Serial.print((temp3 == DEVICE_DISCONNECTED_C) ? "Error" : String(temp3, 2) + "°C");

  Serial.print(" | BATTERY INLET: ");
  Serial.print((temp4 == DEVICE_DISCONNECTED_C) ? "Error" : String(temp4, 2) + "°C");

  Serial.print(" | BATTERY TEMP: ");
  Serial.println((temp5 == DEVICE_DISCONNECTED_C) ? "Error" : String(temp5, 2) + "°C");

  // Calculate RPM
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    int rpm = pulseCount * 60;  // Calculate RPM
    pulseCount = 0;  // Reset pulse count for next interval
    
    Serial.print(" | RPM: ");
    Serial.println(rpm);
  }

  // Read accelerometer data and calculate speed
  accelX = accelgyro.getAccelerationX() / 16384.0;  // MPU6050 gives raw values, convert to 'g'
  
  unsigned long currentTime = millis();
  timeStep = (currentTime - lastTime) / 1000.0;  // Calculate time difference in seconds
  lastTime = currentTime;

  velocity += accelX * 9.81 * timeStep;  // Integrate acceleration to get velocity (m/s), 9.81 m/s² is gravity

  Serial.print(" | Speed (m/s): ");
  Serial.println(velocity);

  delay(1000);  // Wait for a second before the next reading
}
