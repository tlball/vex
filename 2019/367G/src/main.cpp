// VEX V5 C++ Project with Competition Template
#include "vex.h"

#include "cube_commands.cpp"
#include "driver_commands.cpp"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor_Left           motor         3               
// Motor_Right          motor         4               
// Left_Arm             motor         9               
// Left_Grabber         motor         10              
// Right_Arm            motor         19              
// Right_Grabber        motor         20              
// Controller1          controller                    
// Controller2          controller                    
// Drivetrain           drivetrain    1, 2            
// ---- END VEXCODE CONFIGURED DEVICES ----
using namespace vex;

// Creates a competition object that allows access to Competition methods.
vex::competition Competition;

void pre_auton() {
  // All activities that occur before competition start
  // Example: setting initial positions
}

void autonomous() {
  // Place autonomous code here
  Motor_Left.rotateTo(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct,
                      false);
  Motor_Right.rotateTo(-2, vex::rotationUnits::rev, 50, vex::velocityUnits::pct,
                       true);
  Motor_Left.stop(vex::brakeType::hold);
  Motor_Right.stop(vex::brakeType::hold);
}

void drivercontrol() {
  // Place drive control code here, inside the loop
  while (true) {
    // This is the main loop for the driver control.
    // Each time through the loop you should update motor
    // movements based on input from the controller.

    // Left grabber, botton L1
    tankDrive();
    grabberButtons();
    armButtons();
  }
}

int main() {
  // Do not adjust the lines below
  vexcodeInit();

  // Set up (but don't start) callbacks for autonomous and driver control
  // periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);

  // Run the pre-autonomous function.
  pre_auton();


  // Robot Mesh Studio runtime continues to run until all threads and
  // competition callbacks are finished.
}
