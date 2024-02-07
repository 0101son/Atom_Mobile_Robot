#include <stdint.h>
#include <Arduino.h>
#include "mobile_robot_controller.h"

/*******************************************************************************
   Declaration for controllers
 *******************************************************************************/
static MobileRobotController controllers;
static float max_linear_vel = 110.0, max_ang = 180.0;
static byte cmd_values[6] = {0};

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
  byte goal_rpm;
  byte servo_position;
  byte auto_;
  byte reverse;
  byte drive_mod;
  byte estop;
  
  int32_t present_rpm[MortorLocation::MOTOR_NUM_MAX];
} ControlItemVariables;

static ControlItemVariables control_items;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  controllers.init(max_linear_vel, max_ang);
}

void loop()
{
  controllers.getRCdata(cmd_values);

  control_items.goal_rpm = cmd_values[0];
  control_items.servo_position = cmd_values[1];
  control_items.auto_ = cmd_values[2];
  control_items.reverse = cmd_values[3];
  control_items.drive_mod = cmd_values[4];
  control_items.estop = cmd_values[5];

  Serial2.print('z')
  Serial2.write(control_items.goal_rpm);
  Serial2.write(control_items.servo_position);
  Serial2.write(control_items.auto_);
  Serial2.write(control_items.reverse);
  Serial2.write(control_items.drive_mod);
  Serial2.write(control_items.estop);
  Serial2.print('{');

  Serial4.print('z');
  Serial4.write(control_items.goal_rpm);
  Serial4.write(control_items.servo_position);
  Serial4.write(control_items.auto_);
  Serial4.write(control_items.reverse);
  Serial4.write(control_items.drive_mod);
  Serial4.write(control_items.estop);
  Serial4.print('{');
  
  //delay(10);
}