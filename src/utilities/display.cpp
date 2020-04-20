#ifndef DISPLAY_CPP
#define DISPLAY_CPP

#include <iostream>
#include <vector>
#include "vex.h"

using namespace std;

#define displayMaxLines 12

namespace {
  class Display {
    public:
      static vector<string> lines;

    public:
      void static println(const char *text) {
        string str(text);
        lines.push_back(str);

        Display::clear();

        for (int i = ((lines.size() >= displayMaxLines) ? lines.size() - displayMaxLines: 0); i < lines.size() - 1; i++) {
          Brain.Screen.print(lines[i].c_str());
          Brain.Screen.newLine();
        }

        Brain.Screen.print(text);
        Brain.Screen.newLine();
      }

      void static println(string text) {
        Display::println(text.c_str());
      }

      void static clear() {
        Brain.Screen.setCursor(1,1);
        Brain.Screen.clearScreen();
      }

      void static setTitle(const char *text) {
        Display::clear();
        Brain.Screen.printAt(1, 16, text);
        Brain.Screen.drawLine(1, 22, 480, 22); //Draw a title separator
      }
  };

  vector<string> Display::lines;
}

#endif