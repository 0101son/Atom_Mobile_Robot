#include <Arduino.h>
#include "IBus.h"

IBus ibus(Serial1); // Serial1 포트를 사용하는 IBus 객체 생성

void setup()
{
    Serial.begin(115200); // 디버그 출력을 위한 시리얼 통신 시작
    Serial.println("Starting IBus Reader...");

    ibus.init(); // IBus 통신을 위해 Serial1 포트 초기화
}

void loop()
{
    

    // 각 채널의 값을 읽고 시리얼 모니터에 출력
    for (int i = 0; i < IBUS_MAXCHANNELS; i++)
    {
        ibus.readRx(); // IBus 데이터 읽기
        int value = ibus.readChannel(i);
        Serial.print("Ch");
        Serial.print(i);
        Serial.print(": ");
        Serial.print(value);
        Serial.print("    ");
    }
    Serial.println();
    delay(1); // 1초마다 반복
}