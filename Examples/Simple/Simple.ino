#include "Arduinonexus.h"

Arduinonexus nexus(10, 2, 14, 1);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
    
  nexus.send(15.0, 32); 
  delay(10000);
}