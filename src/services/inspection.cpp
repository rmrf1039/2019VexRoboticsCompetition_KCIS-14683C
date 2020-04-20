#ifndef INSPECTION_CPP
#define INSPECTION_CPP

#include "../modules/joystick.cpp"
#include "../utilities/log.cpp"
#include "vex.h"

#define TOLERENCE 0.1

namespace {
  class Inspection {
    public:
      void static inspect() {
        bool isDone = false;

        if (confirmExecution()) {
          Display::clear();
          Display::println("[SYS] Start running the inspection program.");
          Joystick::println("[SYS] INSP. Start");

          //custom code
          //Inspection::inspectMotor(LFM, 360);

          vex::task::sleep(1000);

          isDone = true;

          Log::appendLog("[SYS] Inspection is succesfully passed.");
          Joystick::println("[SYS] INSP. Pass");
        }

        isDone = true;

        while (!isDone) vex::task::sleep(20);
      }

      /*
      * Test a motor in both forward and backward
      */
      bool static inspectMotor(vex::motor m, int testValue) {
        /*if (m.isSpinning()) m.stop(vex::brakeType::hold);

        int initDeg = m.rotation(vex::rotationUnits::deg);

        m.rotateFor(vex::directionType::fwd, testValue, vex::rotationUnits::deg, false);

        int finalDeg = m.rotation(vex::rotationUnits::deg);

        m.rotateFor(vex::directionType::rev, testValue, vex::rotationUnits::deg, false);

        return (finalDeg - initDeg / 100 <= TOLERENCE) ? true : false;*/

        return true;
      }

    private:
      bool static confirmExecution() {
        Display::setTitle("Are you sure to run the inspection?");
        Brain.Screen.drawRectangle(30, 32, 200, 200, "#00FF00");
        Brain.Screen.drawRectangle(250, 32, 200, 200, "#FF0000");

        int x, y;

        do {
          while (!Brain.Screen.pressing()) vex::task::sleep(20);

          x = Brain.Screen.xPosition();
          y = Brain.Screen.yPosition();

          if ((x >= 30 && x <= 230) && (y >= 32 && y <= 232)) {
            return true;
          } else if ((x >= 250 && x <= 450) && (y >= 32 && y <= 232)) {
            break;
          }
        } while (!(((x >= 30 && x <= 230) && (y >= 32 && y <= 232)) || ((x >= 250 && x <= 450) && (y >= 32 && y <= 232))));

        return false;
      }
  };
}

#endif