#include "controller.h"
#include <Arduino.h>

#define recvCH1 8   
#define recvCH2 9  
#define recvCH3 10
#define recvCH4 11
#define recvCH5 12
#define recvCH6 13

Controller::Controller() {
  pinMode(recvCH1, INPUT);
  pinMode(recvCH2, INPUT);
  pinMode(recvCH3, INPUT);
  pinMode(recvCH4, INPUT);
  pinMode(recvCH5, INPUT);
  pinMode(recvCH6, INPUT);
}
void Controller::setCH(unsinged long value, int i) {
  
}
unsigned long Controller::getCH(int i);

private:
  unsigned long valueCH[6];

