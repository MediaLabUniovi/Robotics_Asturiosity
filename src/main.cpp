//*CODIGO MAESTRO

// DECLARACIÓN DE LIBRERÍAS
#include <Arduino.h>
#include <Wire.h>

// Definir pines SDA y SCL
#define SDA_PIN 21
#define SCL_PIN 22

byte dataToSend = 0x42;   // Datos a enviar
byte slaveAddress = 0x50; // Dirección del dispositivo esclavo

void setup()
{
    // Iniciar comunicación I2C
    Wire.begin(SDA_PIN, SCL_PIN);
    Serial.begin(115200); // Inicializa comunicación serial
    // delay(1000); //Esperar un poco
}

void loop()
{
    Wire.beginTransmission(slaveAddress); // Iniciar transmisión al dispositivo
    Wire.write(dataToSend);               // Enviar datos
    Wire.endTransmission();               // Finalizar transmisión
    //

//   Wire.beginTransmission(slaveAddress); // Inicia la transmisión a la dirección del esclavo
//   Wire.write("Hola esclavo!"); // Envía un mensaje al esclavo
//   Wire.endTransmission(); // Termina la transmisión

//   delay(1000); // Espera un segundo antes de enviar otro mensaje

//   Wire.requestFrom(slaveAddress, 13); // Solicita 13 bytes del esclavo
//   while(Wire.available()) {
//     char c = Wire.read(); // Lee un byte recibido del esclavo
//     Serial.print(c); // Imprime el byte en el monitor serial
//   }
//   Serial.println(); // Nueva línea para el siguiente mensaje
}
