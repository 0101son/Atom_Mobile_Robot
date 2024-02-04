#include "mobile_robot_controller.h"
#include <arduino.h>

MobileRobotController::MobileRobotController() : iBus_(Serial1) {
}

MobileRobotController::~MobileRobotController()
{
}

bool MobileRobotController::init(float max_lin_vel, float max_ang)
{

  iBus_.init();

  max_lin_vel_ = max_lin_vel;
  max_ang_ = max_ang;
  lin_vel_ratio_ = max_lin_vel_/500;
  ang_ratio_ = max_ang_/1000;

  return true;
}

void MobileRobotController::getRCdata(float *get_cmd_vel)
{

  float lin_x = 0.0, ang_z = 0.0;
  
  // 여기에 입력값()을 lin_x(속력), ang_z(조향각)로 변환하는 계산 알고리즘 삽입
  // 계산을 위한 파라미터는 임의로 수정/추가
  // float lin_x 0~110 = ;
  // float ang_z 0~180

  // 예)
  
  iBus_.readRx();

  lin_x = (float)(iBus_.readChannel(velChannel)-1500);
  ang_z = (float)(iBus_.readChannel(SteerChannel)-1000);

  lin_x = constrain(lin_x, 0, 500);

  lin_x = lin_x*lin_vel_ratio_;
  ang_z = ang_z*ang_ratio_;

  get_cmd_vel[0] = lin_x;
  get_cmd_vel[1] = ang_z;
}