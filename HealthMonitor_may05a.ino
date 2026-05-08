#include "thingProperties.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>
#include "MAX30100_PulseOximeter.h"

#define SDA_PIN 21
#define SCL_PIN 22
#define BUZZER_PIN 25

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
PulseOximeter pox;

unsigned long lastCloudUpdate = 0;
unsigned long lastSensorRead = 0;
unsigned long lastOLEDUpdate = 0;
unsigned long lastBuzzerCheck = 0;
unsigned long lastBpmAliveTime = 0;

float tempLocal = 0;
float bpmLocal = 0;
float spo2Local = 0;
float previousBpm = -1;

float bpmThreshold = 100;
float tempThreshold = 37.5;

void setup() {
  Serial.begin(115200);
  delay(1500);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000);   // I2C yavaslatildi, MAX30100 icin daha stabil

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  showMessage("Starting...");

  if (!mlx.begin()) {
    showMessage("MLX ERROR");
    while (1);
  }

  if (!pox.begin()) {
    showMessage("MAX30100 ERROR");
    while (1);
  }

  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  lastBpmAliveTime = millis();

  showMessage("System Ready");
}

void loop() {
  pox.update();

  if (millis() - lastCloudUpdate >= 2000) {
    ArduinoCloud.update();
    lastCloudUpdate = millis();
  }

  if (millis() - lastSensorRead >= 1000) {
    tempLocal = mlx.readObjectTempC();
    bpmLocal = pox.getHeartRate();
    spo2Local = pox.getSpO2();

    bodyTemp = tempLocal;
    bpm = bpmLocal;
    spo2 = spo2Local;

    // BPM geliyorsa veya degisiyorsa sensör canlı kabul edilir
    if (bpmLocal > 0 && bpmLocal != previousBpm) {
      lastBpmAliveTime = millis();
      previousBpm = bpmLocal;
    }

    // 6 saniyedir yeni BPM yoksa MAX30100'u yeniden baslat
    if (millis() - lastBpmAliveTime > 6000) {
      showMessage("MAX Reset...");
      resetMAX30100();
      lastBpmAliveTime = millis();
      previousBpm = -1;
    }

    lastSensorRead = millis();
  }

  if (millis() - lastBuzzerCheck >= 100) {
    checkAlarm();
    lastBuzzerCheck = millis();
  }

  if (millis() - lastOLEDUpdate >= 1000) {
    updateOLED();
    lastOLEDUpdate = millis();
  }
}

void checkAlarm() {
  bool alarmCondition = false;

  if (bpmLocal > bpmThreshold || tempLocal > tempThreshold) {
    alarmCondition = true;
  }

  if (alarmCondition) {
    riskStatus = "ALERT";
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    riskStatus = "NORMAL";
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void resetMAX30100() {
  digitalWrite(BUZZER_PIN, LOW);

  Wire.end();
  delay(100);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000);
  delay(100);

  pox.begin();
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  bpmLocal = 0;
  spo2Local = 0;
}

void updateOLED() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Health Monitor");

  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

  display.setCursor(0, 18);
  display.print("BPM: ");
  display.println(bpmLocal);

  display.setCursor(0, 32);
  display.print("SpO2: ");
  display.print(spo2Local);
  display.println(" %");

  display.setCursor(0, 46);
  display.print("Temp: ");
  display.print(tempLocal);
  display.println(" C");

  display.setCursor(82, 0);
  display.print(riskStatus);

  display.display();
}

void showMessage(String msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println(msg);
  display.display();
}

void onAlarmEnabledChange() {
  if (!alarmEnabled) {
    digitalWrite(BUZZER_PIN, LOW);
    riskStatus = "NORMAL";
  }
}