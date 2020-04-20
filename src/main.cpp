#include "vex.h"
#include "utilities/display.cpp"
#include "utilities/pid.cpp"
#include "services/inspection.cpp"
#include "services/autonScript.cpp"
#include "modules/joystick.cpp"
#include "modules/chassis.cpp"
#include "modules/cubeIntaker.cpp"
#include "modules/cubeHolder.cpp"
#include "vex_task.h"
#include "vex_units.h"
#include <globals.h>

using namespace vex;

// Custom Settings
#define THRESHOLD 20

// Modules Register
AutonScript autonScript;
Chassis chassis(LFM, LBM, RFM, RBM);
CubeIntaker cubeIntaker(CML, CMR);
CubeHolder cubeHolder(CHL, CHR);

void pre_auton(void) {
  Display::println("[SYS] Pre-Auton Start");

  Joystick::initialize();
  Inspection::inspect(); //Inspection
  chassis.stop(vex::brakeType::hold);
  autonScript.initialize(chassis, cubeIntaker, cubeHolder); //AutonScript
  Display::println("[SYS] Pre-Auton End");
  Joystick::println("[OK] Pre-Auton");
}

void autonomous(void) {
  Display::println("[SYS] Auton Period Start");

  autonScript.runScript(); //Run auton script
  
  Display::println("[SYS] Auton Period End");
  Joystick::println("[OK] Auton P.");
}

void usercontrol(void) {
  Display::println("[SYS] User Period Start");
  Joystick::println("[SYS] User P.");

  int Joy1Axis, Joy2Axis, Joy3Axis, Joy4Axis;

  //usercontrol mode initialization
  //cubeHolder.init();

  while (1) {
    if (isCritical()) continue;

    Joy1Axis = Controller.Axis1.position();
    Joy2Axis = Controller.Axis2.position();
    Joy3Axis = Controller.Axis3.position();
    Joy4Axis = Controller.Axis4.position();

    if (Controller.ButtonLeft.pressing()) {
      //chassis.rotateFor(40, 90);
    }
    
    if (Controller.ButtonDown.pressing()) {
      
    }
    
    if (Controller.ButtonRight.pressing()) {}

    if (Controller.ButtonUp.pressing()) {
      
    }
    
    if (Controller.ButtonL1.pressing() || Controller.ButtonL2.pressing()) {
      cubeHolder.init();
      vex::task::sleep(20);
    }
    
    if (Controller.ButtonR1.pressing()) {
      chassis.setMode(1); //regular mode
      vex::task::sleep(20);
    }
    
    if (Controller.ButtonR2.pressing()) {
      chassis.setMode(2); //speed mode
      vex::task::sleep(20);
    }

    if (abs(Joy2Axis) > 50) { //passing the threshold, preventing unstable axis value
      cubeIntaker.roll(Joy2Axis);
    } else {
      cubeIntaker.stop(vex::brakeType::coast);
    }

    if (abs(Joy1Axis) > 40) {
      if (Joy1Axis > 0) {
        cubeHolder.spin(-10); //going up
      } else if (!CubeHolderLimit.pressing()){
        cubeHolder.spin(80); //going down
      } else {
        cubeHolder.stop(vex::brakeType::hold);
      }
    } else {
      cubeHolder.stop(vex::brakeType::hold);
    }

    if (abs(Joy3Axis) > THRESHOLD || abs(Joy4Axis) > THRESHOLD) { //passing the threshold, preventing unstable axis value
      chassis.moveManually(Joy4Axis, Joy3Axis);
    } else {
      chassis.stop(vex::brakeType::coast);
    }

    Controller.Screen.print("CHD: %f", cubeHolder.getCurrentDegree());

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

int main() {
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    pre_auton();
                           
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
}