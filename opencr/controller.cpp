#include "controller.h"

Controller::Controller(byte recvCH1, byte recvCH2, byte recvCH3,
                      byte recvCH4, byte recvCH5, byte recvCH6) {
  this->recvCH[0] = recvCH1;
  this->recvCH[1] = recvCH2;
  this->recvCH[2] = recvCH3;
  this->recvCH[3] = recvCH4;
  this->recvCH[4] = recvCH5;
  this->recvCH[5] = recvCH6;
  pinMode(recvCH1, INPUT);
  pinMode(recvCH2, INPUT);
  pinMode(recvCH3, INPUT);
  pinMode(recvCH4, INPUT);
  pinMode(recvCH5, INPUT);
  pinMode(recvCH6, INPUT);
}

void Controller::setValue(byte channel) {
  valueCH[channel] = pulseIn(recvCH[channel], HIGH);
}
unsigned long Controller::getValue(byte channel){
  return valueCH[channel];
}
void Controller::serialTransmission(byte channel) {
  Serial.print(valueCH[channel]); Serial.print(" ");
  if(channel == 5)
    Serial.println();
}
