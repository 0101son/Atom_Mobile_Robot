`Turtlebot3Sensor` 클래스는 TurtleBot3 로봇의 다양한 센서를 관리합니다. 이 클래스는 로봇의 IMU(Inertial Measurement Unit), 충돌 방지 센서, 적외선 센서, 초음파 센서, LED 및 배터리 전압 등을 초기화하고, 이를 업데이트하며, 해당 데이터를 처리하는 기능을 포함하고 있습니다.

### 클래스 구조 및 주요 기능

1. **초기화 (`bool Turtlebot3Sensor::init`):**
   - 센서들을 초기화하고 IMU를 시작합니다. 초기화가 성공적으로 이루어졌는지 확인합니다.

2. **IMU 관련 함수 (`void initIMU`, `void updateIMU`, `void calibrationGyro`):**
   - IMU를 초기화하고, 데이터를 업데이트하며, 자이로스코프를 보정합니다.

3. **IMU 데이터 가져오기 (`getImuAngularVelocity`, `getImuLinearAcc`, `getImuMagnetic`, `getOrientation`):**
   - 각속도, 선형가속도, 자기장 데이터 및 IMU의 방향(쿼터니언)을 반환합니다.

4. **전압 체크 (`float checkVoltage`):**
   - 로봇의 배터리 전압을 확인합니다.

5. **버튼 입력 확인 (`uint8_t checkPushButton`):**
   - 로봇에 탑재된 버튼의 상태를 확인합니다.

6. **멜로디 재생 (`void onMelody`, `void makeMelody`):**
   - 지정된 멜로디를 재생합니다.

7. **충돌 방지 센서 (`void initBumper`, `uint8_t checkPushBumper`, `getBumper1State`, `getBumper2State`):**
   - 충돌 방지 센서를 초기화하고, 상태를 확인합니다.

8. **적외선 센서 및 초음파 센서 (`void initIR`, `float getIRsensorData`, `void initSonar`, `void updateSonar`, `float getSonarData`):**
   - 적외선 센서 및 초음파 센서를 초기화하고, 해당 데이터를 업데이트 및 반환합니다.

9. **LED 제어 (`void initLED`, `void setLedPattern`):**
   - LED를 초기화하고, 로봇의 이동 상태에 따라 LED 패턴을 설정합니다.

### 주요 포인트

- **다양한 센서의 통합 관리**: IMU, 충돌 방지 센서, 적외선 센서, 초음파 센서 등 다양한 센서를 관리하고 데이터를 처리합니다.
- **환경 인식 및 반응**: 로봇이 주변 환경을 인식하고 이에 반응할 수 있도록 센서 데이터를 활용합니다.
- **사용자 인터랙션**: 멜로디 재생 및 LED 패턴을 통해 사용자와의 상호작용을 지원합니다.
- **자이로스코프 보정**: 정확한 이동 및 위치 추정을 위해 IMU의 자이로스코프를 보정합니다.

이 클래스는 TurtleBot3 로봇의 다양한 센서 데이터를 효율적으로 관리하고, 로봇의 인식 및 반응 능력을 향상시키는 데 중요한 역할을 합니다.
