#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <Arduino.h>

class Controller {
public:
  Controller(byte recvCH[], byte chNum = 6);
  void setValue(byte channel);
  unsigned long getValue(byte channel);
  void serialTransmission(byte channel);
private:
  byte chNum = 6;
  unsigned long valueCH[chNum];
  byte recvCH[chNum];
};

#endif
