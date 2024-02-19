#include "MobileRobotServo.h"

MobileRobotServo::MobileRobotServo(byte FLPin, byte FRPin, byte RLPin, byte RRPin) {
    FLservo.attach(FLPin);
    FRservo.attach(FRPin);
    RLservo.attach(RLPin);
    RRservo.attach(RRPin);
}

MobileRobotServo::~MobileRobotServo() {}

void MobileRobotServo::setAngle(byte goal) {
    this->goal_position = goal;
    FLservo.write(goal_position);
    FRservo.write(goal_position);
    RLservo.write(goal_position);
    RRservo.write(goal_position);
}

float MobileRobotServo::getAngle() const {
    return goal_position;
}
