

# 목차
- [2.1. setup()](#21-setup)
- [2.2. loop()](#22-loop)
- [2.3. Subscriber(Callback)](#23-subscribercallback)
    - [2.3.1. *commandVelocity*Callback()](#231-commandvelocitycallback)
    - [2.3.2. *sound*Callback()](#232-soundcallback)
    - [2.3.3. *motorPower*Callback()](#233-motorpowercallback)
    - [2.3.4. *reset*Callback()](#234-resetcallback)
- [2.4. Publisher(publish-Msg)](#24-publisherpublish-msg)
    - [2.4.1. publish*CmdVelFromRC100*Msg()](#241-publishcmdvelfromrc100msg)
    - [2.4.2. publish*Imu*Msg()](#242-publishimumsg)
    - [2.4.3. publish*Mag*Msg()](#243-publishmagmsg)
    - [2.4.4. publish*SensorState*Msg()](#244-publishsensorstatemsg)
    - [2.4.5. publish*VersionInfo*Msg()](#245-publishversioninfomsg)
    - [2.4.6. publish*BatteryState*Msg()](#246-publishbatterystatemsg)
    - [2.4.7. publish*DriveInformation*()](#247-publishdriveinformation)
- [2.5. update](#25-update)
    - [2.5.1. update*TFPrefix*()](#251-updatetfprefix)
    - [2.5.2. update*Odometry*()](#252-updateodometry)
    - [2.5.3. update*TF*()](#253-updatetf)
    - [2.5.4. update*MotorInfo*()](#254-updatemotorinfo)
    - [2.5.5. update*Variable*()](#255-updatevariable)
    - [2.5.6. update*Time*()](#256-updatetime)
    - [2.5.7. update*GyroCali*()](#257-updategyrocali)
    - [2.5.8. update*GoalVelocity*()](#258-updategoalvelocity)
- [2.6. calcOdometry()](#26-calcodometry)
- [2.7. driveTest()](#27-drivetest)
- [2.8. waitForSerialLink()](#28-waitforseriallink)
- [2.9. rosNow()](#29-rosnow)
- [2.10. addMicros()](#210-addmicros)
- [2.11. sendLogMsg()](#211-sendlogmsg)
- [2.12. init](#212-init)
    - [2.12.1. initOdom()](#2121-initodom)
    - [2.12.2. initJointStates()](#2122-initjointstates)
- [2.13. sendDebuglog()](#213-senddebuglog)


---

# 1. 요약
이 코드는 ROS(로봇 운영 체제) 기반의 TurtleBot3 로봇의 핵심 구성 요소와 기능들을 설정하고 제어하는 데 사용됩니다. 주요 기능은 다음과 같습니다:

1. **시리얼 통신 설정**: 디버깅을 위한 시리얼 통신과 ROS 노드 핸들 초기화를 포함합니다.

2. **ROS 토픽 구독 및 발행**: 여러 ROS 토픽들을 구독하고 발행합니다 (예: cmd_vel, sensor_state, imu 등).

3. **센서 및 액추에이터 초기화**: IMU(관성 측정 장치), 모터 드라이버 등의 센서와 액추에이터를 초기화합니다.

4. **주기적 업데이트**: 루프 함수에서 주기적으로 로봇의 상태를 업데이트하고, 각종 센서 데이터를 수집 및 발행합니다.

5. **속도 제어**: 명령된 속도(cmd_vel)에 따라 로봇의 선형 및 각속도를 제어합니다.

6. **오도메트리 및 TF(Transformations) 업데이트**: 로봇의 위치 및 자세 정보를 계산하고, TF를 통해 다른 노드와 공유합니다.

7. **콜백 함수**: 다양한 ROS 메시지에 대한 콜백 함수를 구현하여, 외부 명령에 대응합니다.

8. **진단 및 디버깅**: 로봇의 상태를 진단하고 LED 상태를 표시하며, 필요한 경우 디버깅 정보를 출력합니다.

9. **보조 기능들**: 버튼 입력에 따른 시험 주행, 자이로 센서의 보정, 로그 메시지 전송 등의 추가적인 기능들을 포함합니다.

이 코드는 TurtleBot3 로봇을 위한 포괄적인 ROS 기반 펌웨어로, 로봇의 주요 기능을 제어하고 센서 데이터를 처리하는 데 중요한 역할을 합니다.

---

# 2. 분석

### 2.1. setup()
@line 21
``` ino
/*******************************************************************************
* Setup function
*******************************************************************************/
void setup()
{
  DEBUG_SERIAL.begin(57600);

  // Initialize ROS node handle, advertise and subscribe the topics
  nh.initNode();
  nh.getHardware()->setBaud(115200);

  nh.subscribe(cmd_vel_sub);
  nh.subscribe(sound_sub);
  nh.subscribe(motor_power_sub);
  nh.subscribe(reset_sub);

  nh.advertise(sensor_state_pub);  
  nh.advertise(version_info_pub);
  nh.advertise(imu_pub);
  nh.advertise(cmd_vel_rc100_pub);
  nh.advertise(odom_pub);
  nh.advertise(joint_states_pub);
  nh.advertise(battery_state_pub);
  nh.advertise(mag_pub);

  tf_broadcaster.init(nh);

  // Setting for Dynamixel motors
  motor_driver.init(NAME);

  // Setting for IMU
  sensors.init();

  // Init diagnosis
  diagnosis.init();

  // Setting for ROBOTIS RC100 remote controller and cmd_vel
  controllers.init(MAX_LINEAR_VELOCITY, MAX_ANGULAR_VELOCITY);

  // Setting for SLAM and navigation (odometry, joint states, TF)
  initOdom();

  initJointStates();

  prev_update_time = millis();

  pinMode(LED_WORKING_CHECK, OUTPUT);

  setup_end = true;
}
```

이 코드의 `setup` 함수는 TurtleBot3 로봇의 초기 설정을 위한 함수입니다. 주요 기능과 각 부분의 역할은 다음과 같습니다:

1. **시리얼 통신 초기화**: `DEBUG_SERIAL.begin(57600)`을 통해 디버그 목적의 시리얼 통신을 57600bps로 설정합니다.

2. **ROS 노드 초기화**:
   - `nh.initNode()`를 통해 ROS 노드를 초기화합니다.
   - `nh.getHardware()->setBaud(115200)`로 ROS 시리얼 통신 속도를 115200bps로 설정합니다.

3. **ROS 토픽 구독 및 발행**:
   - `nh.subscribe()`를 사용하여 `cmd_vel`, `sound`, `motor_power`, `reset` 등의 토픽을 구독합니다.
   - `nh.advertise()`를 사용하여 `sensor_state`, `version_info`, `imu`, `cmd_vel_rc100`, `odom`, `joint_states`, `battery_state`, `mag` 등의 토픽을 발행할 준비를 합니다.

4. **TF 브로드캐스터 초기화**: `tf_broadcaster.init(nh)`를 통해 ROS의 TF(Transformation) 브로드캐스터를 초기화합니다. 이는 로봇의 위치 및 자세 정보를 다른 노드와 공유하기 위해 사용됩니다.

5. **Dynamixel 모터 설정**: `motor_driver.init(NAME)`를 통해 Dynamixel 모터 드라이버를 초기화합니다.

6. **IMU(관성 측정 장치) 설정**: `sensors.init()`를 호출하여 IMU 센서를 초기화합니다.

7. **진단 모듈 초기화**: `diagnosis.init()`를 통해 로봇의 상태 진단을 위한 모듈을 초기화합니다.

8. **RC100 리모트 컨트롤러 및 cmd_vel 설정**: `controllers.init(MAX_LINEAR_VELOCITY, MAX_ANGULAR_VELOCITY)`를 사용하여 ROBOTIS RC100 리모트 컨트롤러 및 로봇의 최대 선형 및 각속도를 설정합니다.

9. **SLAM 및 내비게이션 설정**:
   - `initOdom()`을 호출하여 오도메트리(위치 추적)를 위한 초기 설정을 수행합니다.
   - `initJointStates()`를 호출하여 관절 상태 정보를 위한 초기 설정을 수행합니다.

10. **타이머 초기화**: `prev_update_time = millis()`를 사용하여 이전 업데이트 시간을 기록합니다.

11. **LED 작동 상태 확인 핀 설정**: `pinMode(LED_WORKING_CHECK, OUTPUT)`을 통해 LED 작동 상태를 확인하기 위한 핀을 출력 모드로 설정합니다.

12. **설정 완료 플래그**: `setup_end = true`를 통해 설정이 완료되었음을 나타내는 플래그를 설정합니다.

이 함수는 로봇이 처음 켜졌을 때 한 번 실행되며, 로봇의 핵심적인 하드웨어와 소프트웨어 구성 요소들을 초기화하고 준비하는 역할을 합니다.

---
### 2.2. loop()
@line 72
``` ino
/*******************************************************************************
* Loop function
*******************************************************************************/
void loop()
{
  uint32_t t = millis();
  updateTime();
  updateVariable(nh.connected());
  updateTFPrefix(nh.connected());

  if ((t-tTime[0]) >= (1000 / CONTROL_MOTOR_SPEED_FREQUENCY))
  {
    updateGoalVelocity();
    if ((t-tTime[6]) > CONTROL_MOTOR_TIMEOUT) 
    {
      motor_driver.controlMotor(WHEEL_RADIUS, WHEEL_SEPARATION, zero_velocity);
    } 
    else {
      motor_driver.controlMotor(WHEEL_RADIUS, WHEEL_SEPARATION, goal_velocity);
    }
    tTime[0] = t;
  }

  if ((t-tTime[1]) >= (1000 / CMD_VEL_PUBLISH_FREQUENCY))
  {
    publishCmdVelFromRC100Msg();
    tTime[1] = t;
  }

  if ((t-tTime[2]) >= (1000 / DRIVE_INFORMATION_PUBLISH_FREQUENCY))
  {
    publishSensorStateMsg();
    publishBatteryStateMsg();
    publishDriveInformation();
    tTime[2] = t;
  }

  if ((t-tTime[3]) >= (1000 / IMU_PUBLISH_FREQUENCY))
  {
    publishImuMsg();
    publishMagMsg();
    tTime[3] = t;
  }

  if ((t-tTime[4]) >= (1000 / VERSION_INFORMATION_PUBLISH_FREQUENCY))
  {
    publishVersionInfoMsg();
    tTime[4] = t;
  }

#ifdef DEBUG
  if ((t-tTime[5]) >= (1000 / DEBUG_LOG_FREQUENCY))
  {
    sendDebuglog();
    tTime[5] = t;
  }
#endif

  // Send log message after ROS connection
  sendLogMsg();

  // Receive data from RC100 
  bool clicked_state = controllers.getRCdata(goal_velocity_from_rc100);
  if (clicked_state == true)  
    tTime[6] = millis();

  // Check push button pressed for simple test drive
  driveTest(diagnosis.getButtonPress(3000));

  // Update the IMU unit
  sensors.updateIMU();

  // TODO
  // Update sonar data
  // sensors.updateSonar(t);

  // Start Gyro Calibration after ROS connection
  updateGyroCali(nh.connected());

  // Show LED status
  diagnosis.showLedStatus(nh.connected());

  // Update Voltage
  battery_state = diagnosis.updateVoltageCheck(setup_end);

  // Call all the callbacks waiting to be called at that point in time
  nh.spinOnce();

  // Wait the serial link time to process
  waitForSerialLink(nh.connected());
}
```

`loop` 함수는 TurtleBot3 로봇의 주요 작업을 지속적으로 수행하는 무한 루프 함수입니다. 여기에는 여러 센서의 데이터를 읽고, 모터를 제어하며, ROS 메시지를 발행하는 등의 작업이 포함됩니다. 각 부분의 역할은 다음과 같습니다:

1. **현재 시간 기록**: `uint32_t t = millis();`로 현재 시간을 밀리초 단위로 기록합니다.

2. **시간 및 변수 업데이트**:
   - `updateTime()`을 호출하여 현재 시간을 업데이트합니다.
   - `updateVariable(nh.connected())`로 ROS 연결 상태에 따라 변수를 업데이트합니다.
   - `updateTFPrefix(nh.connected())`로 ROS 연결 상태에 따라 TF(Transformation) 접두사를 업데이트합니다.

3. **모터 제어**:
   - 모터 속도 제어 주기를 확인하고, 필요한 경우 `updateGoalVelocity()`를 호출하여 목표 속도를 업데이트합니다.
   - 모터 제어 타임아웃을 체크하여, 타임아웃 시 정지하거나 목표 속도에 따라 모터를 제어합니다.

4. **ROS 메시지 발행**:
   - 다양한 주기에 따라 `publishCmdVelFromRC100Msg()`, `publishSensorStateMsg()`, `publishBatteryStateMsg()`, `publishDriveInformation()`, `publishImuMsg()`, `publishMagMsg()`, `publishVersionInfoMsg()` 등을 호출하여 각종 센서 데이터와 상태 정보를 ROS 토픽으로 발행합니다.

5. **디버그 로그**:
   - `#ifdef DEBUG` 조건문 아래에서 디버그 모드가 활성화되어 있을 경우 `sendDebuglog()`를 호출하여 디버그 로그를 출력합니다.

6. **RC100 데이터 수신 및 처리**:
   - `controllers.getRCdata()`를 호출하여 RC100 리모트 컨트롤러로부터 데이터를 수신하고, 클릭 상태에 따라 처리합니다.

7. **버튼 입력에 따른 테스트 드라이브**:
   - `driveTest()` 함수를 호출하여 버튼 입력에 따라 간단한 테스트 드라이브를 수행합니다.

8. **센서 업데이트**:
   - `sensors.updateIMU()`를 호출하여 IMU 센서를 업데이트합니다.
   - 소나 데이터 업데이트는 구현 예정(`TODO`)으로 표시되어 있습니다.

9. **자이로 센서 보정 및 LED 상태 표시**:
   - `updateGyroCali()`를 호출하여 자이로 센서의 보정을 시작합니다.
   - `diagnosis.showLedStatus()`를 통해 LED 상태를 표시합니다.

10. **배터리 상태 업데이트**: `diagnosis.updateVoltageCheck()`를 호출하여 배터리 상태를 업데이트합니다.

11. **ROS 콜백 처리**: `nh.spinOnce()`를 호출하여 대기 중인 ROS 콜백 함수들을 실행합니다.

12. **시리얼 링크 대기**: `waitForSerialLink()`을 호출하여 시리얼 링크의 처리 시간을 기다립니다.

이 함수는 로봇이 작동하는 동안 지속적으로 실행되며, 로봇의 센서 데이터 읽기, 모터 제어, ROS 메시지 처리 등을 주기적으로 수행합니다.

---

### 2.3. Subscriber(Callback)

함수명에 "callback"이 포함된 함수들은 ROS(로봇 운영 체제) 프로그래밍에서 주로 사용되는 콜백 함수들입니다. 이러한 콜백 함수들은 ROS의 통신 메커니즘의 핵심 부분으로, 특정 유형의 메시지를 수신할 때마다 자동으로 호출됩니다. 각 콜백 함수의 공통적인 특징과 역할은 다음과 같습니다:

1. **자동 호출**: 콜백 함수들은 ROS 노드가 특정 토픽의 메시지를 받을 때 자동으로 호출됩니다. 이는 ROS의 이벤트 기반 프로그래밍 패러다임에 따른 것입니다.

2. **특정 메시지 처리**: 각 콜백 함수는 특정 종류의 메시지를 처리하기 위해 설계되어 있습니다. 예를 들어, `commandVelocityCallback`은 속도 제어 명령을, `soundCallback`은 소리 관련 명령을, `motorPowerCallback`은 모터 전원 제어 명령을 처리합니다.

3. **매개변수**: 콜백 함수들은 각각의 메시지 타입에 맞는 매개변수를 가집니다. 이 매개변수들은 수신된 메시지의 데이터를 포함하며, 함수 내에서 이 데이터에 따른 로직을 수행합니다.

4. **비동기 실행**: 콜백 함수들은 메시지가 도착할 때마다 비동기적으로 실행됩니다. 즉, 프로그램의 다른 부분이 실행되는 동안에도 독립적으로 호출되고 작동합니다.

5. **ROS 노드와의 통합**: 이 함수들은 ROS 노드에 등록되어, 해당 노드가 구독하는 특정 토픽에 대한 메시지를 처리합니다.

6. **로봇의 행동 제어**: 이 콜백 함수들은 로봇의 다양한 기능을 제어하는 데 사용됩니다. 예를 들어, 모터의 속도 설정, 소리 재생, 센서 데이터 처리 등이 이에 해당합니다.

이러한 콜백 함수들은 ROS 기반의 로봇 프로그래밍에서 메시지 기반의 통신과 로봇의 반응적인 행동 제어를 가능하게 하는 중요한 요소입니다.

---
##### 2.3.1. *commandVelocity*Callback()
@line 164
``` ino
/*******************************************************************************
* Callback function for cmd_vel msg
*******************************************************************************/
void commandVelocityCallback(const geometry_msgs::Twist& cmd_vel_msg)
{
  goal_velocity_from_cmd[LINEAR]  = cmd_vel_msg.linear.x;
  goal_velocity_from_cmd[ANGULAR] = cmd_vel_msg.angular.z;

  goal_velocity_from_cmd[LINEAR]  = constrain(goal_velocity_from_cmd[LINEAR],  MIN_LINEAR_VELOCITY, MAX_LINEAR_VELOCITY);
  goal_velocity_from_cmd[ANGULAR] = constrain(goal_velocity_from_cmd[ANGULAR], MIN_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY);
  tTime[6] = millis();
}
```

`commandVelocityCallback` 함수는 ROS 메시지 `cmd_vel`을 받을 때 호출되는 콜백 함수입니다. 이 함수는 TurtleBot3 로봇의 선형 및 각속도 목표값을 설정합니다. 구체적으로 다음과 같이 작동합니다:

1. **매개변수**: 
   - `const geometry_msgs::Twist& cmd_vel_msg`: `geometry_msgs/Twist` 타입의 ROS 메시지로, 로봇의 선형 및 각속도를 나타냅니다.

2. **선형 및 각속도 설정**:
   - `cmd_vel_msg.linear.x`: 메시지에서 로봇의 선형 속도(x축) 값을 가져옵니다.
   - `cmd_vel_msg.angular.z`: 메시지에서 로봇의 각속도(z축) 값을 가져옵니다.
   - 이 값들은 `goal_velocity_from_cmd` 배열에 각각 `LINEAR` 및 `ANGULAR` 인덱스로 저장됩니다.

3. **속도 제한**:
   - `constrain` 함수를 사용하여, 로봇의 선형 및 각속도가 최소 및 최대 속도 한계 (`MIN_LINEAR_VELOCITY`, `MAX_LINEAR_VELOCITY`, `MIN_ANGULAR_VELOCITY`, `MAX_ANGULAR_VELOCITY`) 내에 있도록 제한합니다. 이는 로봇이 안전하게 움직일 수 있도록 하기 위함입니다.

4. **시간 기록**:
   - `tTime[6] = millis();`를 통해 명령을 받은 시간을 기록합니다. 이 시간은 나중에 모터의 제어 로직에서 타임아웃을 판단하는 데 사용될 수 있습니다.

이 콜백 함수는 ROS 시스템에서 `cmd_vel` 메시지를 통해 로봇에 움직임 명령을 내릴 때마다 호출되어 로봇의 움직임을 제어하는 데 중요한 역할을 합니다.

---

##### 2.3.2. *sound*Callback()
@line 177
``` ino
/*******************************************************************************
* Callback function for sound msg
*******************************************************************************/
void soundCallback(const turtlebot3_msgs::Sound& sound_msg)
{
  sensors.makeSound(sound_msg.value);
}
```

`soundCallback` 함수는 ROS 시스템에서 소리 메시지(`sound_msg`)를 받았을 때 호출되는 콜백 함수입니다. 이 함수는 TurtleBot3 로봇이 특정 소리를 내도록 하는 데 사용됩니다. 함수의 작동 방식은 다음과 같습니다:

1. **매개변수**:
   - `const turtlebot3_msgs::Sound& sound_msg`: `turtlebot3_msgs/Sound` 타입의 ROS 메시지로, 소리를 나타내는 값이 포함되어 있습니다.

2. **소리 재생**:
   - `sensors.makeSound(sound_msg.value)`: `makeSound` 메서드를 호출하여, `sound_msg`에서 받은 값(`value`)에 해당하는 소리를 재생합니다. 이 값은 특정 소리나 경고음을 나타낼 수 있으며, `sensors` 객체(아마도 로봇의 센서 시스템을 제어하는 클래스의 인스턴스)가 이를 처리합니다.

이 함수의 주요 목적은 외부 ROS 노드로부터 소리 관련 명령을 받고, 해당 명령에 따라 로봇이 소리를 내도록 하는 것입니다. 예를 들어, 로봇이 특정 상황을 알리거나 사용자의 주의를 끌기 위해 사용될 수 있습니다.

---

##### 2.3.3. *motorPower*Callback()
@line 185
``` ino
/*******************************************************************************
* Callback function for motor_power msg
*******************************************************************************/
void motorPowerCallback(const std_msgs::Bool& power_msg)
{
  bool dxl_power = power_msg.data;

  motor_driver.setTorque(dxl_power);
}
```

`motorPowerCallback` 함수는 ROS에서 `motor_power` 메시지를 받았을 때 호출되는 콜백 함수입니다. 이 함수는 TurtleBot3 로봇의 모터 동력을 제어하는 데 사용됩니다. 함수의 작동 방식은 다음과 같습니다:

1. **매개변수**:
   - `const std_msgs::Bool& power_msg`: `std_msgs/Bool` 타입의 ROS 메시지로, 모터의 전원 상태(켜짐/꺼짐)를 나타냅니다.

2. **모터 전원 제어**:
   - `bool dxl_power = power_msg.data;`: 메시지에서 모터 전원 상태를 나타내는 불리언 값을 추출합니다.
   - `motor_driver.setTorque(dxl_power);`: `setTorque` 메서드를 호출하여 추출한 전원 상태(`dxl_power`)에 따라 모터의 토크(즉, 동력)를 설정합니다. 이 값이 `true`이면 모터에 동력을 공급하고, `false`이면 모터를 꺼서 동력을 차단합니다.

이 콜백 함수의 주요 목적은 외부 ROS 노드로부터 모터 전원 관련 명령을 받고, 해당 명령에 따라 로봇의 모터 전원을 켜거나 끄는 것입니다. 예를 들어, 로봇이 작업을 시작하거나 멈출 때 사용될 수 있습니다.

---

##### 2.3.4. *reset*Callback()
@line 195
``` ino
/*******************************************************************************
* Callback function for reset msg
*******************************************************************************/
void resetCallback(const std_msgs::Empty& reset_msg)
{ 
  char log_msg[50];

  (void)(reset_msg);

  sprintf(log_msg, "Start Calibration of Gyro");
  nh.loginfo(log_msg);

  sensors.calibrationGyro();

  sprintf(log_msg, "Calibration End");
  nh.loginfo(log_msg);

  initOdom();

  sprintf(log_msg, "Reset Odometry");
  nh.loginfo(log_msg);  
}
```

`resetCallback` 함수는 ROS에서 `reset` 메시지를 받았을 때 호출되는 콜백 함수입니다. 이 함수는 로봇의 자이로스코프 보정과 오도메트리(위치 추적 데이터) 초기화를 수행합니다. 함수의 작동 방식은 다음과 같습니다:

1. **매개변수**:
   - `const std_msgs::Empty& reset_msg`: `std_msgs/Empty` 타입의 ROS 메시지로, 별도의 데이터를 포함하지 않습니다. 이 메시지는 단순히 리셋 명령을 나타냅니다.

2. **자이로스코프 보정**:
   - `sensors.calibrationGyro()`: 로봇의 자이로스코프 센서를 보정하는 메서드를 호출합니다. 자이로스코프는 로봇의 방향과 회전을 감지하는 데 사용되므로, 정확한 데이터를 위해 주기적인 보정이 필요합니다.
   - `sprintf(log_msg, "Start Calibration of Gyro");`와 `sprintf(log_msg, "Calibration End");`를 사용하여 로그 메시지를 생성하고, `nh.loginfo(log_msg);`를 통해 ROS 로그에 해당 메시지를 기록합니다. 이는 보정 시작과 종료를 로그에 남깁니다.

3. **오도메트리 초기화**:
   - `initOdom()`: 오도메트리 데이터를 초기화하는 함수를 호출합니다. 오도메트리는 로봇의 위치와 이동 경로를 추적하는 데 사용되며, 리셋 시에 이 데이터를 초기 상태로 되돌리는 것이 중요합니다.
   - `sprintf(log_msg, "Reset Odometry");`와 `nh.loginfo(log_msg);`를 통해 오도메트리 리셋을 로그에 기록합니다.

이 콜백 함수는 ROS 시스템으로부터 리셋 명령을 받았을 때 로봇의 주요 센서와 데이터를 초기 상태로 되돌리는 데 중요한 역할을 합니다. 이를 통해 로봇은 정확한 센서 데이터와 위치 추적을 유지할 수 있습니다.

---




### 2.4. Publisher(publish-Msg)

함수명에 "publish-Msg"가 포함된 함수들은 ROS(로봇 운영 체제)에서 사용되는 메시지 발행(publishing) 관련 함수들입니다. 이러한 함수들은 로봇이나 센서의 상태, 데이터 또는 다른 유형의 정보를 ROS 네트워크 상의 다른 노드들과 공유하기 위해 사용됩니다. 각 함수의 공통적인 특징과 역할은 다음과 같습니다:

1. **ROS 메시지 생성**: 이 함수들은 특정한 데이터나 상태 정보를 ROS 메시지 형식으로 포맷합니다. 메시지 형식은 `std_msgs`, `geometry_msgs`, `sensor_msgs` 등 ROS 표준 메시지 타입을 따릅니다.

2. **데이터 패키징**: 함수들은 로봇의 센서 데이터, 상태 정보, 명령 등을 적절한 메시지 타입에 맞게 변환하고 패키징합니다.

3. **메시지 발행**: 생성된 메시지는 ROS 통신 시스템을 통해 발행되며, 다른 노드들이 이 메시지를 구독하여 사용할 수 있습니다.

4. **ROS 토픽과의 연동**: 각 함수는 특정 ROS 토픽에 메시지를 발행합니다. 토픽은 로봇의 다양한 정보를 주제별로 구분하는 데 사용되며, 네트워크 상의 다른 노드들은 이러한 토픽을 구독할 수 있습니다.

5. **정보의 실시간 전달**: 이 함수들은 로봇의 상태나 센서 데이터가 변경될 때마다 호출되어, 실시간으로 정보를 네트워크에 공유합니다.

6. **시스템 간 통합**: 이 메시지 발행 함수들은 로봇의 센서 데이터, 제어 명령, 상태 정보 등을 다른 ROS 노드나 시스템과 통합하는 데 중요한 역할을 합니다. 예를 들어, 센서 데이터를 분석하는 노드, 로봇의 동작을 제어하는 노드 등이 있을 수 있습니다.

이러한 함수들은 ROS 기반의 로봇 프로그래밍에서 중요한 역할을 하며, 로봇과 시스템 간의 효율적인 데이터 교환 및 커뮤니케이션을 가능하게 합니다.

---
##### 2.4.1. publish*CmdVelFromRC100*Msg()
@line 218

---
##### 2.4.2. publish*Imu*Msg()
@line 229

---
##### 2.4.3. publish*Mag*Msg()
@line 242

---
##### 2.4.4. publish*SensorState*Msg()
@line 255

---
##### 2.4.5. publish*VersionInfo*Msg()

---
##### 2.4.6. publish*BatteryState*Msg()

---

##### 2.4.7. publish*DriveInformation*()

---

### 2.5. update

함수명에 "update"가 포함된 함수들은 주로 로봇의 상태, 센서 데이터, 설정 또는 내부 변수를 갱신하는 데 사용됩니다. 이러한 함수들은 ROS(로봇 운영 체제) 기반의 로봇 프로그래밍에서 특히 중요한 역할을 수행합니다. 각 함수의 공통적인 특징과 역할은 다음과 같습니다:

1. **상태 갱신**: 이 함수들은 로봇의 다양한 내부 상태나 변수를 최신 상태로 업데이트합니다. 예를 들어, 센서 값, 위치 데이터, 속도 등이 이에 해당할 수 있습니다.

2. **지속적인 모니터링**: 로봇 시스템에서 변화하는 조건이나 데이터를 지속적으로 모니터링하고, 이에 따라 필요한 조정을 자동으로 수행합니다.

3. **센서 데이터 처리**: 센서로부터 입력된 데이터를 처리하고, 이를 기반으로 로봇의 행동이나 상태를 조정합니다.

4. **환경 변화에 대한 반응**: 로봇의 운영 환경이나 조건이 변할 때 이에 적절히 대응하기 위해 필요한 조정을 수행합니다.

5. **내부 로직 수행**: 특정 조건이나 기준에 따라 로봇의 내부 로직을 수행하거나 수정합니다.

6. **시스템 통합 및 연동**: 로봇의 다양한 구성 요소나 시스템 간의 연동을 위해 필요한 정보를 갱신하고 조정합니다.

이러한 함수들은 로봇이 신뢰성 있고 효율적으로 작동하도록 하며, 실시간으로 변화하는 운영 환경에 빠르고 정확하게 대응할 수 있게 합니다. 로봇의 자율성과 반응성을 향상시키는 데 중요한 역할을 합니다.

---

##### 2.5.1. updatez*TFPrefix*()

---

##### 2.5.2. update*Odometry*()

---

##### 2.5.3. update*TF*()

---

##### 2.5.4. update*MotorInfo*()

---



##### 2.5.5. update*Variable*()

---



##### 2.5.6. update*Time*()

---



##### 2.5.7. update*GyroCali*()

---



##### 2.5.8. update*GoalVelocity*()

---


### 2.6. calcOdometry()

---
### 2.7. driveTest()

---
### 2.8. waitForSerialLink()

---
### 2.9. rosNow()

---
### 2.10. addMicros()

---

### 2.11. sendLogMsg()

---

### 2.12. init
initialize, 즉 초기화 함수 입니다.

---
##### 2.12.1. initOdom()

---

##### 2.12.2. initJointStates()

---

### 2.13. sendDebuglog()
디버깅을 위해 시스템의 실시간 정보를 출력하는 함수 입니다.

---
