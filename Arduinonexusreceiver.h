/*
  Arduinonexusreceiver.h - Nexus 433Mhz radio protocol library for Arduino and Esp8266.
  Created by Jorge García.
  Arduinonexus is licensed under the MIT License.
*/

#ifndef Arduinonexusreceiver_h
#define Arduinonexusreceiver_h

#include "Arduino.h"


#define MAX_CHANGES 128

int getId(long packet);

int getBattery(long packet);

int getChannel(long packet);

float getTemperature(long packet);

int getHumidity(long packet);

void processPacket();

void detectPacket(int duration);

long getPacket();

void handleInterrupt();

int getId(long packet);

bool available();

#endif
