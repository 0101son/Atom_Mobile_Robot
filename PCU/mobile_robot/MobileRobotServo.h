#ifndef MOBILE_ROBOT_SERVO_H
#define MOBILE_ROBOT_SERVO_H

#include <Arduino.h>
#include <Servo.h>

class MobileRobotServo {
private:
    byte goal_position;
    Servo FLservo;
    Servo FRservo;
    Servo RLservo;
    Servo RRservo;

public:
    MobileRobotServo(byte FLPin, byte FRPin, byte RLPin, byte RRPin);
    ~MobileRobotServo();
    void setAngle(byte goal);
    float getAngle() const;
};

#endif
