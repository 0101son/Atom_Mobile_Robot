#include <Arduino.h>
#include "Mobile_Robot_Controller.h"

MobileRobotController robotController;

void setup()
{
    Serial.begin(9600);
    Serial.println("Initializing Mobile Robot Controller...");

    // 여기에서 max_lin_vel과 max_ang 값을 적절히 설정하세요.
    float max_lin_vel = 110.0; // 예시 값
    float max_ang = 180.0;     // 예시 값

    if (!robotController.init(max_lin_vel, max_ang))
    {
        Serial.println("Failed to initialize the robot controller!");
        while (1)
            ; // 초기화 실패 시 무한 루프
    }
}

void loop()
{
    float cmd_vel[2]; // [0]에는 선속도, [1]에는 각속도가 저장될 예정

    robotController.getRCdata(cmd_vel); // RC 데이터 읽기

    // 읽은 데이터 출력
    Serial.print(cmd_vel[0]);
    Serial.print(" ");
    Serial.print(cmd_vel[1]);
    Serial.print(" ");
    Serial.println();
}
