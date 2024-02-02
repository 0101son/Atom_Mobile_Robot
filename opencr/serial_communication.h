#ifndef SERIAL_COMMUNICATION_H_
#define SERIAL_COMMUNICATION_H_

#include <Arduino.h>

enum SpeedField {
  FRONT_LEFT, 
  FRONT_RIGHT, 
  REAR_LEFT, 
  REAR_RIGHT
};
enum AngleField {
  FRONT_ANGLE, 
  REAR_ANGLE
};

class RCStatus {
private:
  int speedValues[4];  // Front left, front right, rear left, rear right
  int angleValues[2];  // Front angle, rear angle

public:
  RCStatus();
  void setSpeedValue(SpeedField field, int value);
  int getSpeedValue(SpeedField field) const;
  void setAngleValue(AngleField field, int value);
  int getAngleValue(AngleField field) const;
};

#endif
