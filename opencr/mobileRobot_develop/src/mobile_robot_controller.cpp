#include "mobile_robot_controller.h"

mobileRobotController::mobileRobotController()
{
}

mobileRobotController::~mobileRobotController()
{
}

bool Turtlebot3Controller::init(float max_lin_vel, float max_ang_vel)
{
  Serial1 = 0; // Serial1 값을 정해주어야 합니다

  IBus_.begin(Serial1);

  max_lin_vel_ = max_lin_vel;
  max_ang_ = max_ang;

  return true;
}

void Turtlebot3Controller::getRCdata(float *get_cmd_vel)
{

  float lin_x = 0.0, ang_z = 0.0;

  // 여기에 입력값()을 lin_x(속력), ang_z(조향각)로 변환하는 계산 알고리즘 삽입
  // 계산을 위한 파라미터는 임의로 수정/추가

  // 예)
  //  lin_x = max_lin_vel * IBus.readChannel(0) / 256;
  //  ang_z = max_lin_vel * IBus.readChannel(1) / 256;

  get_cmd_vel[0] = lin_x;
  get_cmd_vel[1] = ang_z;
}