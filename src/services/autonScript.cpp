#ifndef AUTON_SCRIPT_CPP
#define AUTON_SCRIPT_CPP

#include "vex.h"
#include "../utilities/display.cpp"
#include "../modules/joystick.cpp"
#include "../modules/visions.cpp"
#include "../modules/chassis.cpp"
#include "../modules/cubeIntaker.cpp"
#include "../modules/cubeHolder.cpp"
#include "vex_task.h"
#include "vex_units.h"
#include <globals.h>

class AutonScript {
  public:
    void (AutonScript::*script)() = NULL;
    Chassis* chassis;
    CubeIntaker* cubeIntaker;
    CubeHolder* cubeHolder;

  public:
    void initialize(Chassis& chassis, CubeIntaker& cubeIntaker, CubeHolder& cubeHolder) {
      this->chassis = &chassis;
      this->cubeIntaker = &cubeIntaker;
      this->cubeHolder = &cubeHolder;

      Display::setTitle("Auton Script Selection");

      //Draw Red Team Fields
      Brain.Screen.drawRectangle(25, 28, 100, 100, "#FF0000"); //RA Team //left
      Brain.Screen.drawRectangle(25, 138, 100, 100, "#FF0000"); //RB Team //right

      //Draw Blue Team Fields
      Brain.Screen.drawRectangle(355, 28, 100, 100, "#0000FF"); //BA Team //right
      Brain.Screen.drawRectangle(355, 138, 100, 100, "#0000FF"); //BB Team //left

      //Draw None Square
      Brain.Screen.drawRectangle(135, 138, 210, 100, "#FFFFFF");
    
      vex::task::sleep(1000);

      while(!Brain.Screen.pressing()) vex::task::sleep(20);

      specifyScript();
    }

    void runScript() {
      Display::clear();
      Display::println("[SYS] Executing the auton script");
      (*this.*script)();
      Display::clear();
    }

  private:
    void specifyScript() {
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();

      Display::clear();

      if ((x >= 25 && x <= 125) && (y >= 28 && y <= 128)) { //Pressed RA Team
        script = &AutonScript::RA_Script;
        Display::println("[SYS] RA Script has been selected");
        Joystick::println("[IN] Run RA Scr.");
      } else if ((x >= 25 && x <= 125) && (y >= 138 && y <= 238)) { //pressed RB Team
        script = &AutonScript::RB_Script;
        Display::println("[SYS] RB Script has been selected");
        Joystick::println("[IN] Run RB Scr.");
      } else if ((x >= 355 && x <= 455) && (y >= 28 && y <= 128)) { //pressed BA Team
        script = &AutonScript::BA_Script;
        Display::println("[SYS] BA Script has been selected");
        Joystick::println("[IN] Run BA Scr.");
      } else if ((x >= 355 && x <= 455) && (y >= 138 && y <= 238)) { //pressed BB Team
        script = &AutonScript::BB_Script;
        Display::println("[SYS] BB Script has been selected");
        Joystick::println("[IN] Run BB Scr.");
      } else if ((x >= 135 && x <= 345) && (y >= 138 && y <= 238)) {
        script = &AutonScript::None_Script;
        Display::println("[SYS] None Script has been selected");
        Joystick::println("[IN] Non Scr.");
      }
    }

  public:
    void RA_Script() {
      cubeIntaker->roll(-200);

      vex::task::sleep(2000);

      chassis->rotateFor(40, -110);

      chassis->moveLinearly(40, 60);

      chassis->rotateFor(20, -40);

      chassis->moveLinearly(40, 50);

      cubeIntaker->roll(200);
      vex::task::sleep(1800);
      chassis->moveLinearly(40, -60, vex::brakeType::coast);
    }

    void RB_Script() {
      cubeIntaker->roll(-200);

      this->General_Script(); //expand cube holder and supportive wheel

      chassis->moveLinearly(70, 40);
      chassis->moveLinearly(10, 100);
      cubeIntaker->roll(0);
      chassis->moveLinearly(40, -100, vex::brakeType::coast);
      //chassis->moveLinearly(30, -70);

      /*
      chassis->rotateFor(30, 120);
      chassis->moveLinearly(30, 30);
      cubeIntaker->roll(30);
      vex::task::sleep(2200);
      cubeIntaker->roll(0);

      cubeHolder->rotateFor(965, 10);
      vex::task::sleep(1000);
      cubeHolder->rotateFor(-965, 40);
      //chassis->moveLinearly(30, -30, vex::brakeType::coast);
      //chassis->moveLinearly(30, -20);
      */
    }

    void BA_Script() {
      cubeIntaker->roll(-200);

      vex::task::sleep(2000);

      chassis->rotateFor(40, 110);

      chassis->moveLinearly(40, 60);

      chassis->rotateFor(20, 40);

      chassis->moveLinearly(40, 50);

      cubeIntaker->roll(200);
      vex::task::sleep(1800);
      chassis->moveLinearly(40, -60, vex::brakeType::coast);
    }

    void BB_Script() {
      cubeIntaker->roll(-200);

      this->General_Script(); //expand cube holder and supportive wheel

      chassis->moveLinearly(70, 40);
      chassis->moveLinearly(10, 110);
      cubeIntaker->roll(0);
      chassis->moveLinearly(40, -100, vex::brakeType::coast);
      //chassis->moveLinearly(30, -70);
    }

    void None_Script() {
      this->General_Script(); //expand cube holder and supportive wheel
    }

    void General_Script() {
      chassis->moveLinearly(50, 20);
      cubeHolder->rotateFor(545, 255);
      cubeHolder->rotateFor(-545, 150);
    }
};

#endif