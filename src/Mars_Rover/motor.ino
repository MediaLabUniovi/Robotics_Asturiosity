#define motorWheel1In1 6  // Pin para IN1 del motor de la rueda 1 (delantera izquierda).
#define motorWheel1In2 7  // Pin para IN2 del motor de la rueda 1.

#define motorWheel2In1 4  // Pin para IN1 del motor de la rueda 2 (media izquierda).
#define motorWheel2In2 5  // Pin para IN2 del motor de la rueda 2.

#define motorWheel3In1 2  // Pin para IN1 del motor de la rueda 3 (trasera izquierda).
#define motorWheel3In2 3  // Pin para IN2 del motor de la rueda 3.

#define motorWheel4In1 13 // Pin para IN1 del motor de la rueda 4 (delantera derecha).
#define motorWheel4In2 10 // Pin para IN2 del motor de la rueda 4.

#define motorWheel5In1 8  // Pin para IN1 del motor de la rueda 5 (media derecha).
#define motorWheel5In2 9  // Pin para IN2 del motor de la rueda 5.

#define motorWheel6In1 11 // Pin para IN1 del motor de la rueda 6 (trasera derecha).
#define motorWheel6In2 12 // Pin para IN2 del motor de la rueda 6.


void initMotors() {
  // Inicialización de los motores, poniendo sus pines en estado bajo (apagados).
  // Motor de la rueda 1 (delantera izquierda)
  digitalWrite(motorWheel1In1, LOW);   
  digitalWrite(motorWheel1In2, LOW);  

  // Motor de la rueda 2 (media izquierda)
  digitalWrite(motorWheel2In1, LOW);
  digitalWrite(motorWheel2In2, LOW);

  // Motor de la rueda 3 (trasera izquierda)
  digitalWrite(motorWheel3In1, LOW);
  digitalWrite(motorWheel3In2, LOW);

  // Motores del lado derecho giran en sentido contrario
  // Motor de la rueda 4 (delantera derecha)
  digitalWrite(motorWheel4In1, LOW);
  digitalWrite(motorWheel4In2, LOW);

  // Motor de la rueda 5 (media derecha)
  digitalWrite(motorWheel5In1, LOW);
  digitalWrite(motorWheel5In2, LOW);

  // Motor de la rueda 6 (trasera derecha)
  digitalWrite(motorWheel6In1, LOW);
  digitalWrite(motorWheel6In2, LOW);
}


void motors(int speed, bool reverse) {
  // Si el modo reversa está desactivado (avanzar hacia adelante)
  if (!reverse) {
    digitalWrite(motorWheel1In1, LOW);
    analogWrite(motorWheel1In2, speed);

    digitalWrite(motorWheel2In1, LOW);
    analogWrite(motorWheel2In2, speed);
    
    digitalWrite(motorWheel3In1, LOW);
    analogWrite(motorWheel3In2, speed);

    analogWrite(motorWheel4In1, speed);
    digitalWrite(motorWheel4In2, LOW);

    digitalWrite(motorWheel5In1, LOW);
    analogWrite(motorWheel5In2, speed);

    digitalWrite(motorWheel6In1, LOW);
    analogWrite(motorWheel6In2, speed);
  } else {
    // Si el modo reversa está activado
    analogWrite(motorWheel1In1, speed);
    digitalWrite(motorWheel1In2, LOW);

    analogWrite(motorWheel2In1, speed);
    digitalWrite(motorWheel2In2, LOW);
    
    analogWrite(motorWheel3In1, speed);
    digitalWrite(motorWheel3In2, LOW);

    digitalWrite(motorWheel4In1, LOW);
    analogWrite(motorWheel4In2, speed);

    analogWrite(motorWheel5In1, speed);
    digitalWrite(motorWheel5In2, LOW);
    
    analogWrite(motorWheel6In1, speed);
    digitalWrite(motorWheel6In2, LOW);
  }
}


void steerServo(int steering) {
  wheel1.write(steering + 70);   // Ajusta la dirección de la rueda 1.
  wheel2.write(-steering + 70);  // Ajusta la dirección de la rueda 2.
  wheel5.write(steering);        // Ajusta la dirección de la rueda 5.
  wheel6.write(-steering + 120); // Ajusta la dirección de la rueda 6.
}



void testMotorsAndServos() {
    int testSpeed = 40;  // Velocidad de prueba para las ruedas
    int delayTime = 5000; // Tiempo de retardo entre cambios

    // Probar las ruedas secuencialmente hacia adelante y luego hacia atrás
    Serial.println("Testing motors...");

    // Apagar todos los motores
    initMotors(); 
    
    // Rueda 1
    Serial.println("Testing Wheel 1 (forward)");
    digitalWrite(motorWheel1In1, LOW);
    analogWrite(motorWheel1In2, testSpeed);
    delay(delayTime);

    Serial.println("Testing Wheel 1 (reverse)");
    analogWrite(motorWheel1In1, testSpeed);
    digitalWrite(motorWheel1In2, LOW);
    delay(delayTime);

    // Apagar todos los motores
    initMotors(); 

    // Rueda 2
    Serial.println("Testing Wheel 2 (forward)");
    digitalWrite(motorWheel2In1, LOW);
    analogWrite(motorWheel2In2, testSpeed);
    delay(delayTime);

    Serial.println("Testing Wheel 2 (reverse)");
    analogWrite(motorWheel2In1, testSpeed);
    digitalWrite(motorWheel2In2, LOW);
    delay(delayTime);

    // Apagar todos los motores
    initMotors(); 

    // Rueda 3
    Serial.println("Testing Wheel 3 (forward)");
    digitalWrite(motorWheel3In1, LOW);
    analogWrite(motorWheel3In2, testSpeed);
    delay(delayTime);

    Serial.println("Testing Wheel 3 (reverse)");
    analogWrite(motorWheel3In1, testSpeed);
    digitalWrite(motorWheel3In2, LOW);
    delay(delayTime);

    // Apagar todos los motores
    initMotors(); 

    // Rueda 4
    Serial.println("Testing Wheel 4 (forward)");
    analogWrite(motorWheel4In1, testSpeed);
    digitalWrite(motorWheel4In2, LOW);
    delay(delayTime);

    Serial.println("Testing Wheel 4 (reverse)");
    digitalWrite(motorWheel4In1, LOW);
    analogWrite(motorWheel4In2, testSpeed);
    delay(delayTime);

    // Apagar todos los motores
    initMotors(); 

    // Rueda 5
    Serial.println("Testing Wheel 5 (forward)");
    digitalWrite(motorWheel5In1, LOW);
    analogWrite(motorWheel5In2, testSpeed);
    delay(delayTime);

    Serial.println("Testing Wheel 5 (reverse)");
    analogWrite(motorWheel5In1, testSpeed);
    digitalWrite(motorWheel5In2, LOW);
    delay(delayTime);

    // Apagar todos los motores
    initMotors(); 

    // Rueda 6
    Serial.println("Testing Wheel 6 (forward)");
    digitalWrite(motorWheel6In1, LOW);
    analogWrite(motorWheel6In2, testSpeed);
    delay(delayTime);

    Serial.println("Testing Wheel 6 (reverse)");
    analogWrite(motorWheel6In1, testSpeed);
    digitalWrite(motorWheel6In2, LOW);
    delay(delayTime);

    // Apagar todos los motores
    initMotors(); 

    // Probar los servos
    Serial.println("Testing servos...");

    // Mover servos al máximo (180 grados)
    Serial.println("Setting servos to maximum");
    wheel1.write(180);
    wheel2.write(180);
    wheel5.write(180);
    wheel6.write(180);
    delay(delayTime);

    // Mover servos al mínimo (0 grados)
    Serial.println("Setting servos to minimum");
    wheel1.write(0);
    wheel2.write(0);
    wheel5.write(0);
    wheel6.write(0);
    delay(delayTime);

    // Mover servos al centro (90 grados)
    Serial.println("Setting servos to center (90 degrees)");
    wheel1.write(90);
    wheel2.write(90);
    wheel5.write(90);
    wheel6.write(90);
    delay(delayTime);

    Serial.println("Test completed.");
}
