#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <Arduino.h>

class Controller {
public:
  Controller(byte recvCH1, byte recvCH2, byte recvCH3,
             byte recvCH4, byte recvCH5, byte recvCH6);
  void setValue(byte channel);
  unsigned long getValue(byte channel);
  void serialTransmission(byte channel);
private:
  unsigned long valueCH[6];
  byte recvCH[6];
};

#endif
