#ifndef MOBILE_ROBOTBOT_CONTROLLER_H_
#define MOBILE_ROBOTBOT_CONTROLLER_H_

#include "ibus.h"

class MobileRobotController
{
public:
    MobileRobotController();
    ~MobileRobotController();

    bool init(float max_lin_vel, float max_ang);

    void getRCdata(float *get_cmd_vel);

private:
    IBus iBus_;

    // 계산을 위한 파라미터는 임의로 수정/추가
    float max_lin_vel_;
    float max_ang_;
};

#endif