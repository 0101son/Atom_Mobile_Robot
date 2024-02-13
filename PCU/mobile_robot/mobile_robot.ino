#include <stdint.h>
#include <Arduino.h>
#include <RTOS.h>
#include "mobile_robot_controller.h"

/*******************************************************************************
   Declaration for controllers
 *******************************************************************************/
static MobileRobotController controllers;
static float max_linear_vel = 110.0, max_ang = 180.0;
static byte cmd_values[6] = {0};
static char packet[6] = {0};

osThreadId thread_id_transmit_data;
osThreadId thread_id_receive_data;

enum MortorLocation
{
  FRONT_LEFT = 0,
  FRONT_RIGHT,
  REAR_LEFT,
  REAR_RIGHT,
  MOTOR_NUM_MAX
};

typedef struct ControlItemVariables
{
  byte goal_rpm;
  byte servo_position;
  byte auto_;
  byte reverse;
  byte drive_mod;
  byte estop;

  int32_t present_rpm[MortorLocation::MOTOR_NUM_MAX];
} ControlItemVariables;

static ControlItemVariables control_items;


static void Thread_Transmit_Data(void const *argument)
{
  (void) argument;


  for (;;)
  {
    Serial2.print('z');
    Serial2.write(packet, 6);
    Serial2.print('{');

    Serial4.print('z');
    Serial4.write(packet, 6);
    Serial4.print('{');
  }
}

static void Thread_Receive_Data(void const *argument)
{
  (void) argument;


  pinMode(13, OUTPUT);

  for (;;)
  {
    controllers.getRCdata(cmd_values);

    control_items.goal_rpm = cmd_values[0];
    control_items.servo_position = cmd_values[1];
    control_items.auto_ = cmd_values[2];
    control_items.reverse = cmd_values[3];
    control_items.drive_mod = cmd_values[4];
    control_items.estop = cmd_values[5];

    packet[0] = control_items.goal_rpm;
    packet[1] = control_items.servo_position;
    packet[2] = control_items.auto_;
    packet[3] = control_items.reverse;
    packet[4] = control_items.drive_mod;
    packet[5] = control_items.estop;
  }
}


void setup()
{
  //  Serial.begin(115200);
  Serial2.begin(115200);
  Serial4.begin(115200);
  controllers.init(max_linear_vel, max_ang);

  osThreadDef(THREAD_NAME_TRANSMIT_DATA, Thread_Transmit_Data, osPriorityNormal, 0, 1024);
  osThreadDef(THREAD_NAME_RECEIVE_DATA,  Thread_Receive_Data,  osPriorityNormal, 0, 1024);

  // create thread
  thread_id_transmit_data = osThreadCreate(osThread(THREAD_NAME_TRANSMIT_DATA), NULL);
  thread_id_receive_data  = osThreadCreate(osThread(THREAD_NAME_RECEIVE_DATA), NULL);
  
  // start kernel
  osKernelStart();
}
