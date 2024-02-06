#include <stdint.h>
#include <Arduino.h>
#include "mobile_robot_controller.h"

/*******************************************************************************
   Declaration for controllers
 *******************************************************************************/
static MobileRobotController controllers;
static float max_linear_vel = 110.0, max_ang = 180.0;
static float goal_values[2] = {0.0, 0.0};
static int switch_values[4] = {0, 0, 0, 0};

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
  uint32_t goal_rpm;
  uint32_t servo_position;
  uint8_t auto_;
  uint8_t reverse;
  uint8_t drive_mod;
  uint8_t estop;
  
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
  controllers.getRCdata(goal_values, switch_values);

  control_items.goal_rpm = goal_values[0];
  control_items.servo_position = goal_values[1];
  control_items.auto_ = switch_values[0];
  control_items.reverse = switch_values[1];
  control_items.drive_mod = switch_values[2];
  control_items.estop = switch_values[3];

  Serial.print(control_items.goal_rpm);
  Serial.print(' ');
  Serial.print(control_items.servo_position);
  Serial.print(' ');
  Serial.print(control_items.auto_);
  Serial.print(' ');
  Serial.print(control_items.reverse);
  Serial.print(' ');
  Serial.print(control_items.drive_mod);
  Serial.print(' ');
  Serial.println(control_items.estop);

  Serial2.print(control_items.goal_rpm);
  Serial2.print(' ');
  Serial2.print(control_items.servo_position);
  Serial2.print(' ');
  Serial2.print(control_items.auto_);
  Serial2.print(' ');
  Serial2.print(control_items.reverse);
  Serial2.print(' ');
  Serial2.print(control_items.drive_mod);
  Serial2.print(' ');
  Serial2.println(control_items.estop);
  
  //delay(10);
}
