#ifndef CUBE_HOLDER_CPP
#define CUBE_HOLDER_CPP

#include "vex.h"
#include "vex_global.h"
#include "vex_units.h"
#include "../utilities/display.cpp"
#include <utility.h>

#define RIGHT_ANGLE_REV 236
#define GEAR_RATIO 5;

class CubeHolder {
  private:
    vex::motor* ML;
    vex::motor* MR;

    //status
    double revPerAngle = RIGHT_ANGLE_REV / GEAR_RATIO;

  public:
    CubeHolder(vex::motor& ML, vex::motor& MR) {
      this->ML = &ML;
      this->MR = &MR;
    }

  public:
    void init() {
      Display::println("[INF] Initilizing CH.");

      while(true) {
        while (!CubeHolderLimit.pressing()) {
          this->spin(80); //go down quickly
        }

        break;
      }

      this->reset();
    }

    void reset() {
      ML->resetRotation();
      MR->resetRotation();
    }

    void rotateFor(int degree, int velocity) {
      Display::println("[INF] CH. rotates for " + to_string(degree));

      CHL.rotateFor(degree, vex::rotationUnits::deg, velocity, vex::velocityUnits::pct, false);
      CHR.rotateFor(-degree, vex::rotationUnits::deg, velocity, vex::velocityUnits::pct);
      this->stop(vex::brakeType::hold);
    }

    void stop(vex::brakeType mode) {
      ML->stop(mode);
      MR->stop(mode);
    }

    void spinInTime(int velocity, int duration) {
      Display::println("[INF] CH. spins for " + to_string(duration) + "s");

      ML->spin(vex::directionType::fwd, velocity, vex::velocityUnits::pct);
      MR->spin(vex::directionType::rev, velocity, vex::velocityUnits::pct);
      vex::task::sleep(duration);
      ML->stop(vex::brakeType::brake);
      MR->stop(vex::brakeType::brake);
      vex::task::sleep(duration * 2);
    }

    void spin(int velocity) {
      ML->spin(vex::directionType::rev, velocity , vex::velocityUnits::pct);
      MR->spin(vex::directionType::fwd, velocity , vex::velocityUnits::pct);
    }

    double getCurrentDegree() {
      return ML->rotation(vex::rotationUnits::rev);
    }
};

#endif