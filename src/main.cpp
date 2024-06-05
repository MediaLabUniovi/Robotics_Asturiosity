//* COMUNICACION I2C ENTRE ESP

// DECLARACIÓN DE LIBRERÍAS
#include <Arduino.h>
#include <Wire.h>

// Definir pines SDA y SCL
#define SDA_PIN 21
#define SCL_PIN 22

byte dataToSend = 0x42;   // Datos a enviar
byte slaveAddress = 0x50; // Dirección del dispositivo esclavo

// //* Funciones CÓDIGO EXCLAVO
// void receiveEvent(int howMany)
// {
//     while (Wire.available())
//     {
//         char c = Wire.read(); // Lee un byte recibido del maestro
//         Serial.print(c);      // Imprime el byte en el monitor serial
//     }
//     Serial.println(); // Nueva línea para el siguiente mensaje
// }

// void requestEvent()
// {
//     Wire.write("Hola maestro!"); // Envía un mensaje de vuelta al maestro
// }

void setup()
{
    //*CODIGO MAESTRO (ESP32-EYE)
    // Iniciar comunicación I2C
    Wire.begin(SDA_PIN, SCL_PIN);
    Serial.begin(115200); // Inicializa comunicación serial
    // delay(1000); //Esperar un poco

    // //* CODIGO ESCLAVO (ESP32)
    // Wire.begin(slaveAddress, SDA_PIN, SCL_PIN); // Inicializa I2C como esclavo con pines específicos
    // Wire.onReceive(receiveEvent);               // Registra la función de callback para recepción de datos
    // Wire.onRequest(requestEvent);               // Registra la función de callback para solicitud de datos
    // Serial.begin(115200);                       // Inicializa la comunicación serial 
}

void loop()
{
    //*CODIGO MAESTRO
    Wire.beginTransmission(slaveAddress); // Iniciar transmisión al dispositivo
    Wire.write(dataToSend);               // Enviar datos
    Wire.endTransmission();               // Finalizar transmisión
    //


    //* Prueba del codigo maestro
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
