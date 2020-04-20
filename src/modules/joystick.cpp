#ifndef JOYSTICK_CPP
#define JOYSTICK_CPP

#include <iostream>
#include <vector>
#include "vex.h"

using namespace std;

#define joystickDisplayMaxLines 3

namespace {
  class Joystick {
    public:
      static vector<string> lines;

    public:
      void static println(const char *text) {
        string str(text);
        lines.push_back(str);

        Joystick::clear();

        for (int i = ((lines.size() >= joystickDisplayMaxLines) ? lines.size() - joystickDisplayMaxLines: 0); i < lines.size() - 1; i++) {
          Controller.Screen.print(lines[i].c_str());
          Controller.Screen.newLine();
        }

        Controller.Screen.print(text);
        Controller.Screen.newLine();
        Controller.rumble(".");
      }

      void static println(string text) {
        Joystick::println(text.c_str());
      }
      
      void static clear() {
        Controller.Screen.setCursor(1,1);
        Controller.Screen.clearScreen();
      }

      void static initialize() {
        Joystick::clear();
      }
  };

  vector<string> Joystick::lines;
}

#endif