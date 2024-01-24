#ifndef SERIAL_COMMUNICATION_H
#define SERIAL_COMMUNICATION_H

const int packetLength = 5;
char receivedData[packetLength];

const int motorPin = 9;
const int minRPM = 0;
const int maxRPM = 110;

int parseDataToSpeed();
void setMotorSpeed(int speed);
void parseAndSetMotorSpeed();
void serialEvent();

#endif
