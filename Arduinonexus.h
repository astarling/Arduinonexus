/*
  Arduinonexus.h - Nexus 433Mhz radio protocol library for Arduino and Esp8266.
  Created by Jorge García.
  Arduinonexus is licensed under the MIT License.
*/

#ifndef Arduinonexus_h
#define Arduinonexus_h

#include "Arduino.h"

class Arduinonexus {
public:
  Arduinonexus(int p, int ch, int i);
  void send(float temperature, float humidity, int battery);
  int pin;
  int channel;
  int id;
  int battery;

private:
  // String _parse(int channel, int code, int battery, float temp, float humidity);
  uint64_t _parse(int id, int battery, int channel, float temp, float hum);
  // String _pad(String s, int l);
  void _one(int pin);
  void _zero(int pin);
};

#endif
