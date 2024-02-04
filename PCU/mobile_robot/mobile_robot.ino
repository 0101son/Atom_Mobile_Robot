#include <stdint.h>
#include <Arduino.h>
#include "mobile_robot_controller.h"

/*******************************************************************************
 * Declaration for controllers
 *******************************************************************************/
static MobileRobotController controllers;
static float max_linear_vel = 1.0, max_ang = 1.0;
static float goal_values[2] = {0.0, 0.0};

enum MortorLocation
{
    FRONT_LEFT = 0,
    FRONT_RIGHT,
    REAR_LEFT,
    REAR_RIGHT,
    MOTOR_NUM_MAX
};

typedef struct ControlItemVariables
{
    int32_t goal_rpm;
    int32_t servo_position;

    int32_t present_rpm[MortorLocation::MOTOR_NUM_MAX];
} ControlItemVariables;

static ControlItemVariables control_items;

void setup()
{
    Serial.begin(9600);
    controllers.init(max_linear_vel, max_ang);
}

void loop()
{
    controllers.getRCdata(goal_values);
    control_items.goal_rpm = goal_values[0];
    control_items.servo_position = goal_values[1];
}