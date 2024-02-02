/*
핀 연결
OpenCR의 UART2(4)(왼쪽) 포트와 앞쪽 담당 nano 연결
OpenCR의 UART1(2)(오른쪽) 포트와 뒤쪽 담당 nano 연결

T: Tx(송신)을 의미함. OpenCR의 Tx를 nano의 Rx와 연결
R: Rx(수신)을 의미함. OpenCR의 Rx를 nano의 Tx와 연결
V: Vcc(전원)을 의미함. 연결 안 해도 되는듯
G; GND(가 뭐냐)를 의미함. OpenCR의 GND와 nano의 GND를 연결 안 해도 작동하긴 함. 필수는 아닌듯  

nano에 프로그램 업로드가 안 될 때에는 OpenCR과 연결 분리한 뒤 업로드 시도하도록! 
nano는 Tx, Rx를 PC와 공유하기 때문에 외부 기기랑 연결되어있으면 업로드가 안될 수도 있다고 하네요

대부분 ChatGPT가 써준 거라 자세한 문법은 나도 살짝 모름
*/

void PCPrintStatus();
String inputString = "";
RCStatus rcStatus;

void setup()
{
  Serial.begin(9600);
  Serial4.begin(9600); // 앞쪽
  Serial2.begin(9600); // 뒤쪽
}

void loop()
{
  while (Serial4.available()) {  // 앞쪽 모터드라이버한테 값을 받았을 때
    char inChar = (char)Serial4.read();
    inputString += inChar;
    if (inChar == ' ') {
      rcStatus.setSpeedValue(FRONT_LEFT, inputString.toInt());  // 첫 번째로 받는 값이 왼쪽 바퀴
      inputString = "";
    } 
    else if (inChar == '\n') {
      rcStatus.setSpeedValue(FRONT_RIGHT, inputString.toInt());  // 두 번째로 받는 값이 오른쪽 바퀴
      inputString = "";
    }
  }
  while (Serial2.available()) {  // 뒤쪽 모터드라이버한테 값을 받았을 때
    char inChar = (char)Serial1.read();
    inputString += inChar;
    if (inChar == ' ') {
      rcStatus.setSpeedValue(REAR_LEFT, inputString.toInt());  // 첫 번째로 받는 값이 왼쪽 바퀴
      inputString = "";
    } 
    else if (inChar == '\n') {
      rcStatus.setSpeedValue(REAR_RIGHT, inputString.toInt());  // 두 번째로 받는 값이 오른쪽 바퀴
      inputString = "";
    }
  }
  PCPrintStatus();
  delay(500); 
}

void PCPrintStatus()
{
  Serial.print("Speeds: ");
  for (int i = 0; i < 4; ++i) {
    Serial.print(rcStatus.getSpeedValue(static_cast<SpeedField>(i)));
    Serial.print(" ");
  }
  Serial.print("Angles: ");
  for (int i = 0; i < 2; ++i) {
    Serial.print(rcStatus.getAngleValue(static_cast<AngleField>(i)));
    Serial.print(" ");
  }
  Serial.println();
}
