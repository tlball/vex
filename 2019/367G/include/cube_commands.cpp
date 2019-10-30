#include "vex.h"

using namespace vex;

void grabberButtons() {
  //// Grabber controls

  // Left, top button spins grabbers
  // Right, top button spins grabbers in reverse
  // Stop grabbers when buttons aren't pressed
  if (Controller1.ButtonL1.pressing()) {
    Left_Grabber.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    // Right grabber, botton R1
    Right_Grabber.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  } else if (Controller1.ButtonR1.pressing()) {
    Left_Grabber.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    Right_Grabber.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  } else {
    Left_Grabber.stop();
    Right_Grabber.stop();
  }
}

void armButtons() {
  if (Controller1.ButtonL2.pressing()) {
    Left_Arm.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    // Right arm, botton R2
    Right_Arm.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  } else if (Controller1.ButtonR2.pressing()) {
    Left_Arm.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    Right_Arm.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  } else {
    Left_Arm.stop();
    Right_Arm.stop();
  }
}