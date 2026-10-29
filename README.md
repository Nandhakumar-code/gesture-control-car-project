# Gesture Control Car Project

A gesture-controlled robotic car project that uses an MPU6050 sensor and Bluetooth communication to control a car using hand movements. The system reads tilt and orientation from a transmitter unit and sends motion commands to a receiver unit that drives the motors.

## Project Overview

This project demonstrates a practical application of:

- Sensor-based gesture detection
- Wireless Bluetooth communication
- Embedded control using ESP32 and Arduino
- Motor control with an L298N driver

The transmitter uses an ESP32 with an MPU6050 accelerometer to detect the user's hand orientation. Based on the detected tilt, it sends commands like:
- Forward
- Backward
- Left
- Right
- Stop

The receiver listens for these commands and drives the robot car accordingly.

---

## Folder Structure

```text
gesture-control-car-project/
├── demo video/
│   └── Project demo video
├── gesture_car_tx/
│   └── gesture_car_tx.ino
├── gesture_car_rx/
│   └── gesture_car_rx.ino
├── wiring Connections/
│   └── wiring connections (1).pdf
├── .gitattributes
├── README.md
└── LICENSE (if added later)
```

---

## Features

- Gesture-based vehicle control
- MPU6050 motion sensing
- ESP32 Bluetooth transmitter
- Arduino receiver with motor control
- Real-time motion commands
- Simple and expandable design for learning and experiments

---

## Hardware Components

### Transmitter Unit
- ESP32 development board
- MPU6050 accelerometer and gyroscope
- HC-05 Bluetooth module
- Power source

### Receiver Unit
- Arduino Uno or compatible board
- L298N motor driver
- 2 DC motors
- Robot chassis
- Battery pack
- Wheels and mechanical assembly

---

## Working Principle

1. The MPU6050 sensor on the transmitter reads the motion and orientation of the hand.
2. The ESP32 calculates tilt values using pitch and roll.
3. Depending on the orientation:
   - Forward movement: `F`
   - Backward movement: `B`
   - Left turn: `L`
   - Right turn: `R`
   - Stop: `S`
4. The command is transmitted over Bluetooth.
5. The receiver receives the signal and drives the motors accordingly.

---

## Transmitter Code

File: `gesture_car_tx/gesture_car_tx.ino`

This code:
- initializes the MPU6050 sensor
- reads acceleration values
- calculates tilt using pitch and roll
- sends commands wirelessly over Bluetooth

### Key behavior
- `pitch < -25` → Forward
- `pitch > 25` → Backward
- `roll < -25` → Left
- `roll > 25` → Right
- Otherwise → Stop

---

## Receiver Code

File: `gesture_car_rx/gesture_car_rx.ino`

This code:
- reads incoming Bluetooth commands
- maps each command to a movement action
- drives the motors using the L298N driver

### Motor actions
- Forward: both motors rotate forward
- Backward: both motors rotate backward
- Left: one wheel forward and the other backward
- Right: opposite wheel rotation
- Stop: both motors stop

---

## Wiring Connections

The repository contains the wiring diagram under:

- `wiring Connections/wiring connections (1).pdf`

It shows the connection details between:
- ESP32 / Arduino
- MPU6050
- Motor driver
- Bluetooth module
- Motors
- Power supply

---

## Setup Instructions

### 1. Install Arduino IDE
Download and install the Arduino IDE from the official Arduino website.

### 2. Install Required Libraries
For the transmitter code, install:
- `Wire`
- `Adafruit_MPU6050`
- `Adafruit_Sensor`
- `BluetoothSerial`

### 3. Upload the Transmitter Code
1. Open `gesture_car_tx/gesture_car_tx.ino`
2. Select the correct ESP32 board
3. Select the correct COM port
4. Upload the code

### 4. Upload the Receiver Code
1. Open `gesture_car_rx/gesture_car_rx.ino`
2. Select the correct Arduino board
3. Select the correct COM port
4. Upload the code

### 5. Power the System
- Power on the transmitter and receiver modules
- Ensure both are connected to a stable power source
- Check the Bluetooth connection

---

## Bluetooth Pairing

The transmitter is configured with the Bluetooth name:

```text
ESP32_Master
```

If needed, use the pairing PIN:

```text
1234
```

Ensure the receiver side is paired and connected correctly before testing.

---

## How to Use

1. Turn on the transmitter and receiver.
2. Pair the Bluetooth modules.
3. Hold the transmitter in your hand.
4. Tilt it in different directions:
   - Forward = move forward
   - Backward = move backward
   - Left = turn left
   - Right = turn right
   - Neutral = stop
5. Observe the robot movement and adjust thresholds if required.

---

## Notes

- Sensor calibration may be needed depending on the orientation and placement of the MPU6050.
- Motor direction may need slight adjustment based on your wiring and mechanical setup.
- The project is suitable for learning robotics, embedded systems, and wireless communication.

---

## Future Improvements

Possible upgrades include:
- obstacle detection using ultrasonic sensors
- speed control using PWM
- mobile app control
- improved gesture calibration
- autonomous navigation features

---

## Conclusion

This project is a simple yet effective demonstration of how human gestures can be translated into robotic movement using embedded electronics and wireless communication. It is a great project for learning about sensors, Bluetooth, motor control, and robotics.

---

## License

This project does not currently include a license file. If you plan to share or distribute it publicly, consider adding an appropriate open-source license such as MIT or Apache 2.0.
