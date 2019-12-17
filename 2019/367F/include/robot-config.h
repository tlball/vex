using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Leftarm;
extern motor Claw;
extern motor Rightarm;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );