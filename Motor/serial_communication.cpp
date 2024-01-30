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


int i = 0;
//String inputString = "";
//int chValue[6] = { 0 };
//
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//}
//
//void loop() {
//  while (Serial.available() > 0) {
//    char inChar = (char)Serial.read();
//    inputString += inChar;
//    if (inChar == ' ') {
//      chValue[i] = inputString.toInt();
//      inputString = "";
//      i++;
//    }
//    else if (inChar == '\n') {
//      chValue[i] = inputString.toInt();
//      inputString = "";
//      i = 0;
//    }
//  }
//  for(int j=0; j<6; j++) {
//    if (j != 5) {
//      Serial.print(chValue[j]);
//      Serial.print(" ");
//    }
//    else
//      Serial.println(chValue[j]);
//  }
//}
