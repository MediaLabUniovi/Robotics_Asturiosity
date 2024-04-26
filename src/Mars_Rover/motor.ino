


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




void initMotors(){

    // Motor Wheel 1 - Left Front
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

void motors(int speed, bool reverse){
  if (reverse==false){
    digitalWrite(motorW1_IN1, LOW);
    analogWrite(motorW1_IN2, speed);

    digitalWrite(motorW2_IN1, LOW);
    analogWrite(motorW2_IN2, speed);
    
    digitalWrite(motorW3_IN1, LOW);
    analogWrite(motorW3_IN2, speed);

    analogWrite(motorW4_IN1, speed);
    digitalWrite(motorW4_IN2, LOW);

    digitalWrite(motorW5_IN1, LOW);
    analogWrite(motorW5_IN2, speed);

    digitalWrite(motorW6_IN1, LOW);
    analogWrite(motorW6_IN2, speed);

  }

  else{

    analogWrite(motorW1_IN1, speed);
    digitalWrite(motorW1_IN2, LOW);

    analogWrite(motorW2_IN1, speed);
    digitalWrite(motorW2_IN2, LOW);
    
    analogWrite(motorW3_IN1, speed);
    digitalWrite(motorW3_IN2, LOW);

    digitalWrite(motorW4_IN1, LOW);
    analogWrite(motorW4_IN2, speed);

    analogWrite(motorW5_IN1, speed);
    digitalWrite(motorW5_IN2, LOW);
    
    analogWrite(motorW6_IN1, speed);
    digitalWrite(motorW6_IN2, LOW);
  }
  
}

void steerServo(int steer){
  wheel_1.write(steer+70);
  wheel_2.write(-steer+70);
  wheel_5.write(steer);
  wheel_6.write(-steer+120);
}