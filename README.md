### README for EVSMS - Electric Vehicle Stats Monitoring System

---

# EVSMS (Electric Vehicle Stats Monitoring System)

## Overview
EVSMS is a comprehensive monitoring system designed for electric vehicles (EVs) to measure and display key statistics such as inverter voltages, currents, power, motor RPM, vehicle speed, and temperatures at various critical points. This system provides real-time data acquisition and monitoring using sensors like DS18B20 temperature sensors, an MPU6050 accelerometer, and an infrared (IR) sensor for RPM calculation.

---

## Features
- **Inverter Voltage & Current Monitoring**: Measure and display voltages (0-500V) and currents (0-100A) from three critical inverters (front, rear, motor).
- **Power Calculation**: Calculate and display the power (in kW) for each inverter.
- **Temperature Monitoring**: Collect and display temperature data from various points such as the front stator, rear stator, transmission, battery inlet, and battery temperature using DS18B20 sensors.
- **RPM Calculation**: Measure and display the RPM of a rotating component using an IR sensor.
- **Speed Estimation**: Estimate and display the speed of the vehicle using an MPU6050 accelerometer for real-time acceleration data.
- **Modular Code Structure**: The system is divided into separate modules for temperature sensing, ADC readings, and speed & RPM calculations, ensuring clean and maintainable code.

---

## Hardware Components
1. **Microcontroller**: Arduino or compatible board.
2. **Temperature Sensors**: DS18B20 (up to 5 sensors).
3. **Accelerometer**: MPU6050 for acceleration and speed estimation.
4. **IR Sensor**: For RPM measurement.
5. **Voltage & Current Sensors**: Analog sensors connected to ADC pins for measuring voltages and currents.
6. **Wires and Power Supply**: To connect sensors and power the system.

---

## Software Components
- **TemperatureSensors.h**: Manages the DS18B20 temperature sensors.
- **ADCReadings.h**: Reads analog values from ADC pins for voltage and current measurements.
- **SpeedAndRPM.h**: Handles speed estimation from the accelerometer and RPM measurement from the IR sensor.
- **EVSMS.ino**: The main Arduino sketch that initializes and integrates the modules, looping through and displaying data.

---

## Installation

### Step 1: Hardware Setup
1. **Connect DS18B20 sensors** to a common OneWire bus on a digital pin (e.g., pin 2).
2. **Connect analog voltage and current sensors** to ADC pins (A0-A5) for the inverters.
3. **Install the MPU6050 accelerometer** on the I2C bus (SCL and SDA pins).
4. **Connect the IR sensor** to an interrupt-capable digital pin (e.g., pin 3).
5. **Ensure all components are correctly wired and powered** based on their specifications.

### Step 2: Software Setup
1. **Download and Install Arduino IDE**: [Arduino IDE Download](https://www.arduino.cc/en/software)
2. **Add Required Libraries**:
   - Install the following libraries via the Arduino Library Manager:
     - `DallasTemperature`
     - `OneWire`
     - `MPU6050`
3. **Clone or Download this Repository** to your local machine.

### Step 3: Code Upload
1. Open the `MainProgram.ino` in Arduino IDE.
2. Select the appropriate board and port.
3. Upload the code to your Arduino board.

---

## Usage

### Real-time Data Monitoring
1. After uploading the code and powering the system, **open the Serial Monitor** in the Arduino IDE (set the baud rate to 9600).
2. The system will start displaying:
   - Inverter voltages, currents, and power (kW) for the front, rear, and motor inverters.
   - Temperature readings from the 5 sensors (front stator, rear stator, transmission, battery inlet, and battery temperature).
   - The RPM of the rotating part measured by the IR sensor.
   - The vehicle’s estimated speed in meters per second (m/s).

### Data Flow
The main loop cycles through each monitoring task:
- **Temperature Monitoring**: Collects and prints the temperature data.
- **ADC Readings**: Reads voltage and current from the connected sensors and computes the power in kW.
- **Speed & RPM Calculation**: Measures speed using the accelerometer and RPM using the IR sensor, then prints both values.

---

## File Structure

```plaintext
EVSMS/
│
├── TemperatureSensors.h     # Temperature sensor functions
├── ADCReadings.h            # ADC pin reading functions (Voltage/Current)
├── SpeedAndRPM.h            # Speed and RPM calculation functions
├── EVSMS.ino          # Main sketch that calls the above modules
├── README.md                # This documentation
```

---

## Contributing
If you want to contribute to this project, feel free to fork the repository and submit pull requests. Any suggestions, improvements, or bug fixes are welcome.

---

## License
This project is open-source and licensed under the MIT License.

---

## Contact
For any questions or support, please reach out to the project maintainer at `a.adithyavardan1@gmail.com`.

---

**Thank you for using EVSMS!**
