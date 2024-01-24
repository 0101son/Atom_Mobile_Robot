#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

#include <Arduino.h>

class LowPassFilter {
private:
    float xn1, yn1, k;
    float xn, yn;
public:
    LowPassFilter();
    
};

#endif
