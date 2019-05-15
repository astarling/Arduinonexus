
/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
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