#ifndef IBUS_H_
#define IBUS_H_

#include <Arduino.h>

#define IBUS_BUFFSIZE 32
#define IBUS_MAXCHANNELS 10

class IBus
{
public:
    IBus(HardwareSerial& serial) : serialRef(&serial) {} // 생성자 수정
    bool init(HardwareSerial &serial);
    int readChannel(uint8_t channelNr);

private:
    HardwareSerial* serialRef; // 시리얼 참조
    uint8_t ibusIndex = 0;
    uint8_t ibus[IBUS_BUFFSIZE] = {0};
    uint16_t rcValue[IBUS_MAXCHANNELS];
    boolean rxFrameDone = false;
    int channelWidths[IBUS_MAXCHANNELS];

    void readRx(); // 시리얼 데이터 읽기
};

#endif