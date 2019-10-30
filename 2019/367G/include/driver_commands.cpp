#include "vex.h"

using namespace vex;

void tankDrive() {
  // Left motor, vertical axis of left joystick
  Motor_Left.spin(vex::directionType::fwd,
                  Controller1.Axis3.position(vex::percentUnits::pct),
                  vex::velocityUnits::pct);
  // Right motor, vertical axis of right joystick
  Motor_Right.spin(vex::directionType::fwd,
                   Controller1.Axis2.position(vex::percentUnits::pct),
                   vex::velocityUnits::pct);
}