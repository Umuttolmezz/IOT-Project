# Health Monitor IoT Project

## Project Description

This project is an IoT-based health monitoring system developed using ESP32 and Arduino IoT Cloud.

The system measures:

- Heart Rate (BPM)
- Blood Oxygen Level (SpO2)
- Body Temperature

The collected data is displayed on:

- OLED Display
- Arduino IoT Cloud Dashboard
- Arduino IoT Cloud Remote Mobile Application

If abnormal conditions are detected, the system activates a buzzer alarm and sends a mobile notification through Arduino IoT Cloud.

## Hardware Components

### Main Controller

- ESP32 DOIT DEVKIT V1

### Sensors

- MAX30100 Pulse Oximeter Sensor
- MLX90614 Infrared Temperature Sensor

### Output Devices

- SSD1306 OLED Display
- Active Buzzer

### Additional Components

- Breadboard
- Jumper Wires
- USB Power Supply

## System Features

- Real-time heart rate monitoring
- Real-time body temperature monitoring
- SpO2 monitoring
- OLED live data display
- Arduino IoT Cloud integration
- Mobile monitoring support
- Buzzer warning system
- Push notification support
- Automatic MAX30100 sensor reset mechanism

## Pin Connections

### MAX30100 Connections

| MAX30100 | ESP32 |
| --- | --- |
| VIN | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

### MLX90614 Connections

| MLX90614 | ESP32 |
| --- | --- |
| VIN | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

### OLED Connections

| OLED | ESP32 |
| --- | --- |
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

### Buzzer Connections

| Buzzer | ESP32 |
| --- | --- |
| + | GPIO 25 |
| - | GND |

## Arduino IoT Cloud Variables

| Variable Name | Type | Permission |
| --- | --- | --- |
| bodyTemp | float | Read Only |
| bpm | float | Read Only |
| spo2 | float | Read Only |
| riskStatus | String | Read Only |
| alarmEnabled | bool | Read & Write |

## System Workflow

1. ESP32 initializes all sensors and OLED display.
2. MAX30100 measures BPM and SpO2 values.
3. MLX90614 measures body temperature.
4. Sensor data is displayed on the OLED screen.
5. Data is uploaded to Arduino IoT Cloud.
6. The mobile application receives live sensor data.
7. If threshold values are exceeded:
   - riskStatus becomes ALERT
   - buzzer alarm activates
   - push notification is sent to the mobile device
8. If the MAX30100 sensor stops responding, the system automatically resets the sensor.

## Threshold Values

| Parameter | Threshold |
| --- | --- |
| BPM | > 100 |
| Body Temperature | > 37.5°C |

## Mobile Notification System

Notifications are configured using Arduino IoT Cloud Alerts.

Trigger condition:

```text
riskStatus == ALERT
```

Notification type:

- Push Notification

## Libraries Used

- Wire.h
- Adafruit_GFX.h
- Adafruit_SSD1306.h
- Adafruit_MLX90614.h
- MAX30100_PulseOximeter.h
- ArduinoIoTCloud.h

## Known Issue

The MAX30100 sensor may not provide fully stable heart rate measurements when used together with ESP32 WiFi and Arduino IoT Cloud. During testing, occasional communication interruptions and unstable BPM readings were observed. To improve stability, automatic sensor reset and I2C stabilization mechanisms were implemented in the software.

## Project Outcome

The project successfully demonstrates:

- Real-time health monitoring
- Cloud-based IoT communication
- Mobile device integration
- Alarm and notification mechanisms
- Sensor data visualization using OLED display

## Authors

Developed as an IoT Health Monitoring System project using ESP32 and Arduino IoT Cloud.

DEVREYI BOZDUGUM ICIN RESIM EKLEYEMEDIM HOCAM KUSURA BAKMAYIN
