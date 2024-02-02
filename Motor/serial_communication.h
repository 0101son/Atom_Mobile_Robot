#ifndef SERIAL_COMMUNICATION_H
#define SERAIL_COMMUNICATION_H

const int packetLength = 13;
const int data_count = 4;
const int motorPin = 9;
const int minRPM = 0;
const int maxRPM = 110;
float velocity[2] = {0};
int received_RPM = 0;
int received_steering = 0;
byte received_motorDir = 0;
byte received_steerMode = 0;

void parseData(char packet[]);
void serialEvent();

#endif
