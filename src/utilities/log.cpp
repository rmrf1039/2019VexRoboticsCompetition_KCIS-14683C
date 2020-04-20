#ifndef LOG_CPP
#define LOG_CPP

#include<sstream>
#include "display.cpp"
#include "vex.h"

using namespace std;

namespace {
  class Log {
    private:
      static string serialNumber;
      static bool isReady;

    public:
      void static appendLog(const char *text) {
        if (Log::isReady) { //Append log when file is ready
          
        }
      }

    public:
      bool static prepareFile(string serialNum) {
        if (Brain.SDcard.isInserted()) {
          //log insertion

          return true;
        } else {
          //Display::println("[ERROR] SD card is not inserted.");
        }

        return false;
      }
  };

  string Log::serialNumber = to_string((rand() % 100) * 100 + (rand() % 100));
  bool Log::isReady = Log::prepareFile(serialNumber);
}

#endif