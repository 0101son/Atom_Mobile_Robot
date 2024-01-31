#include "controller.h"

Controller::Controller(byte recvCH[]) {
  for (int i=0; i<6; i++) {
    this->recvCH[i] = recvCH[i];
    pinMode(recvCH[i], INPUT);
  }
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
