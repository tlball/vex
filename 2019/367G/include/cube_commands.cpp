#include "vex.h"

using namespace vex;

void grabberButtons() {
  //// Grabber controls

  // Left, top button spins grabbers
  // Right, top button spins grabbers in reverse
  // Stop grabbers when buttons aren't pressed
  if (Controller1.ButtonL1.pressing()) {
    // Left and Right grabbers run forward when pressing L1
    Left_Grabber.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
    Right_Grabber.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
  } else if (Controller1.ButtonR1.pressing()) {
    // Left and Right grabbers run in reverse when pressing R1
    Left_Grabber.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
    Right_Grabber.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
  } else {
    // Stop motors if neither button pressed
    Left_Grabber.stop(hold);
    Right_Grabber.stop(hold);
  }
}

void armButtons() {
  if (Controller1.ButtonL2.pressing()) {
    // Left and Right arms move up when pressing L2
    Left_Arm.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
    Right_Arm.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
  } else if (Controller1.ButtonR2.pressing()) {
    // Left and Right arms move down when pressing R2
    Left_Arm.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
    Right_Arm.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
  } else {
    // Stop motors if neither button pressed
    Left_Arm.stop(hold);
    Right_Arm.stop(hold);
  }
}