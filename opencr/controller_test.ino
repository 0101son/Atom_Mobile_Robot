#include "controller.h"

#define CHNUM 6

unsigned long valueCH1;
unsigned long valueCH2;
unsigned long valueCH3;
unsigned long valueCH1_p;
unsigned long valueCH1_m;

Controller c(8, 9, 10, 11, 12, 13);

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
