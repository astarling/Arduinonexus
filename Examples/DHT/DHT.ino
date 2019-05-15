#include "Arduinonexus.h"
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);
Arduinonexus nexus(10, 2, 14, 1);


void setup() {
  Serial.begin(9600);
}

void loop() {

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.println(t);
  Serial.println(h);
  nexus.send(t, h); 
  delay(10000);
}