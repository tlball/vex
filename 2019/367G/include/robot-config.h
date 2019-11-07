using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Motor_Left;
extern motor Motor_Right;
extern motor Left_Arm;
extern motor Left_Grabber;
extern motor Right_Arm;
extern motor Right_Grabber;
extern controller Controller1;
extern controller Controller2;
extern drivetrain Drivetrain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );