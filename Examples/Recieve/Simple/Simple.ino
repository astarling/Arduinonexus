#include "Arduinonexusreceiver.h"


void setup() {
  Serial.begin(115200);

  // inits receaver pin and helps with noise
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(2, INPUT);
  digitalWrite(2, LOW);

  // Visit https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  // to discover which pins support interrupts on Arduino boards and learning more about interrupts
  // Visit https://www.esp8266.com/wiki/doku.php?id=esp8266_gpio_pin_allocations#interrupts
  // On Esp8266 can be used any GPIO except for GPIO16

  attachInterrupt(digitalPinToInterrupt(2), handleInterrupt, CHANGE);
}

void loop() {
  long p = 0;
  if(available()){
    p = getPacket();
    Serial.print("Raw: 0x");
    Serial.println((unsigned long) p, HEX);
    Serial.print("Bin: ");
    Serial.println((unsigned long) p, BIN);
    Serial.print("Id: ");
    Serial.println(getId(p));
    Serial.print("Battery: ");
    Serial.println(getBattery(p));
    Serial.print("Channel: ");
    Serial.println(getChannel(p));
    Serial.print("Temperatura: ");
    Serial.println(getTemperature(p));
    Serial.print("Humedad: ");
    Serial.println(getHumidity(p));
    Serial.println("");
    Serial.println("");
    Serial.println("");
  }
}