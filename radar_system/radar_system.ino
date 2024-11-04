// Includes the Servo library
#include <Servo.h>

// Defines Trig and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;
const int buzzerPin = 13;
const int ledPin = 9;

const int thresholdDistance = 20;
bool buzzerOn = false;

// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin the servo motor is attached
  myServo.write(90);
}

void loop() {
  // Rotate the servo motor from 15 to 165 degrees
  for (int i = 15; i <= 165; i++) {  
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    // Radar LED Blink at end of the sweep (15 and 165 degrees)
    if (i == 60 || i == 15 || i == 105 || i == 150) {
      digitalWrite(ledPin, HIGH); 
      delay(90);                   
      digitalWrite(ledPin, LOW); 
    }
  }

  // Repeats the previous lines from 165 to 15 degrees
  for (int i = 165; i > 15; i--) {  
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    // Radar LED Blink at end of the sweep (15 and 165 degrees)
    if (i == 135 || i == 90 || i == 45) {
      digitalWrite(ledPin, HIGH);
      delay(90);
      digitalWrite(ledPin, LOW); 
    }
  }

  // BUZZER CODE
  if(distance <  thresholdDistance) {
    if(!buzzerOn) {
      digitalWrite(buzzerPin, HIGH); 
      buzzerOn = true;
    }
  } else {
    if(buzzerOn) {
      digitalWrite(buzzerPin, LOW);
      buzzerOn = false;
    }
  }
  /*
  if (distance < 20) { // Adjust the threshold as needed
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  } else {
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  }*/
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() { 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2; // Calculate the distance
  return distance;
}
