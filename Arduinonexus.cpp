/*
  Arduinonexus.cpp - Nexus 433Mhz radio protocol library for Arduino and Esp8266.
  Created by Jorge García.
  Arduinonexus is licensed under the MIT License.
*/

#include "Arduino.h"
#include "Arduinonexus.h"

Arduinonexus::Arduinonexus(int p, int ch, int i, int b){
  pinMode(p, OUTPUT);
  pin = p;
  channel = ch;
  id = i;
  battery = b;

}

void Arduinonexus::send(float temp, float humidity){
  String msg = _parse(channel, id, battery, temp, humidity);
  char buffer[37];
  msg.toCharArray(buffer, 37);

  for(int i=0; i<13; i++){
    digitalWrite(pin, LOW);
    delayMicroseconds(4000);
    for(int i=0; i<37; i++){
      if(msg[i] == '1'){
        _one(pin);
      }
      else{
        _zero(pin);
      }
    }
  }  
}

String Arduinonexus::_pad(String s, int l) {
  String padding = "";
  int size = l - s.length();

  for(int i=0; i<size; i++){
    padding += "0";
  }
  return padding + s;
}

String Arduinonexus::_parse(int channel, int id, int battery, float temp, float humidity){
  String s_id = _pad(String(id, BIN), 8);
  String s_battery = String(battery);
  String s_channel = _pad(String(channel, BIN), 2);
  String s_temp;
  if(temp < 0){
    s_temp = _pad(String(int(temp * 10), BIN), 12).substring(4);      
  }
  else{
    s_temp = _pad(String(int(temp * 10), BIN), 12);
  }
  String s_humidity = _pad(String(int(humidity), BIN), 8);
  
  //         id     Battery      padding      channel     temperature     padding        humidity     padding
  //bits      8        1            1            2             12            4               8           1 
  //      00001110     1            0            01       000000001111      1111          00000111       0
  //data      14       1                         2             1.50                          7   
  String msg = s_id + s_battery + "0" + s_channel + s_temp + "1111" + s_humidity + "0";
  Serial.println(msg);
  return msg;
}

void Arduinonexus::_one(int pin){
  digitalWrite(pin, HIGH);
  delayMicroseconds(500);
  digitalWrite(pin, LOW);
  delayMicroseconds(2000);
}

void Arduinonexus::_zero(int pin){
  digitalWrite(pin, HIGH);
  delayMicroseconds(500);
  digitalWrite(pin, LOW);
  delayMicroseconds(1000);
}
