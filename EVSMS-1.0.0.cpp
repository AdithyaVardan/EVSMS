// Define the ADC pins for the two sensors
int sensor1Pin = A0;  // Sensor 1: 0-500 range
int sensor2Pin = A1;  // Sensor 2: 0-100 range

void setup() {
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Read raw ADC values (0 to 1023 for 0-5V input)
  int adcValue1 = analogRead(sensor1Pin);  // Read from sensor 1 (0-500)
  int adcValue2 = analogRead(sensor2Pin);  // Read from sensor 2 (0-100)

  // Convert sensor 1's ADC value to a 0-500 range with 2 decimal places
  float sensor1Value = (adcValue1 / 1023.0) * 500.0;

  // Convert sensor 2's ADC value to a 0-100 range with 2 decimal places
  float sensor2Value = (adcValue2 / 1023.0) * 100.0;

  // Print both sensor values with 2 decimal point precision
  Serial.print("Sensor 1 (0-500): ");
  Serial.print(sensor1Value, 2);  // Print with 2 decimal points
  Serial.print(" | Sensor 2 (0-100): ");
  Serial.println(sensor2Value, 2);  // Print with 2 decimal points

  delay(1000);  // Wait for a second before the next reading
}