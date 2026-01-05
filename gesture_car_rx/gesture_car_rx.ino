// Receiver with FIXED Left/Right Logic + Debug Comments
// Arduino Pins 0 & 1 are used for Bluetooth (Hardware Serial)

// Motor Driver Connections (L298N)
const int motorA1 = 8;
const int motorA2 = 9;
const int motorB1 = 10;
const int motorB2 = 11;

char command;

void setup() {
  // Start Serial at 9600
  // Used for both Bluetooth communication AND debugging on PC
  Serial.begin(9600); 

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  
  Serial.println("--- Car Ready (Steering Fixed) ---");
  Serial.println("Waiting for commands from ESP32...");
}

void loop() {
  // Check if data is coming from the HC-05
  if (Serial.available() > 0) {
    command = Serial.read();

    // Print the received command to the Serial Monitor
    Serial.print("Received: ");
    Serial.print(command);
    Serial.print(" -> Action: ");

    switch (command) {
      case 'F': 
        Serial.println("MOVING FORWARD");
        moveForward(); 
        break;
        
      case 'B': 
        Serial.println("MOVING BACKWARD");
        moveBackward(); 
        break;
        
      case 'L': 
        Serial.println("TURNING LEFT (Logic Swapped)");
        turnLeft(); 
        break;
        
      case 'R': 
        Serial.println("TURNING RIGHT (Logic Swapped)");
        turnRight(); 
        break;
        
      case 'S': 
        Serial.println("STOPPED");
        stopCar(); 
        break;
        
      default:
        Serial.println("Unknown Command");
        break;
    }
  }
}

// --- Driver Functions ---

void moveForward() {
  digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW);
}

void moveBackward() {
  digitalWrite(motorA1, LOW); digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW); digitalWrite(motorB2, HIGH);
}

// --- FIXED STEERING LOGIC ---

void turnLeft() {
  // We swapped this logic. Now it mimics the old "Right" turn
  // which should result in a correct LEFT turn for your wiring.
  digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW); // Left Wheel Fwd
  digitalWrite(motorB1, LOW); digitalWrite(motorB2, HIGH); // Right Wheel Back
}

void turnRight() {
  // We swapped this logic. Now it mimics the old "Left" turn
  // which should result in a correct RIGHT turn for your wiring.
  digitalWrite(motorA1, LOW); digitalWrite(motorA2, HIGH); // Left Wheel Back
  digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW); // Right Wheel Fwd
}

void stopCar() {
  digitalWrite(motorA1, LOW); digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW); digitalWrite(motorB2, LOW);
}