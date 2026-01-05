#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "BluetoothSerial.h"

Adafruit_MPU6050 mpu;
BluetoothSerial SerialBT;

// --- CONFIGURATION ---
// HC-05 Address: 00:22:04:00:c8:30
uint8_t address[6]  = {0x00, 0x22, 0x04, 0x00, 0xC8, 0x30};
bool connected = false;

void setup() {
  Serial.begin(115200);

  // 1. Setup MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) { delay(10); }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // 2. Setup Bluetooth
  SerialBT.begin("ESP32_Master", true); 
  
  // --- FIXED PASSWORD LINE ---
  // The '4' tells the ESP32 that the password has 4 characters
  bool pinSet = SerialBT.setPin("1234", 4); 
  
  if (pinSet) {
    Serial.println("PIN set successfully");
  } else {
    Serial.println("Failed to set PIN");
  }

  Serial.println("Bluetooth started. connecting...");

  // Connect using the address
  connected = SerialBT.connect(address);
  
  if(connected) {
    Serial.println("Connected Successfully!");
  } else {
    while(!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Trying again...");
      connected = SerialBT.connect(address);
    }
  }
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float x = a.acceleration.x;
  float y = a.acceleration.y;
  float z = a.acceleration.z;
  
  int pitch = -(atan2(x, sqrt(y*y + z*z)) * 180.0) / PI;
  int roll  = (atan2(y, z) * 180.0) / PI;

  if (connected) {
    if (pitch < -25) SerialBT.write('F'); 
    else if (pitch > 25) SerialBT.write('B'); 
    else if (roll < -25) SerialBT.write('L'); 
    else if (roll > 25) SerialBT.write('R'); 
    else SerialBT.write('S'); 
  }
  
  delay(50);
}