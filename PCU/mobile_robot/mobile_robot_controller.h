#ifndef MOBILE_ROBOTBOT_CONTROLLER_H_
#define MOBILE_ROBOTBOT_CONTROLLER_H_

#include "ibus.h"
#include <Arduino.h>

#define velChannel 2
#define steerChannel 0
#define manualChannel 4
#define reverseChannel 5
#define drivemodChannel 6
#define estopChannel 7

class MobileRobotController
{
  public:
    MobileRobotController();
    ~MobileRobotController();

    bool init(float max_lin_vel, float max_ang);

    void getRCdata(byte get_cmd_vel[]);

  private:
    IBus iBus_;

    // 계산을 위한 파라미터는 임의로 수정/추가
    float max_lin_vel_;
    float max_ang_;
    float lin_vel_ratio_;
    float ang_ratio_;
};

#endif
