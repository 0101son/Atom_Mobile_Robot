#include "serial_communication.h"
#include <Arduino.h>

void parseData(char packet[]) {
    char* token = strtok(packet, ",");  // 쉼표를 구분자로 사용하여 문자열을 자름
    int count = 0;  // 데이터 개수를 세는 변수
    int data[4];
    while (token != NULL && count < data_count) {
      data[count] = atoi(token);  // 문자열을 정수로 변환
      token = strtok(NULL, " ");  // 다음 데이터를 자르기 위해 NULL을 전달하여 재사용
      count++;
    }
    received_RPM = data[0];
    received_steering = data[1];
    received_motorDir = data[2];
    received_steerMode = data[3];
}

void serialEvent() {
  if (Serial.available() >= packetLength) {  // 수신 버퍼에 패킷의 길이만큼 데이터가 있는지 확인
    char packet[packetLength + 1];  // 패킷을 저장할 문자열 배열
    Serial.readBytes(packet, packetLength);  // 패킷 데이터를 읽어서 배열에 저장
    packet[packetLength] = '\0';  // 문자열 끝을 표시하기 위해 널 문자 추가
    parseData(packet);
  }
}

void sendData() {
  Serial.print(velocity[0]);
  Serial.print(" ");
  Serial.print(velocity[1]);
  Serial.println();
}
