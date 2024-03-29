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
    int32_t goal_rpm;
    int32_t servo_position;

    int32_t present_rpm[MortorLocation::MOTOR_NUM_MAX];
} ControlItemVariables;