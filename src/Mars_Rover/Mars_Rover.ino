/*
  ASTURIOSITY - ROVER
*/

/* ---------------------- Bibliotecas ---------------------- */
#include <Servo.h>               // Control de servomotores.
#include <IBusBM.h>              // Comunicación con el receptor FlySky iBUS.
#include <Adafruit_NeoPixel.h>    // Control de tiras LED NeoPixel.

/* ---------------------- Variables ---------------------- */
#define pinLeds 37      // Pin para controlar los LEDs.
#define numLeds 7       // Número de LEDs en la tira.

IBusBM iBus;             // Instancia para recibir datos iBUS.
IBusBM iBusSensor;       // Instancia para el sensor iBUS (aunque no se utiliza en este código).

int channel0, channel1, channel2, channel3, channel4, channel5, channel6 = 1500; // Canales de iBUS inicializados en 1500 (valor neutral).

Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(numLeds, pinLeds, NEO_GRB + NEO_KHZ800); // Configuración de la tira de LEDs.

int currentSpeed = 0;           // Variable para controlar la velocidad.
int steering = 0;               // Variable para controlar la dirección.
int step = 1;                   // Control del desplazamiento en el efecto LED.

Servo wheel1, wheel2, wheel5, wheel6; // Servos que controlan las ruedas del robot.

long lastTime = 0;             // Control del tiempo para el efecto de LED.

int ledState[7] = {0, 0, 0, 0, 0, 0, 0}; // Arreglo que almacena el estado de los LEDs.
int ledIndex = 0;               // Índice para controlar el estado de los LEDs.

bool isReversing = false;     // Controla si el robot va en reversa.

/* ---------------------- Configuración Inicial  ---------------------- */
void setup() {
    Serial.begin(115200);                            // Inicia comunicación serie a 115200 baudios.
    iBus.begin(Serial1, IBUSBM_NOTIMER);             // Inicia la recepción de datos iBUS.
    iBusSensor.begin(Serial2, IBUSBM_NOTIMER);       // Inicia sensor iBUS (aunque no se usa en el código actual).

    initMotors();                                    // Inicializa los motores (función que no está en el código).
    
    wheel1.attach(22);  // Asigna el pin 22 al servo de la rueda 1.
    wheel2.attach(23);  // Asigna el pin 23 al servo de la rueda 2.
    wheel5.attach(24);  // Asigna el pin 24 al servo de la rueda 5.
    wheel6.attach(25);  // Asigna el pin 25 al servo de la rueda 6.

    ledStrip.begin();       // Inicializa la tira de LEDs.
    ledStrip.show();        // Apaga todos los LEDs.

    // Configura todos los LEDs en azul.
    for (int i = 0; i < numLeds; i++) {
        ledStrip.setPixelColor(i, 0, 0, 255); // Azul: R=0, G=0, B=255.
        ledStrip.show();                      // Actualiza los LEDs.
    }
}

/* ---------------------- Bucle Principal ---------------------- */
void loop() {
    iBus.loop();  // Lee continuamente los valores de los canales del receptor iBUS.

    // Asigna los valores de los canales iBUS a variables.
    channel0 = iBus.readChannel(0);
    channel1 = iBus.readChannel(1);
    channel2 = iBus.readChannel(2);
    channel3 = iBus.readChannel(3);
    channel4 = iBus.readChannel(4);
    channel5 = iBus.readChannel(5);
    channel6 = iBus.readChannel(6);

    // Si el canal 6 tiene un valor menor a 800, se reestablecen los valores predeterminados.
    if (channel6 < 800) {
        channel0 = 1500;
        channel1 = 1500;
        channel2 = 1000;
        channel3 = 1500;
        channel4 = 1500;
        channel5 = 1500;
        channel6 = 1500;
    }

    //printChannelValues();

    // Determina si se activa el modo reversa.
    if (channel4 > 1700) {
        isReversing = true;   // Si el canal 5 es mayor a 1700, el robot va en reversa.
    } else {
        isReversing = false;  // Si no, avanza normalmente.
    }

    if (channel5 > 1700){
      //testMotorsAndServos();
    }

    // Calcula la velocidad con base en el valor del canal 2 (acelerador).
    currentSpeed = map(channel2, 1000, 2000, 0, 75); // Mapea el rango del canal (1000-2000) a una velocidad (0-75).
    motors(currentSpeed, isReversing);               // Controla los motores.

    // Calcula el ángulo de dirección basado en el canal 0 (steering).
    steering = map(channel0, 1000, 2000, -45, 45);   // Mapea el rango del canal a un ángulo entre -45 y 45 grados.
    steerServo(steering);                            // Controla los servos de la dirección.

    // Efecto de LED con desplazamiento.
    if (millis() - lastTime > 75) {  // Cada 75 ms se actualiza el estado de los LEDs.
        ledState[ledIndex] = 255;
        ledState[ledIndex + 1] = 255;

        // Actualiza el color de cada LED con los valores de la matriz `ledState`.
        ledStrip.setPixelColor(0, ledState[0], 0, 0); 
        ledStrip.setPixelColor(1, ledState[1], 0, 0);
        ledStrip.setPixelColor(2, ledState[2], 0, 0);
        ledStrip.setPixelColor(3, ledState[3], 0, 0);
        ledStrip.setPixelColor(4, ledState[4], 0, 0);
        ledStrip.setPixelColor(5, ledState[5], 0, 0);
        ledStrip.setPixelColor(6, ledState[6], 0, 0);
        ledStrip.show();  // Muestra el cambio en los LEDs.

        ledState[ledIndex] = 0;  // Restablece el valor del LED actual.
        ledState[ledIndex + 1] = 0;

        ledIndex += step;  // Actualiza el índice para el siguiente LED.
        lastTime = millis();  // Reinicia el contador de tiempo.

        // Cambia la dirección del desplazamiento de los LEDs cuando alcanza los extremos.
        if (ledIndex == 6) { step = -1; }  
        if (ledIndex == 0) { step = 1; }   
    }
}

void colorWipe(uint32_t color, int wait) {
    // Esta función "limpia" los LEDs uno por uno con el color especificado y un retraso entre cada LED.
    for (int i = 0; i < ledStrip.numPixels(); i++) {
        ledStrip.setPixelColor(i, color);  // Establece el color de un LED.
        ledStrip.show();                   // Muestra el cambio.
        delay(wait);                       // Espera el tiempo especificado.
    }
}

void printChannelValues() {
    // Imprimir los valores de los canales en el puerto Serial
    Serial.print("Channel 0: ");
    Serial.print(channel0);
    Serial.print("\tChannel 1: ");
    Serial.print(channel1);
    Serial.print("\tChannel 2: ");
    Serial.print(channel2);
    Serial.print("\tChannel 3: ");
    Serial.print(channel3);
    Serial.print("\tChannel 4: ");
    Serial.print(channel4);
    Serial.print("\tChannel 5: ");
    Serial.print(channel5);
    Serial.print("\tChannel 6: ");
    Serial.println(channel6);
    delay(500);
}

