/* 
 *  Moisés Frutos Plaza
 *  Mario Losantos Albacete
 */


#include "DHT.h"

#define PIN_SENSOR 3
#define PIN_RELAY 8

#define DHTTYPE DHT11 
#define UMBRAL 2
#define UMBRAL_HUMEDAD 2

unsigned long last_relay_change = 0;
unsigned long t_delay = 5000;
unsigned long tiempo = 0;
float temperatura_inicial = 0;
float humedad_inicial = 0;

int relaystatus = 0;
int ledstatus = 0;
DHT dht(PIN_SENSOR, DHTTYPE);


void abrir_relay(){
  Serial.println("abrir_relay");
  if (relaystatus == 0){
    digitalWrite(PIN_RELAY, HIGH);
    relaystatus = 1;
  }
}

void cerrar_relay(){
  Serial.println("cerrar_relay");
  if (relaystatus == 1){
    digitalWrite(PIN_RELAY, LOW);
    relaystatus = 0;
  }
}

float readTemperature(){
  float t = dht.readTemperature(false);
  Serial.print("Temperatura:");
  Serial.println(t);

  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0;
  }
  return t;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Bienvenido a las practicas de IoT!");

  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_RELAY, OUTPUT);
  dht.begin();
  temperatura_inicial = readTemperature();
}

void check_temperature(){
  float temp = readTemperature();
  if (temp > (temperatura_inicial + UMBRAL) && relaystatus == 0){
    Serial.println("demasiado calor");
    abrir_relay();
  } else if (temp < (temperatura_inicial - UMBRAL) && relaystatus == 1){
    Serial.println("demasiado refrigerado");
    cerrar_relay();
  }
}

void ledOn(){
  
}

void ledOff(){
  
}

float readHumidity(){
  return dht.readHumidity();
}

void check_humidity(){

 float humidity = readHumidity();
  if (humidity > (humedad_inicial + UMBRAL_HUMEDAD) && ledstatus == 0){
    Serial.println("demasiado calor");
    ledOff();
  } else if (humidity < (humedad_inicial - UMBRAL_HUMEDAD) && ledstatus == 1){
    Serial.println("demasiado refrigerado");
    ledOn();
  }
}

void loop() {
  tiempo = millis();

  //delay artificial
  if( tiempo > last_relay_change + t_delay) {
    last_relay_change = tiempo;
    check_temperature();
    check_humidity();
  }
}


/*
 * 
 * Falta leer humedad, con:
 * float h = dht.readHumidity();
 * 
 * y un par de funciones para encender y apagar leds
 * 
*/

