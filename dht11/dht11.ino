#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600);
  dht.begin();
}

void loop(){
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  Serial.print("Úmidade relativa: ");
  Serial.print(h);
  Serial.println(" %");
  delay(2500);

  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" C'");
  delay(2500);
}

