# Health Monitor IoT Project

## Project Overview

This project is an IoT-based Health Monitoring System developed using ESP32 and Arduino IoT Cloud.

## Authors

Developed as an IoT Health Monitoring Project using ESP32 and Arduino IoT Cloud.

The system measures:

- Heart Rate (BPM)
- Blood Oxygen Level (SpO2)
- Body Temperature

Measured data is displayed in real-time on:

- OLED Display
- Arduino IoT Cloud Dashboard
- Mobile Application

When abnormal conditions are detected, the system:

- Activates a buzzer alarm
- Sends push notifications through Arduino IoT Cloud

## Hardware Components

### Main Controller

- ESP32 DOIT DEVKIT V1

### Sensors

- MAX30100 Pulse Oximeter Sensor
- MLX90614 Infrared Temperature Sensor

### Output Devices

- 0.96" OLED Display (SSD1306)
- Active Buzzer

### Additional Components

- Breadboard
- Jumper Wires
- USB Power Supply

## Features

### Real-Time Monitoring

The system continuously monitors:

- Heart Rate (BPM)
- Blood Oxygen Level (SpO2)
- Body Temperature

### OLED Display

Live sensor data is displayed on the OLED screen.

### Arduino IoT Cloud Integration

Sensor data is sent to Arduino IoT Cloud for remote monitoring.

### Mobile Monitoring

Data can be monitored using:

- Arduino IoT Cloud Web Dashboard
- Arduino IoT Cloud Remote Mobile Application

### Alarm System

The buzzer activates when:

- BPM exceeds threshold
- Body temperature exceeds threshold

### Mobile Notifications

Push notifications are sent to the mobile application when a critical condition is detected.

### Automatic Sensor Recovery

The system automatically resets the MAX30100 sensor if communication is lost.

## Pin Connections

### MAX30100

| MAX30100 | ESP32 |
| --- | --- |
| VIN | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

### MLX90614

| MLX90614 | ESP32 |
| --- | --- |
| VIN | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

### OLED SSD1306

| OLED | ESP32 |
| --- | --- |
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

### Buzzer

| Buzzer | ESP32 |
| --- | --- |
| + | GPIO 25 |
| - | GND |

## Arduino IoT Cloud Variables

| Variable | Type | Permission |
| --- | --- | --- |
| bodyTemp | float | Read Only |
| bpm | float | Read Only |
| spo2 | float | Read Only |
| riskStatus | String | Read Only |
| alarmEnabled | bool | Read & Write |

## System Workflow

1. ESP32 initializes sensors and OLED display.
2. MAX30100 continuously measures BPM and SpO2.
3. MLX90614 measures body temperature.
4. Data is displayed on OLED.
5. Sensor values are uploaded to Arduino IoT Cloud.
6. If threshold values are exceeded:
   - riskStatus becomes ALERT
   - buzzer activates
   - mobile notification is triggered
7. If MAX30100 stops responding, the system automatically resets the sensor.

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

The MAX30100 sensor may not provide fully stable heart rate measurements when used together with ESP32 WiFi and Arduino IoT Cloud. During testing, occasional communication interruptions and unstable BPM readings were observed. To reduce this issue, automatic sensor reset and I2C stabilization mechanisms were implemented in the software.

## Challenges Faced

During development:

- MAX30100 instability with WiFi connection was observed.
- ESP32 occasionally lost communication with the sensor.
- Automatic sensor reset logic was implemented to improve stability.
- I2C communication speed was reduced for more reliable operation.

## Future Improvements

Possible future upgrades:

- Replace MAX30100 with MAX30102/MAX30105 for higher stability
- Add battery support
- Add ECG sensor
- Store historical health data
- Improve notification system

DEVREYI BOZDUGUM ICIN RESIM EKLEYEMEDIM HOCAM KUSURA BAKMAYIN
