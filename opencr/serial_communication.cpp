#include "serial_communication.h"

RCStatus::RCStatus()
: speedValues{0, 0, 0, 0}, angleValues{0, 0} 
{}

void RCStatus::setSpeedValue(SpeedField field, int value) {
  speedValues[field] = value;
}

int RCStatus::getSpeedValue(SpeedField field) const {
  return speedValues[field];
}

void RCStatus::setAngleValue(AngleField field, int value) {
  angleValues[field] = value;
}

int RCStatus::getAngleValue(AngleField field) const {
  return angleValues[field];
}
