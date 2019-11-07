#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Motor_Left = motor(PORT3, ratio18_1, true);
motor Motor_Right = motor(PORT4, ratio18_1, false);
motor Left_Arm = motor(PORT9, ratio18_1, true);
motor Left_Grabber = motor(PORT10, ratio18_1, true);
motor Right_Arm = motor(PORT19, ratio18_1, false);
motor Right_Grabber = motor(PORT20, ratio18_1, false);
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor LeftDriveSmart = motor(PORT1, ratio18_1, false);
motor RightDriveSmart = motor(PORT2, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 130, mm, 1);

// VEXcode generated functions
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_callback_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    // calculate the drivetrain motor velocities from the controller joystick axies
    // left = Axis3
    // right = Axis2
    int drivetrainLeftSideSpeed = Controller1.Axis3.position();
    int drivetrainRightSideSpeed = Controller1.Axis2.position();
    // check if the value is inside of the deadband range
    if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
      // check if the left motor has already been stopped
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        // stop the left drive motor
        LeftDriveSmart.stop();
        // tell the code that the left motor has been stopped
        DrivetrainLNeedsToBeStopped_Controller1 = false;
      }
    } else {
      // reset the toggle so that the deadband code knows to stop the left motor next time the input is in the deadband range
      DrivetrainLNeedsToBeStopped_Controller1 = true;
    }
    // check if the value is inside of the deadband range
    if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
      // check if the right motor has already been stopped
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        // stop the right drive motor
        RightDriveSmart.stop();
        // tell the code that the right motor has been stopped
        DrivetrainRNeedsToBeStopped_Controller1 = false;
      }
    } else {
      // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
      DrivetrainRNeedsToBeStopped_Controller1 = true;
    }
    // only tell the left drive motor to spin if the values are not in the deadband range
    if (DrivetrainLNeedsToBeStopped_Controller1) {
      LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
      LeftDriveSmart.spin(forward);
    }
    // only tell the right drive motor to spin if the values are not in the deadband range
    if (DrivetrainRNeedsToBeStopped_Controller1) {
      RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
      RightDriveSmart.spin(forward);
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

// define variables used for controlling motors based on controller inputs
bool Controller2LeftShoulderControlMotorsStopped = true;
bool Controller2RightShoulderControlMotorsStopped = true;
bool Controller2XBButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller2
int rc_auto_loop_callback_Controller2() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    // check the ButtonL1/ButtonL2 status to control Right_Arm
    if (Controller2.ButtonL1.pressing()) {
      Right_Arm.spin(forward);
      Controller2LeftShoulderControlMotorsStopped = false;
    } else if (Controller2.ButtonL2.pressing()) {
      Right_Arm.spin(reverse);
      Controller2LeftShoulderControlMotorsStopped = false;
    } else if (!Controller2LeftShoulderControlMotorsStopped) {
      Right_Arm.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller2LeftShoulderControlMotorsStopped = true;
    }
    // check the ButtonR1/ButtonR2 status to control Motor_Right
    if (Controller2.ButtonR1.pressing()) {
      Motor_Right.spin(forward);
      Controller2RightShoulderControlMotorsStopped = false;
    } else if (Controller2.ButtonR2.pressing()) {
      Motor_Right.spin(reverse);
      Controller2RightShoulderControlMotorsStopped = false;
    } else if (!Controller2RightShoulderControlMotorsStopped) {
      Motor_Right.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller2RightShoulderControlMotorsStopped = true;
    }
    // check the X/B buttons status to control Motor_Left
    if (Controller2.ButtonX.pressing()) {
      Motor_Left.spin(forward);
      Controller2XBButtonsControlMotorsStopped = false;
    } else if (Controller2.ButtonB.pressing()) {
      Motor_Left.spin(reverse);
      Controller2XBButtonsControlMotorsStopped = false;
    } else if (!Controller2XBButtonsControlMotorsStopped){
      Motor_Left.stop();
      Controller2XBButtonsControlMotorsStopped = true;
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_callback_Controller1);
  task rc_auto_loop_task_Controller2(rc_auto_loop_callback_Controller2);
}