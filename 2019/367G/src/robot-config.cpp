#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Motor_Left = motor(PORT1, ratio18_1, true);
motor Motor_Right = motor(PORT2, ratio18_1, false);
motor Left_Arm = motor(PORT9, ratio18_1, true);
motor Left_Grabber = motor(PORT10, ratio18_1, true);
motor Right_Arm = motor(PORT19, ratio18_1, false);
motor Right_Grabber = motor(PORT20, ratio18_1, false);
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}