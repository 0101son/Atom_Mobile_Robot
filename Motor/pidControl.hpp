#ifndef PIDCONTROL_H
#define PIDCONTROL_H

class PIDcontrol {
  float kp, kd, ki, umax;
  float eprev, eintegral;

public:
  PIDcontrol();

  void setParams(float kpIn, float kdIn, float kiIn, float umaxIn) {
    kp = kpIn; kd = kdIn; ki = kiIn; umax = umaxIn; 
  }
  void evalu(int value, int target, float deltaT, int &pwr, int &dir);

  void piControl();
  void pdControl();
  void pidControl();
};

#endif
