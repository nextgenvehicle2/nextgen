// Include the necessary libraries
#include <Arduino.h>

// Define the pin connections
const int irSensorPin = 4;
const int buzzerPin = 5;

void setup() {
  // Set the sensor pin as INPUT
  pinMode(irSensorPin, INPUT);

  // Set the buzzer pin as OUTPUT
  pinMode(buzzerPin, OUTPUT);
  
  // Start the Serial communication
  Serial.begin(115200);
}

void loop() {
  // Read the state of the sensor
  int sensorState = digitalRead(irSensorPin);

  if (sensorState == LOW) {
    Serial.println("Object detected!");
    
    // Turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
  } else {
    // No object detected
    
    // Turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }

  delay(500); // Delay for stability
}
