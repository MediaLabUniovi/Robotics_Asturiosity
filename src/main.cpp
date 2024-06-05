//*CODIGO MAESTRO

// DECLARACIÓN DE LIBRERÍAS
#include <Arduino.h>
#include <Wire.h>
#include <twoWire.h>

// Definir pines SDA y SCL
#define SDA_PIN 21
#define SCL_PIN 22

void setup()
{
    // Iniciar comunicación I2C
    Wire.begin(SDA_PIN, SCL_PIN);
    Serial.begin(115200); // Inicializa comunicación serial
                          // delay(1000); //Esperar un poco
}

void loop()
{
}
