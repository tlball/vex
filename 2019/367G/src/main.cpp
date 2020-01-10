/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
motor_group Arms = motor_group(LeftArm, RightArm);
controller Controller2 = controller(partner);
motor_group Grabbers = motor_group(LeftGrabber, RightGrabber);


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void stacker(void) {

  Drivetrain.stop(hold);
  Pusher.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
  Grabbers.spin(vex::directionType::fwd, 55, vex::velocityUnits::pct);
  wait(500, msec);
  Pusher.stop();
  wait(300, msec);
  Drivetrain.driveFor(-14, vex::distanceUnits::in);
  Grabbers.stop();
  wait(500, msec);
  Pusher.spin(vex::directionType::fwd, 70, vex::velocityUnits::pct);
  wait(500, msec);
  Pusher.stop();
}

void pickerupper(void) {
  Grabbers.spin(vex::directionType::rev, 55, vex::velocityUnits::pct);
  Drivetrain.driveFor(forward, 39, inches, 20, velocityUnits::pct, true);
  Drivetrain.stop(hold);
  wait(500, msec);
  Grabbers.stop();
  // Drivetrain.driveFor(reverse, 39, inches, 50, velocityUnits::pct, true);
  Drivetrain.turnFor(-120, degrees);
  Drivetrain.setTimeout(2, sec);
  Drivetrain.driveFor(forward, 25, inches, 50, velocityUnits::pct, true);
  Drivetrain.stop(hold);
  wait(300, msec);
}

void armsup(void) {
  Arms.spin(vex::directionType::rev, 20, velocityUnits::pct);
  Grabbers.spin(vex::directionType::fwd, 73, vex::velocityUnits::pct);
  wait(1000, msec);
  Arms.stop(hold);
  wait(1000, msec);
  Arms.spin(vex::directionType::fwd, 20, velocityUnits::pct);
  wait(1000, msec);
  Arms.stop(hold);
}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  // Drivetrain.driveFor(forward, 36, inches, 50, velocityUnits::pct, true);
  // Arms.spinFor(reverse, 5, rotationUnits::rev, 75, velocityUnits::pct);
  // Grabbers.spinFor(forward, 5, rotationUnits::rev, 75, velocityUnits::pct);
  armsup();
  pickerupper();
  stacker();

  //// Current working autonomous
  // Drivetrain.setDriveVelocity(75, percent);
  // Drivetrain.driveFor(25, vex::distanceUnits::in);
  // wait(3, msec);
  // Drivetrain.setDriveVelocity(35, percent);
  // Drivetrain.driveFor(-14, vex::distanceUnits::in);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void pusherJoystick() {
  // Dividing by 2 regulates the speed
  int pusherSpeed = Controller2.Axis3.position() / 2;

  // Deadband is how much leeway you give the joystick
  double deadband = 5 / 2;
  if (abs(pusherSpeed) <= deadband) {
    pusherSpeed = 0;
  }
  Pusher.spin(vex::directionType::rev, pusherSpeed, vex::velocityUnits::pct);
}

void grabberJoystick() {

  int grabberSpeed = Controller2.Axis2.position();
  int deadband = 5;

  if (abs(grabberSpeed) <= deadband) {
    grabberSpeed = 0;
  }

  Grabbers.spin(vex::directionType::rev, grabberSpeed, vex::velocityUnits::pct);
}

void grabberButtons() {
  //// Grabber controls

  // Left, top button spins grabbers
  // Right, top button spins grabbers in reverse
  // Stop grabbers when buttons aren't pressed
  if (Controller2.ButtonR1.pressing()) {
    // Left and Right grabbers run forward when pressing L1
    Grabbers.spin(vex::directionType::rev, 55, vex::velocityUnits::pct);
  } else if (Controller2.ButtonR2.pressing()) {
    // Left and Right grabbers run in reverse when pressing R1
    Grabbers.spin(vex::directionType::fwd, 55, vex::velocityUnits::pct);
  } else {
    // Stop motors if neither button pressed
    grabberJoystick();
  }
}

void armButtons() {
  if (Controller2.ButtonL1.pressing()) {
    // Left and Right arms move up when pressing L2
    Arms.spin(reverse, 35, percent);
  } else if (Controller2.ButtonL2.pressing()) {
    // Left and Right arms move down when pressing R2
    Arms.spin(forward, 35, percent);
  } else {
    // Stop motors if neither button pressed
    Arms.stop(hold);
  }
}

void pusherButtons() {
  if (Controller2.ButtonX.pressing()) {
    // Pusher moves forward
    Pusher.spin(vex::directionType::fwd, 30, vex::velocityUnits::pct);
  } else if (Controller2.ButtonB.pressing()) {
    // Pusher moves back
    Pusher.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
  } else {
    // Stop motor if neither button pressed
    pusherJoystick();
  }
}

void stackerbuttons() {
  if(Controller2.ButtonDown.pressing()){
    stacker();
  }
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    
    stackerbuttons();
    grabberButtons();
    armButtons();
    pusherButtons();
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
