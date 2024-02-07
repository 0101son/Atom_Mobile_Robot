#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <Arduino.h>

class Controller {
public:
  Controller(byte recvCH[]);
  void setValue(byte channel);
  unsigned long getValue(byte channel);
  void serialTransmission(byte channel);
private:
  unsigned long valueCH[6];
  byte recvCH[6];
};

#endif
