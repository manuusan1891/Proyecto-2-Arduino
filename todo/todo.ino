#include <Wire.h>
#include <DHT.h>

// Configuración del sensor DHT11 en pin 5
#define DHTPIN 5            
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Configuración del Sensor de Humedad de Suelo
const int PIN_SUELO = A0; 

// Pines del semáforo (Verificados)
const int LED_ROJO = 12;
const int LED_AMARILLO = 11;
const int LED_VERDE = 10;

void setup() {
  Serial.begin(9600); 
  dht.begin();
  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);

  // 1. ESPERA DE ESTABILIZACIÓN
  // Esperamos 2.5 segundos para asegurarnos de que el DHT11 y el suelo estén listos
  delay(2500); 

  // 2. LECTURA DE SENSORES
  float t = dht.readTemperature();
  float hAmb = dht.readHumidity();

  int valorSueloCrudo = analogRead(PIN_SUELO);
  int hSuelo = map(valorSueloCrudo, 1023, 200, 0, 100); 
  
  if(hSuelo < 0) hSuelo = 0;
  if(hSuelo > 100) hSuelo = 100;

  // Validación de sensor
  if (isnan(t) || isnan(hAmb)) {
    Serial.println("{\"error\": \"Falla en la lectura del DHT11\"}");
    // Encendemos todos los LEDs para avisarte visualmente que falló la lectura
    digitalWrite(LED_VERDE, HIGH); 
    digitalWrite(LED_AMARILLO, HIGH); 
    digitalWrite(LED_ROJO, HIGH);
    return; 
  }

  // 3. LÓGICA DEL SEMÁFORO 
  // Verde: t < 25 e hAmb > 60% e hSuelo > 30%
  if (t < 25.0 && hAmb > 60.0 && hSuelo > 30) {
    digitalWrite(LED_VERDE, HIGH); 
    digitalWrite(LED_AMARILLO, LOW); 
    digitalWrite(LED_ROJO, LOW);
  } 
  // Rojo: t > 32 e hAmb < 40% e hSuelo < 15%
  else if (t > 32.0 && hAmb < 40.0 && hSuelo < 15) {
    digitalWrite(LED_VERDE, LOW); 
    digitalWrite(LED_AMARILLO, LOW); 
    digitalWrite(LED_ROJO, HIGH);
  } 
  // Amarillo: Cualquier otra combinación intermedia o de precaución
  else {
    digitalWrite(LED_VERDE, LOW); 
    digitalWrite(LED_AMARILLO, HIGH); 
    digitalWrite(LED_ROJO, LOW);
  }

  // 4. ENVÍO DE DATOS JSON (Única vez - Intacto para el Dashboard)
  Serial.print("{");
  Serial.print("\"temperatura\":"); Serial.print(t, 1); Serial.print(",");
  Serial.print("\"humAmbiente\":"); Serial.print((int)hAmb); Serial.print(",");
  Serial.print("\"humSuelo\":"); Serial.print(hSuelo);
  Serial.println("}"); 
}

void loop() {
  // El loop se queda completamente vacío. 
  // No necesitamos que repita nada porque ya mediste y vas a apagar el Arduino.
}