
#include <Servo.h>
//#include <IBusBM.h>
#include <Adafruit_NeoPixel.h>




#define PIN_LEDS 34
#define NUM_LEDS 7

//IBusBM IBus;
//IBusBM IBusSensor;

int ch0, ch1, ch2, ch3, ch4, ch5, ch6 = 1500;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN_LEDS, NEO_GRB + NEO_KHZ800);

int speed = 0;

int steer = 0;
int step = 1;

Servo wheel_1;
Servo wheel_2;
Servo wheel_5;
Servo wheel_6;

long t1 = 0;

int j[7] = { 0, 0, 0, 0, 0, 0, 0 };
int i = 0;

bool reverse = false;

void setup() {


  Serial.begin(115200);
  //IBus.begin(Serial1, IBUSBM_NOTIMER);        // Servo iBUS
  //IBusSensor.begin(Serial2, IBUSBM_NOTIMER);  // Sensor iBUS

  initMotors();

  wheel_1.attach(22);
  wheel_2.attach(23);
  wheel_5.attach(24);
  wheel_6.attach(25);

  strip.begin();
  strip.show();  // Inicialmente, apaga todos los LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0, 0, 255);  // Azul: R=0, G=0, B=255
    strip.show();                       // Muestra los cambios en la tira de LEDs
  }
}

void loop() {

  /* 
  // Read RX
  IBus.loop();

  ch0 = IBus.readChannel(0);
  ch1 = IBus.readChannel(1);
  ch2 = IBus.readChannel(2);
  ch3 = IBus.readChannel(3);
  ch4 = IBus.readChannel(4);
  ch5 = IBus.readChannel(5);
  ch6 = IBus.readChannel(6);
  
  if(ch6<800){
    ch0=1500;
    ch1=1500;
    ch2=1000;
    ch3=1500;
    ch4=1500;
    ch5=1500;
    ch6=1500;
  }
  */
  if (Serial.available() > 0) {  // Se recibe x-x-x-x-x... primer x=velocidad (0-255), segundo direccion(hacia delante o detrás), tercero angulo de giro (0-200)
    // Leer la cadena de caracteres recibida
    String cadena = Serial.readStringUntil('\n');
    char char_array[cadena.length() + 1];  // Convertir la cadena en un arreglo de caracteres
    cadena.toCharArray(char_array, cadena.length() + 1);

    // Inicializar el puntero para la función strtok()
    char *token;

    // Obtener el primer token
    token = strtok(char_array, "-");
    speed = atoi(token);
    token = strtok(NULL, "-");
    int direccion = atoi(token);
    token = strtok(NULL, "-");
    steer = atoi(token);
    if (direccion) {
      reverse = false;
    } else {
      reverse = true;
    }
    steer = map(steer, 0, 200, -45, 45);
    /*
    Serial.print("Velocidad: ");
    Serial.print(speed);
    Serial.print("\tdireccion: ");
    Serial.print(direccion);
    Serial.print("\tGiro: ");
    Serial.println(steer);
    Serial.print("\tÁngulo_giro: ");
    Serial.println(steer);
    */
  }



  //speed = map(ch2, 1000, 2000, 0, 75);
  motors(speed, reverse);

  //Serial.println(speed);
  
  //Serial.println(steer);
  steerServo(steer);


  if (millis() - t1 > 75) {
    j[i] = 255;
    j[i + 1] = 255;
    strip.setPixelColor(0, j[0], 0, 0);
    strip.setPixelColor(1, j[1], 0, 0);
    strip.setPixelColor(2, j[2], 0, 0);
    strip.setPixelColor(3, j[3], 0, 0);
    strip.setPixelColor(4, j[4], 0, 0);
    strip.setPixelColor(5, j[5], 0, 0);
    strip.setPixelColor(6, j[6], 0, 0);
    strip.show();
    j[i] = 0;
    j[i + 1] = 0;
    i = i + step;
    t1 = millis();

    if (i == 6) { step = -1; }
    if (i == 0) { step = 1; }
  }
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}
