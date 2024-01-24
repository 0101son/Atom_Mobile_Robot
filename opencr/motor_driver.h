
#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <Arduino.h>

#define TORQUE_ENABLE ControlTableItem::TORQUE_ENABLE

enum MortorLocation{
  LEFT = 0,
  RIGHT,
  MOTOR_NUM_MAX
};

enum VelocityType{
  LINEAR = 0,
  ANGULAR,
  TYPE_NUM_MAX
};


class MotorDriver
{
 public:
  MotorDriver();
  ~MotorDriver();
  
  bool init(void);
  void close(void);

  bool is_connected();

  bool set_torque(bool onoff);
  bool get_torque();
  
  bool read_present_position(int32_t &left_value, int32_t &right_value);
  bool read_present_velocity(int32_t &left_value, int32_t &right_value);
  bool read_present_current(int16_t &left_value, int16_t &right_value);
  bool read_profile_acceleration(uint32_t &left_value, uint32_t &right_value);
  
  bool write_velocity(int32_t left_value, int32_t right_value);
  bool write_profile_acceleration(uint32_t left_value, uint32_t right_value);

  bool control_motors(const float wheel_separation, float linear_value, float angular_value);

 private:
  uint8_t left_wheel_id_;
  uint8_t right_wheel_id_;
  bool torque_;
};

#endif // TURTLEBOT3_MOTOR_DRIVER_H_
