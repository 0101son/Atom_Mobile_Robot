#include "PIDcontrol.hpp"

void PIDcontrol::evalu(int value, int target, float deltaT, int &pwr, int &dir) {
    float e = target - value;
    eintegral = eintegral + e*deltaT;
  
    float u = kp*e + ki*eintegral;

    // Set the motor speed and direction
    dir = 1;
    if (u<0) {
      dir = -1;
    }
    pwr = (int) fabs(u); // fabs = float + abs 절대값인데 소수에 붙이는거
    if(pwr > 255) {
      pwr = 255;
    }
  }
