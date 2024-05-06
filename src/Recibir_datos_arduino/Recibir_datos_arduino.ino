void setup() {
  Serial.begin(115200);

}

float valor1;
int valor2;
long valor3;
int valor4;


void loop() {
  if (Serial.available() > 0) {
    // Leer la cadena de caracteres recibida
    String cadena = Serial.readStringUntil('\n');
    
    // Convertir la cadena en un arreglo de caracteres
    char char_array[cadena.length() + 1];
    cadena.toCharArray(char_array, cadena.length() + 1);
    
    // Inicializar el puntero para la función strtok()
    char *token;
    
    // Obtener el primer token
    token = strtok(char_array, "-");
    
    // Convertir y almacenar el primer valor numérico
    valor1 = atof(token);
    
    // Obtener y almacenar el segundo valor numérico
    token = strtok(NULL, "-");
    valor2 = atoi(token);
    
    // Obtener y almacenar el tercer valor numérico
    token = strtok(NULL, "-");
    valor3 = atol(token);
    
    // Obtener y almacenar el cuarto valor numérico
    token = strtok(NULL, "-");
    valor4 = atoi(token);
    
    // Imprimir los valores numéricos
    Serial.print("Valor 1: ");
    Serial.println(valor1);
    Serial.print("Valor 2: ");
    Serial.println(valor2);
    Serial.print("Valor 3: ");
    Serial.println(valor3);
    Serial.print("Valor 4: ");
    Serial.println(valor4);
  }
}

