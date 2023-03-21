
#include <Arduino.h>

#include <Servo.h>
#include <ServoEasing.hpp> // proporciona una forma fácil de crear movimientos de servo suaves y personalizados.
// Esta librería utiliza algoritmos de interpolación para calcular el movimiento de los servos de manera precisa y suave,
// permitiendo a los usuarios crear patrones de movimiento específicos como ondas sinusoidales, ondas cuadradas, rampas, escalones, etc.
// Además, la librería ofrece la capacidad de personalizar la curva de movimiento para adaptarse a diferentes requisitos.
#include <IBusBM.h>
#include <AccelStepper.h>
#include <SoftwareSerial.h>
// #include <Wire.h>

#define motorW1_IN1 7
#define motorW1_IN2 6
#define motorW2_IN1 5
#define motorW2_IN2 4
#define motorW3_IN1 3
#define motorW3_IN2 2
#define motorW4_IN1 10
#define motorW4_IN2 13
#define motorW5_IN1 9
#define motorW5_IN2 8
#define motorW6_IN1 12
#define motorW6_IN2 11

ServoEasing servoW1;
ServoEasing servoW3;
ServoEasing servoW4;
ServoEasing servoW6;

IBusBM IBus;
IBusBM IBusSensor;

int angle = 0; // servo position in degrees
int ch0, ch1, ch2, ch3, ch4, ch5 = 0;
int servo1Angle = 90;
int servo3Angle = 90;
int servo4Angle = 90;
int servo6Angle = 90;
int s = 0; // rover speed
int r = 0; // turning radius
int m1, m2, m3, m4, m5, m6;

float s1, s2, s3 = 0;
float s1PWM, s2PWM, s3PWM = 0;
float thetaInnerFront, thetaInnerBack, thetaOuterFront, thetaOuterBack = 0;

float d1 = 271; // distancia in mm
float d2 = 278;
float d3 = 301;
float d4 = 304;

void calculateMotorsSpeed(int s, int s1, int s2, int s3)
{
  // if no steering, all wheels speed is the same - straight move
  if (IBus.readChannel(0) > 1450 && IBus.readChannel(0) < 1550)
  {
    s1 = s2 = s3 = s;
  }
  // when steering, wheels speed depend on the turning radius value
  else
  {
    // Outer wheels, furthest wheels from turning point, have max speed
    // Due to the rover geometry, all three outer wheels should rotate almost with the same speed. They differe only 1% so we asume they are the same.
    s1 = s;
    // Inner front and back wheels are closer to the turing point and have lower speeds compared to the outer speeds
    s2 = s * sqrt(pow(d3, 2) + pow((r - d1), 2)) / (r + d4);
    // Inner middle wheel is closest to the turning point, has the lowest speed
    s3 = s * (r - d4) / (r + d4);
  }

  // speed value from 0 to 100% to PWM value from 0 to 255
  s1PWM = map(round(s1), 0, 100, 0, 255);
  s2PWM = map(round(s2), 0, 100, 0, 255);
  s3PWM = map(round(s3), 0, 100, 0, 255);
}

void calculateServoAngle()
{
  // Calculate the angle for each servo for the input turning radius "r"
  thetaInnerFront = round((atan((d3 / (r + d1)))) * 180 / PI);
  thetaInnerBack = round((atan((d2 / (r + d1)))) * 180 / PI);
  thetaOuterFront = round((atan((d3 / (r - d1)))) * 180 / PI);
  thetaOuterBack = round((atan((d2 / (r - d1)))) * 180 / PI);
}

//* 1 SENSOR
// int receiveData()
// {
//   while (Serial3.available() == 0)
//   {
//   }                              // Espera hasta que lleguen datos
//   int data = Serial3.parseInt(); // Lee los datos del puerto serial
//   return data;
// }

//* 4 SENSORES
bool recibirDistancias() {

  // esperar hasta que se reciba un mensaje completo
  if (Serial3.available() >= 4){
    ; // esperar a que se reciban 4 bytes

  // leer los 4 bytes recibidos y convertirlos a enteros
  int distanciaW1 = Serial3.read();
  int distanciaW3 = Serial3.read();
  int distanciaW4 = Serial3.read();
  int distanciaW6 = Serial3.read();

  // imprimir las distancias en el monitor serie Serial
  Serial.print("Distancia motorW1: ");
  Serial.print(distanciaW1);
  Serial.println(" cm ");
  Serial.println();
  delay(1000); // Hacemos una pausa de 100ms

  Serial.print("Distancia motorW3: ");
  Serial.print(distanciaW3);
  Serial.println(" cm ");
  Serial.println();
  delay(1000); // Hacemos una pausa de 100ms

  Serial.print("Distancia motorW4: ");
  Serial.print(distanciaW4);
  Serial.println(" cm ");
  Serial.println();
  delay(1000); // Hacemos una pausa de 100ms

  Serial.print("Distancia motorW6: ");
  Serial.print(distanciaW6);
  Serial.println(" cm ");
  Serial.println();
  delay(1000); // Hacemos una pausa de 100ms

  return true;
  } else {
    return false;
  }
}
  //   Serial.print("Distancias recibidas: ");
  //   Serial.print(distanciaW1);
  //   Serial.print(", ");
  //   Serial.print(distanciaW3);
  //   Serial.print(", ");
  //   Serial.print(distanciaW4);
  //   Serial.print(", ");
  //   Serial.println(distanciaW6);


//   if ((distanciaW1 < 30) || (distanciaW3 < 30) || (distanciaW4 < 30) || (distanciaW6 < 30))
//   {

//     // DC Motors
//     // Motor Wheel 1 - Left Front
//     digitalWrite(motorW1_IN1, LOW); // PWM value
//     digitalWrite(motorW1_IN2, LOW); // Forward
//     // Motor Wheel 2 - Left Middle
//     digitalWrite(motorW2_IN1, LOW);
//     digitalWrite(motorW2_IN2, LOW);
//     // Motor Wheel 3 - Left Back
//     digitalWrite(motorW3_IN1, LOW);
//     digitalWrite(motorW3_IN2, LOW);
//     // right side motors move in opposite direction
//     // Motor Wheel 4 - Right Front
//     digitalWrite(motorW4_IN1, LOW);
//     digitalWrite(motorW4_IN2, LOW);
//     // Motor Wheel 5 - Right Middle
//     digitalWrite(motorW5_IN1, LOW);
//     digitalWrite(motorW5_IN2, LOW);
//     // Motor Wheel 6 - Right Back
//     digitalWrite(motorW6_IN1, LOW);
//     digitalWrite(motorW6_IN2, LOW);
//   }
//   else
//   {
//     break;
//   }
//}

// return true;
//   } else {
//     return false;
//   }
// }

void setup()
{

  // DC Motors
  // Motor Wheel 1 - Left Front
  digitalWrite(motorW1_IN1, LOW); // PWM value
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

  Serial.begin(115200);

  IBus.begin(Serial1, IBUSBM_NOTIMER);       // Servo IBUS
  IBusSensor.begin(Serial2, IBUSBM_NOTIMER); // Sensor IBUS
  Serial3.begin(115200);
  IBusSensor.addSensor(IBUSS_INTV); // add voltage sensor

  servoW1.attach(22);
  servoW3.attach(23);
  servoW4.attach(24);
  servoW6.attach(25);

  servoW1.write(90);
  servoW3.write(90);
  servoW4.write(90);
  servoW6.write(90);

  servoW1.setSpeed(550);
  servoW3.setSpeed(550);
  servoW4.setSpeed(550);
  servoW6.setSpeed(550);
}

void loop()
{

  // //* 1 SENSOR
  // int distance = receiveData(); // Lee los datos del Arduino Nano
  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println(" cm");

  //* 4 SENSORES
  // receiveDistances(); // Lee las distancias desde el Arduino Nano
  // delay(500);
  recibirDistancias();

  // Reading the data comming from the RC Transmitter
  IBus.loop();
  ch0 = IBus.readChannel(0); // Channel 1 Girar
  ch1 = IBus.readChannel(1); // Channel 2 NO
  ch2 = IBus.readChannel(2); // Channel 3 Speed
  ch3 = IBus.readChannel(3); // Channel 4 NO
  ch4 = IBus.readChannel(4); // Channel 5 NO
  ch5 = IBus.readChannel(5); // Channel 6 Direction

  // ch0=1500; // Steering radius
  ch1 = 0; // Camera
  // ch2=1500; // Speed
  ch3 = 0;
  ch4 = 0;
  // ch5=0;

  // Convertign the incoming data
  // Steering right
  if (IBus.readChannel(0) > 1550)
  {
    r = map(IBus.readChannel(0), 1550, 2000, 1400, 600); // turining radius from 1400mm to 600mm
  }
  // Steering left
  else if (IBus.readChannel(0) < 1450)
  {
    r = map(IBus.readChannel(0), 1450, 1000, 1400, 600); // turining radius from 600mm to 1400mm
  }
  // Rover speed in % from 0 to 100
  s = map(IBus.readChannel(2), 1000, 2000, 0, 100); // rover speed from 0% to 100%

  calculateMotorsSpeed(s, s1, s2, s3);
  calculateServoAngle();

  // Steer right
  if (IBus.readChannel(0) > 1550)
  {
    // Servo motors
    // Outer wheels
    servoW1.startEaseTo(97 + thetaInnerFront); // front wheel steer right
    servoW3.startEaseTo(97 - thetaInnerBack);  // back wheel steer left for overall steering to the right of the rover
    // Inner wheels
    servoW4.startEaseTo(94 + thetaOuterFront);
    servoW6.startEaseTo(96 - thetaOuterBack);

    // DC Motors
    if (IBus.readChannel(5) < 1400)
    { // Move forward
      // Motor Wheel 1 - Left Front
      analogWrite(motorW1_IN1, s1PWM); // Outer wheels running at speed1 - max speed
      digitalWrite(motorW1_IN2, LOW);
      // Motor Wheel 2 - Left Middle
      analogWrite(motorW2_IN1, s1PWM);
      digitalWrite(motorW2_IN2, LOW);
      // Motor Wheel 3 - Left Back
      analogWrite(motorW3_IN1, s1PWM);
      digitalWrite(motorW3_IN2, LOW);
      // right side motors move in opposite direction
      // Motor Wheel 4 - Right Front
      digitalWrite(motorW4_IN1, LOW);
      analogWrite(motorW4_IN2, s2PWM); // Inner front wheel running at speed2 - lower speed
      // Motor Wheel 5 - Right Middle
      digitalWrite(motorW5_IN1, LOW);
      analogWrite(motorW5_IN2, s3PWM); // Inner middle wheel running at speed3 - lowest speed
      // Motor Wheel 6 - Right Back
      digitalWrite(motorW6_IN1, LOW);
      analogWrite(motorW6_IN2, s2PWM); // Inner back wheel running at speed2 - lower speed
    }
    else if (IBus.readChannel(5) > 1600)
    {
      // Motor Wheel 1 - Left Front
      digitalWrite(motorW1_IN1, LOW); // Outer wheels running at speed1 - max speed
      analogWrite(motorW1_IN2, s1PWM);
      // Motor Wheel 2 - Left Middle
      digitalWrite(motorW2_IN1, LOW);
      analogWrite(motorW2_IN2, s1PWM);
      // Motor Wheel 3 - Left Back
      digitalWrite(motorW3_IN1, LOW);
      analogWrite(motorW3_IN2, s1PWM);
      // right side motors move in opposite direction
      // Motor Wheel 4 - Right Front
      analogWrite(motorW4_IN1, s2PWM);
      digitalWrite(motorW4_IN2, LOW); // Inner front wheel running at speed2 - lower speed
      // Motor Wheel 5 - Right Middle
      analogWrite(motorW5_IN1, s3PWM);
      digitalWrite(motorW5_IN2, LOW); // Inner middle wheel running at speed3 - lowest speed
      // Motor Wheel 6 - Right Back
      analogWrite(motorW6_IN1, s2PWM);
      digitalWrite(motorW6_IN2, LOW); // Inner back wheel running at speed2 - lower speed
    }
    else if (IBus.readChannel(5) > 1400 || IBus.readChannel(5) < 1600) // &&: y ; || ; ó ; ==: igual
    {
      // DC Motors
      // Motor Wheel 1 - Left Front
      digitalWrite(motorW1_IN1, LOW); // PWM value
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
  }

  // Steer left
  else if (IBus.readChannel(0) < 1450)
  {
    // Servo motors
    servoW1.startEaseTo(97 - thetaOuterFront);
    servoW3.startEaseTo(97 + thetaOuterBack);
    servoW4.startEaseTo(94 - thetaInnerFront);
    servoW6.startEaseTo(96 + thetaInnerBack);

    // DC Motors
    if (IBus.readChannel(5) < 1400)
    { // Move forward
      // Motor Wheel 1 - Left Front
      analogWrite(motorW1_IN1, s2PWM); // PWM value
      digitalWrite(motorW1_IN2, LOW);  // Forward
      // Motor Wheel 2 - Left Middle
      analogWrite(motorW2_IN1, s3PWM);
      digitalWrite(motorW2_IN2, LOW);
      // Motor Wheel 3 - Left Back
      analogWrite(motorW3_IN1, s2PWM);
      digitalWrite(motorW3_IN2, LOW);
      // Motor Wheel 4 - Right Front
      // right side motors move in opposite direction
      digitalWrite(motorW4_IN1, LOW);
      analogWrite(motorW4_IN2, s1PWM);
      // Motor Wheel 5 - Right Middle
      digitalWrite(motorW5_IN1, LOW);
      analogWrite(motorW5_IN2, s1PWM);
      // Motor Wheel 6 - Right Back
      digitalWrite(motorW6_IN1, LOW);
      analogWrite(motorW6_IN2, s1PWM);
    }
    else if (IBus.readChannel(5) > 1600)
    { // Move backward
      // Motor Wheel 1 - Left Front
      digitalWrite(motorW1_IN1, LOW);  // PWM value
      analogWrite(motorW1_IN2, s2PWM); // Forward
      // Motor Wheel 2 - Left Middle
      digitalWrite(motorW2_IN1, LOW);
      analogWrite(motorW2_IN2, s3PWM);
      // Motor Wheel 3 - Left Back
      digitalWrite(motorW3_IN1, LOW);
      analogWrite(motorW3_IN2, s2PWM);
      // Motor Wheel 4 - Right Front
      // right side motors move in opposite direction
      analogWrite(motorW4_IN1, s1PWM);
      digitalWrite(motorW4_IN2, LOW);
      // Motor Wheel 5 - Right Middle
      analogWrite(motorW5_IN1, s1PWM);
      digitalWrite(motorW5_IN2, LOW);
      // Motor Wheel 6 - Right Back
      analogWrite(motorW6_IN1, s1PWM);
      digitalWrite(motorW6_IN2, LOW);
    }
    else if (IBus.readChannel(5) > 1400 || IBus.readChannel(5) < 1600)
    {
      // DC Motors
      // Motor Wheel 1 - Left Front
      digitalWrite(motorW1_IN1, LOW); // PWM value
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
  }
  // Move straight
  else
  {
    servoW1.startEaseTo(97);
    servoW3.startEaseTo(97);
    servoW4.startEaseTo(94);
    servoW6.startEaseTo(96);

    // DC Motors
    if (IBus.readChannel(5) < 1400)
    {
      // Motor Wheel 1 - Left Front
      analogWrite(motorW1_IN1, s1PWM); // all wheels move at the same speed
      digitalWrite(motorW1_IN2, LOW);  // Forward
      // Motor Wheel 2 - Left Middle
      analogWrite(motorW2_IN1, s1PWM);
      digitalWrite(motorW2_IN2, LOW);
      // Motor Wheel 3 - Left Back
      analogWrite(motorW3_IN1, s1PWM);
      digitalWrite(motorW3_IN2, LOW);
      // right side motors move in opposite direction
      // Motor Wheel 4 - Right Front
      digitalWrite(motorW4_IN1, LOW);
      analogWrite(motorW4_IN2, s1PWM);
      // Motor Wheel 5 - Right Middle
      digitalWrite(motorW5_IN1, LOW);
      analogWrite(motorW5_IN2, s1PWM);
      // Motor Wheel 6 - Right Back
      digitalWrite(motorW6_IN1, LOW);
      analogWrite(motorW6_IN2, s1PWM);
    }
    else if (IBus.readChannel(5) > 1600)
    {
      // Motor Wheel 1 - Left Front
      digitalWrite(motorW1_IN1, LOW);  // all wheels move at the same speed
      analogWrite(motorW1_IN2, s1PWM); // Forward
      // Motor Wheel 2 - Left Middle
      digitalWrite(motorW2_IN1, LOW);
      analogWrite(motorW2_IN2, s1PWM);
      // Motor Wheel 3 - Left Back
      digitalWrite(motorW3_IN1, LOW);
      analogWrite(motorW3_IN2, s1PWM);
      // right side motors move in opposite direction
      // Motor Wheel 4 - Right Front
      analogWrite(motorW4_IN1, s1PWM);
      digitalWrite(motorW4_IN2, LOW);
      // Motor Wheel 5 - Right Middle
      analogWrite(motorW5_IN1, s1PWM);
      digitalWrite(motorW5_IN2, LOW);
      // Motor Wheel 6 - Right Back
      analogWrite(motorW6_IN1, s1PWM);
      digitalWrite(motorW6_IN2, LOW);
    }
    else if (IBus.readChannel(5) > 1400 || IBus.readChannel(5) < 1600)
    {
      // DC Motors
      // Motor Wheel 1 - Left Front
      digitalWrite(motorW1_IN1, LOW); // PWM value
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
  }

  //* Monitor the battery voltage
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.00 / 1023.00) * 3.02; // Convert the reading values from 5v to suitable 12V
  // Send battery voltage value to transmitter
  IBusSensor.loop();
  IBusSensor.setSensorMeasurement(1, voltage * 100);
}