#ifndef GLOBALS_H
#define GLOBALS_H

#include "vex.h"

// Structs
struct MotorSet {
  vex::motor obj;
  int velocity;
};

// Controllers
extern vex::brain Brain;
extern vex::competition Competition;
extern vex::controller Controller;

// Motors
extern vex::motor LFM;
extern vex::motor LBM;
extern vex::motor RFM;
extern vex::motor RBM;
extern vex::motor CML;
extern vex::motor CMR;
extern vex::motor CHL;
extern vex::motor CHR;

// Sensors
extern vex::limit CubeHolderLimit;
extern vex::limit CubeDetectorLimit;

#endif