#include <Arduino.h>







#define motorW1_IN1 6
#define motorW1_IN2 7
#define motorW2_IN1 4
#define motorW2_IN2 5
#define motorW3_IN1 2
#define motorW3_IN2 3
#define motorW4_IN1 13
#define motorW4_IN2 10
#define motorW5_IN1 8
#define motorW5_IN2 9
#define motorW6_IN1 11
#define motorW6_IN2 12

void setup() {

  Serial.begin(115200);

  digitalWrite(motorW1_IN1, LOW);   // PWM value
  digitalWrite(motorW1_IN2, LOW); // Forward
  // Motor Wheel 2 - Left Middle
  digitalWrite(motorW2_IN1, LOW);
  digitalWrite(motorW2_IN2, LOW);
  // Motor Wheel 3 - Left Back
  digitalWrite(motorW3_IN1, LOW);
  digitalWrite(motorW3_IN2, LOW);
  // right side motors move in opposite direction
  // Motor Wheel 4 - Right Front
  digitalWrite(motorW4_IN1, LOW);
  digitalWrite(motorW4_IN2, LOW);
  // Motor Wheel 5 - Right Middle
  digitalWrite(motorW5_IN1, LOW);
  digitalWrite(motorW5_IN2, LOW);
  // Motor Wheel 6 - Right Back
  digitalWrite(motorW6_IN1, LOW);
  digitalWrite(motorW6_IN2, LOW);
}

void loop() {
  
  analogWrite(motorW1_IN1, 200);   // PWM value
  digitalWrite(motorW1_IN2, LOW); // Forward

  analogWrite(motorW2_IN1, 200);
  digitalWrite(motorW2_IN2, LOW);

  analogWrite(motorW3_IN1, 200);   // PWM value
  digitalWrite(motorW3_IN2, LOW); // Forward

  analogWrite(motorW4_IN1, 200);
  digitalWrite(motorW4_IN2, LOW);

  analogWrite(motorW5_IN1, 200);
  digitalWrite(motorW5_IN2, LOW);
  
  analogWrite(motorW6_IN1, 200);
  digitalWrite(motorW6_IN2, LOW);
  
  delay(10000);

  digitalWrite(motorW1_IN1, LOW);   // PWM value
  digitalWrite(motorW1_IN2, LOW); // Forward
  // Motor Wheel 2 - Left Middle
  digitalWrite(motorW2_IN1, LOW);
  digitalWrite(motorW2_IN2, LOW);
  // Motor Wheel 3 - Left Back
  digitalWrite(motorW3_IN1, LOW);
  digitalWrite(motorW3_IN2, LOW);
  // right side motors move in opposite direction
  // Motor Wheel 4 - Right Front
  digitalWrite(motorW4_IN1, LOW);
  digitalWrite(motorW4_IN2, LOW);
  // Motor Wheel 5 - Right Middle
  digitalWrite(motorW5_IN1, LOW);
  digitalWrite(motorW5_IN2, LOW);
  // Motor Wheel 6 - Right Back
  digitalWrite(motorW6_IN1, LOW);
  digitalWrite(motorW6_IN2, LOW);

  delay(10000);

  digitalWrite(motorW1_IN1, LOW);   // PWM value
  analogWrite(motorW1_IN2, 200); // Forward

  digitalWrite(motorW2_IN1, LOW);
  analogWrite(motorW2_IN2, 200);

  digitalWrite(motorW3_IN1, LOW);   // PWM value
  analogWrite(motorW3_IN2, 200); // Forward

  digitalWrite(motorW4_IN1, LOW);
  analogWrite(motorW4_IN2, 200);

  
  digitalWrite(motorW5_IN1, LOW);
  analogWrite(motorW5_IN2, 200);

  
  digitalWrite(motorW6_IN1, LOW);
  analogWrite(motorW6_IN2, 200);

  delay(10000);

  digitalWrite(motorW1_IN1, LOW);   // PWM value
  digitalWrite(motorW1_IN2, LOW); // Forward
  // Motor Wheel 2 - Left Middle
  digitalWrite(motorW2_IN1, LOW);
  digitalWrite(motorW2_IN2, LOW);
  // Motor Wheel 3 - Left Back
  digitalWrite(motorW3_IN1, LOW);
  digitalWrite(motorW3_IN2, LOW);
  // right side motors move in opposite direction
  // Motor Wheel 4 - Right Front
  digitalWrite(motorW4_IN1, LOW);
  digitalWrite(motorW4_IN2, LOW);
  // Motor Wheel 5 - Right Middle
  digitalWrite(motorW5_IN1, LOW);
  digitalWrite(motorW5_IN2, LOW);
  // Motor Wheel 6 - Right Back
  digitalWrite(motorW6_IN1, LOW);
  digitalWrite(motorW6_IN2, LOW);

  delay(10000);
}