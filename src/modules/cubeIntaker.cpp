#ifndef CUBE_INTAKER_CPP
#define CUBE_INTAKER_CPP

#include "vex.h"

class CubeIntaker {
  private:
    vex::motor* ML;
    vex::motor* MR;

    //status
    

  public:
    CubeIntaker(vex::motor& ML, vex::motor& MR) {
      this->ML = &ML;
      this->MR = &MR;
    }

  public:
    void roll(int velocity) {
      ML->spin(vex::directionType::rev, velocity , vex::velocityUnits::pct);
      MR->spin(vex::directionType::fwd, velocity , vex::velocityUnits::pct);
    }

    void stop(vex::brakeType mode) {
      ML->stop(mode);
      MR->stop(mode);
    }
};

#endif