#include "Arduinonexus.h"

int pin = 10; // Pin where the transmitter is connected
int channel = 2; // Channel used 0 -> 1, 1 -> 2 , 2 -> 3, 3 -> 4
int id = 14; // Sensor id
int battery = 1; // Battery status (0 -> LOW or 1 -> OK)



Arduinonexus nexus(10, 2, 14, 1);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
    
  nexus.send(15.0, 32); 
  delay(10000);
}