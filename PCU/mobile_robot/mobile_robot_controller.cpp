#include "mobile_robot_controller.h"
#include <arduino.h>

MobileRobotController::MobileRobotController() : iBus_(Serial1) {
}

MobileRobotController::~MobileRobotController()
{
}

bool MobileRobotController::init(float max_lin_vel, float max_ang)
{

  iBus_.init(Serial1);

  max_lin_vel_ = 10;
  max_ang_ = 90;

  return true;
}

void MobileRobotController::getRCdata(float *get_cmd_vel)
{

  float lin_x = 0.0, ang_z = 0.0;

  // 여기에 입력값()을 lin_x(속력), ang_z(조향각)로 변환하는 계산 알고리즘 삽입
  // 계산을 위한 파라미터는 임의로 수정/추가
  // float lin_x 0~110
  // float ang_z 0~180

  // 예)
  lin_x = iBus_.readChannel(0);
  ang_z = iBus_.readChannel(1);
  

  get_cmd_vel[0] = lin_x;
  get_cmd_vel[1] = ang_z;
}