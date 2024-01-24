#include "serial_communication.h"
#include <Arduino.h>

int parseDataToSpeed() {
  int speed = 0;
  speed = atoi(receivedData);
  if (speed < minRPM) {
    speed = minRPM;
  } else if (speed > maxRPM) {
    speed = maxRPM;
  }
  return speed;
}

void setMotorSpeed(int speed) {
  int motorOutput = map(speed, 0, maxRPM, 0, 255);
  analogWrite(motorPin, motorOutput);
}

void parseAndSetMotorSpeed() {
  int speed = parseDataToSpeed();
  setMotorSpeed(speed);
}

void serialEvent() {
  while (Serial.available()) {
    char receivedChar = Serial.read();
    if (receivedChar == 'S') {
      memset(receivedData, 0, sizeof(receivedData));
    }
    else if (receivedChar == 'E') {
      parseAndSetMotorSpeed();
    }
    else {
      size_t dataLength = strlen(receivedData);
      if (dataLength < packetLength - 1) {
        receivedData[dataLength] = receivedChar;
      }
    }
  }
}
