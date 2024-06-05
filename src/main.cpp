//*CODIGO MAESTRO


//DECLARACIÓN DE LIBRERÍAS
#include <Arduino.h>
#include <Wire.h>



#define SDA_PIN 21
#define SCL_PIN 22

void setup() {
  // Iniciar comunicación I2C
 Wire.begin();
  Serial.begin(115200); // Inicializa comunicación serial 
  //delay(1000); //Esperar un poco


}

void loop() {
  
}

