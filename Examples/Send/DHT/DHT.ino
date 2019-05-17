#include "Arduinonexus.h"
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

int pin = 10; // Pin where the transmitter is connected
int channel = 2; // Channel used 0 -> 1, 1 -> 2 , 2 -> 3, 3 -> 4
int id = 14; // Sensor id
int battery = 1; // Battery status (0 -> LOW or 1 -> OK)

DHT dht(DHTPIN, DHTTYPE);
Arduinonexus nexus(pin, channel, id);


void setup() {
  Serial.begin(9600);
}

void loop() {

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.println(t);
  Serial.println(h);
  nexus.send(t, h, battery); 
  delay(10000);
}