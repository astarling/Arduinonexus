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
  Arduinonexus(int p, int ch, int i, int b);
  void send(float temp, float humidity);
  int pin;
  int channel;
  int id;
  int battery;

private:
  String _parse(int channel, int code, int battery, float temp, float humidity);
  String _pad(String s, int l);
  void _one(int pin);
  void _zero(int pin);
};

#endif
