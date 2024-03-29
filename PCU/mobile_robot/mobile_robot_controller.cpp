#include "mobile_robot_controller.h"

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
  lin_vel_ratio_ = max_lin_vel_/1000;
  ang_ratio_ = max_ang_/1000;

  return true;
}

void MobileRobotController::getRCdata(byte get_cmd_vel[])
{

  uint16_t lin_x = 0, ang_z = 0;
  
  // 여기에 입력값()을 lin_x(속력), ang_z(조향각)로 변환하는 계산 알고리즘 삽입
  // 계산을 위한 파라미터는 임의로 수정/추가
  // float lin_x 0~110 = ;
  // float ang_z 0~180

  // 예)
  
  iBus_.readRx();
  
  lin_x = (iBus_.readChannel(velChannel)-1000);
  ang_z = (iBus_.readChannel(steerChannel)-1000);
  
  lin_x = constrain(lin_x, 0, 1000);
  
  lin_x = lin_x*lin_vel_ratio_;
  ang_z = ang_z*ang_ratio_;
  
  get_cmd_vel[0] = (byte)lin_x;
  get_cmd_vel[1] = (byte)ang_z;
  get_cmd_vel[2] = (byte)(iBus_.readChannel(manualChannel) / 1000 - 1);
  get_cmd_vel[3] = (byte)(iBus_.readChannel(reverseChannel) / 1000 - 1);
  get_cmd_vel[4] = (byte)(iBus_.readChannel(drivemodChannel) / 500 - 2);
  get_cmd_vel[5] = (byte)(iBus_.readChannel(estopChannel) / 1000 - 1);
}
