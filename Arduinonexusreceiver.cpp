/*
  Arduinonexusreceiver.cpp - Nexus 433Mhz radio protocol library for Arduino and Esp8266.
  Created by Jorge García.
  Arduinonexus is licensed under the MIT License.
*/

#include "Arduino.h"
#include "Arduinonexusreceiver.h"

// #define DEBUG

const unsigned int ONE = 1800; 
const unsigned int ZERO = 800;
unsigned int timings[128];
unsigned int bitsRead;
unsigned int END_PACKET = 3000; 
unsigned int MIN_PACKET = 650;
unsigned int packet_size = 37;
long packet = 0;

int getId(long packet) {
  bitClear(packet, 36);
  int id = (packet >> 28) & 0xFF;
  return id;
}

int getBattery(long packet) {
  int batt = (packet >> 24) & 0x8;
  return batt ? 1 : 0;
}

int getChannel(long packet) {
  int channel = (packet >> 24) & 0x3;
  return channel+1;
}

float getTemperature(long packet) {
  long t = packet >> 12 & 0x0FFF;
  t = 0x0800 & t ? 0xF000 | t  : t;
  float temperature = float(t) / 10;
  return temperature;
}

int getHumidity(long packet) {
  int humidity = packet & 0xFF;
  return humidity;
}

void processPacket() {
  for(int i=1; i< bitsRead; i++) {
    unsigned duration = timings[i];
    if(duration > ONE) {
        packet = packet << 1;
          bitSet(packet, 0);
        } else if(duration > ZERO) {
          packet = packet << 1;
          bitClear(packet, 0);
        }

  }
  #ifdef DEBUG
    Serial.print("Raw: ~0x");
    Serial.println((unsigned long) packet, HEX);
    Serial.print("Bin: ");
    Serial.println((unsigned long) packet, BIN);
    Serial.print("Temperatura: ");
    Serial.println(getTemperature(packet));
    Serial.print("Humedad: ");
    Serial.println(getHumidity(packet));
  #endif

  if (packet == 0) {
    for(int i=0; i < bitsRead; i++)
      Serial.println(timings[i]);
  }
}

void detectPacket(unsigned int duration) {

  if(duration > END_PACKET) {

      if(bitsRead > packet_size-packet_size*0.1 && bitsRead < packet_size+packet_size*0.1) {  //check if we are in the range +- 10%
      #ifdef DEBUG
        Serial.println(bitsRead);
      #endif
      processPacket();
        }
    bitsRead = 0; 
    }

  if(duration > MIN_PACKET) {
       timings[bitsRead] = duration;
       bitsRead++;
  }

  if(bitsRead == MAX_CHANGES) {
      bitsRead = 0;
  }

}

long getPacket() {
  long p = packet;
  packet = 0;
  return p;
}

void handleInterrupt() {
  static unsigned long lastTime;
  long time = micros();
  unsigned int duration = time - lastTime;

  detectPacket(duration);

  lastTime = time;
}

int getId(uint64_t packet) {
  int id = (packet >> 28) & 0xFF;
  return id;
}

bool available() {
  if(packet != 0) {
      return true;
  }
  return false;
}