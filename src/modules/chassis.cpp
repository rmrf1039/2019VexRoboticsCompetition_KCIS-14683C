#ifndef CHASSIS_CPP
#define CHASSIS_CPP

#include "vex.h"
#include "../utilities/display.cpp"
#include "vex_units.h"
#include <utility.h>

#define WHEEL_DIAMETER 10.16

class Chassis {
  private:
    vex::motor* LFM;
    vex::motor* LBM;
    vex::motor* RFM;
    vex::motor* RBM;

    //states
    int mode = 1;

  public:
    Chassis(vex::motor& LFM, vex::motor& LBM, vex::motor& RFM, vex::motor& RBM) {
      this->LFM = &LFM;
      this->LBM = &LBM;
      this->RFM = &RFM;
      this->RBM = &RBM;
    }

  public:
    void setVelocity(int velocity) {
      LFM->setVelocity(velocity, vex::velocityUnits::pct); 
      LBM->setVelocity(velocity, vex::velocityUnits::pct);
      RFM->setVelocity(velocity, vex::velocityUnits::pct); 
      RBM->setVelocity(velocity, vex::velocityUnits::pct);
    }

    void stop(vex::brakeType mode) {
      this->setVelocity(0);

      LFM->stop(mode);
      LBM->stop(mode);
      RFM->stop(mode);
      RBM->stop(mode);
    }

    void moveLinearly(int velocity, int distance, vex::brakeType bType) {
      double degreesToRotate = (360 * (1.7 + (distance - 1) * 0.7)) / (WHEEL_DIAMETER * 3.141592);

      Display::println("[INF] Chs. moves linearly " + to_string(distance) + "cm");

      this->setVelocity(velocity);

      LFM->rotateFor(vex::directionType::fwd, degreesToRotate, vex::rotationUnits::deg, false);
      LBM->rotateFor(vex::directionType::fwd, degreesToRotate, vex::rotationUnits::deg, false);
      RFM->rotateFor(vex::directionType::rev, degreesToRotate, vex::rotationUnits::deg, false); 
      RBM->rotateFor(vex::directionType::rev, degreesToRotate, vex::rotationUnits::deg, false);

      while(!LFM->isDone() || !LBM->isDone() || !RFM->isDone() || !RBM->isDone()){}

      this->stop(bType); //To immediately stop wheel spinning.
    }

    void moveLinearly(int velocity, int distance) {
      this->moveLinearly(velocity, distance, vex::brakeType::hold);
    }

    void rotateFor(int velocity, int degree) {
      double oneDegree = 345/90;

      Display::println("[INF] Chs. rotates for " + to_string(degree));

      this->setVelocity(velocity);

      LFM->rotateFor(vex::directionType::fwd, oneDegree * degree, vex::rotationUnits::deg, false);
      LBM->rotateFor(vex::directionType::fwd, oneDegree * degree, vex::rotationUnits::deg, false);
      RFM->rotateFor(vex::directionType::fwd, oneDegree * degree, vex::rotationUnits::deg, false);
      RBM->rotateFor(vex::directionType::fwd, oneDegree * degree, vex::rotationUnits::deg, false);
      
      while(!LFM->isDone() || !LBM->isDone() || !RFM->isDone() || !RBM->isDone()){}

      this->stop(vex::brakeType::hold); //To immediately stop wheel spinning.
    }

    void rotateTo(int velocity, int degree) {

    }

    void spin(int velocity) {
      LFM->spin(vex::directionType::fwd);
      LBM->spin(vex::directionType::fwd);
      RFM->spin(vex::directionType::rev);
      RBM->spin(vex::directionType::rev);
    }

    void moveManually(int axis1, int axis2) {
      float decayRate = 1;

      if (mode == 1) {
        decayRate = 0.4;
      } else if (mode == 2) {
        decayRate = 1;
      }

      LFM->spin(vex::directionType::fwd, decayRate * (axis2 + axis1), vex::velocityUnits::pct);
      LBM->spin(vex::directionType::fwd, decayRate * (axis2 + axis1), vex::velocityUnits::pct);
      RFM->spin(vex::directionType::rev, decayRate * (axis2 - axis1), vex::velocityUnits::pct);
      RBM->spin(vex::directionType::rev, decayRate * (axis2 - axis1), vex::velocityUnits::pct);
    }

    void setMode(int mode) {
      this->mode = mode;
      
      switch(mode){
        case 1:
          Display::println("[INF] Chs's mode sets to REGULAR");
          break;

        case 2:
          Display::println("[INF] Chs' mode sets to TURBO");
          break;
      }
    }

    int getMode() {
      return mode;
    }
};

#endif