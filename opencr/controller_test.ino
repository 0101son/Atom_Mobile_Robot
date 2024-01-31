#include "controller.h"

#define CHNUM 6

byte recvCh[6] = {8, 9, 10, 11, 12, 13};

Controller c(recvCh);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // receive PWM signals from receiver channel 1 to 3.
  for(byte channel=0; channel<CHNUM; channel++)
    c.setValue(channel);
  for(byte channel=0; channel<CHNUM; channel++)
    c.serialTransmission(channel);
  
}
