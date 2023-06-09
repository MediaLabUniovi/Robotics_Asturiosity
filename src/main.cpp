
//*DECLARACIÓN DE LIBRERÍAS
#include <Arduino.h>

#include <Servo.h>
#include <ServoEasing.hpp> // proporciona una forma fácil de crear movimientos de servo suaves y personalizados.
// Esta librería utiliza algoritmos de interpolación para calcular el movimiento de los servos de manera precisa y suave,
// permitiendo a los usuarios crear patrones de movimiento específicos como ondas sinusoidales, ondas cuadradas, rampas, escalones, etc.
// Además, la librería ofrece la capacidad de personalizar la curva de movimiento para adaptarse a diferentes requisitos.
#include <IBusBM.h>
// #include <AccelStepper.h>
// #include <SoftwareSerial.h>

//* DECLARACIÓN DE VARIABLES
#define STOP_SIGNAL 38

void setup()
{
    Serial.begin(115200);
    pinMode(STOP_SIGNAL, INPUT);
}

void loop(){
    int STOP = digitalRead(STOP_SIGNAL);
    Serial.println(STOP);
    delay(1000);

}