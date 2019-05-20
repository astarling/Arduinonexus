/*
  Arduinonexus.cpp - Nexus 433Mhz radio protocol library for Arduino and Esp8266.
  Created by Jorge García.
  Arduinonexus is licensed under the MIT License.
*/

#include "Arduino.h"
#include "Arduinonexus.h"

// #define DEBUG

// This values where tested with an Arduino UNo R3 that has a 16Mhz clock
// You shiuld tweak this values if you are using a microcontroller with
// a different clock speed.

int BITS_TART = 500;
int ONE_DELAY = 1800;
int ZERO_DELAY = 800;

Arduinonexus::Arduinonexus(int p, int ch, int i){
  pinMode(p, OUTPUT);
  pin = p;
  channel = ch;
  id = i;
  
}

void Arduinonexus::send(float temperature, float humidity, int battery){
  uint64_t packet = _parse(id, battery, channel, temperature, humidity);
  bitClear(packet, 36);
  #ifdef DEBUG
  Serial.print("Raw: ~0x");
  Serial.println((unsigned long) packet, HEX);
  Serial.print("Bin: ");
  Serial.println((unsigned long) packet, BIN);
  #endif 
  
  for(int i=0; i<13; i++){
    int bit;
    digitalWrite(pin, LOW);
    delayMicroseconds(4000);
    for(int j=35; j>=0; j--){
      bit = (packet >> j) & 1;
      if(bit == 1){

        #ifdef DEBUG
          Serial.print(1);
        #endif

        _one(pin);

      }
      else{

        #ifdef DEBUG
          Serial.print(0);
        #endif

        _zero(pin);
      }
    }

    _zero(pin); // traling 0

    #ifdef DEBUG
      Serial.print(0);
      Serial.println("");
    #endif
  } 
}

uint64_t Arduinonexus::_parse(int id, int battery, int channel, float temp, float hum){
  uint64_t packet = 0;
  int temperature = temp * 10;
  int humidity = hum;

  packet = (packet << 8) | id;
  packet = (packet << 1) | battery;
  packet = (packet << 1); // 1 bit 0 padding
  packet = (packet << 2) | channel;
  packet = (packet << 12) | temperature;
  packet = (packet << 4) | 15; // 4 bits 1 padding 
  packet = (packet << 8) | humidity;

  #ifdef DEBUG
    Serial.println((unsigned long) packet, BIN);
  #endif 

  return packet;

}

void Arduinonexus::_one(int pin){
  digitalWrite(pin, HIGH);
  delayMicroseconds(BITS_TART);
  digitalWrite(pin, LOW);
  delayMicroseconds(ONE_DELAY);
}

void Arduinonexus::_zero(int pin){
  digitalWrite(pin, HIGH);
  delayMicroseconds(BITS_TART);
  digitalWrite(pin, LOW);
  delayMicroseconds(ZERO_DELAY);
}
