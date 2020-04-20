#ifndef GLOBALS_CPP
#define GLOBALS_CPP

#include "vex.h"
#include "modules/chassis.cpp"
#include "vex_triport.h"

// Structus
struct MotorSet;

// Controllers
vex::brain Brain;
vex::competition Competition;
vex::controller Controller = vex::controller();

// Motors
vex::motor LFM(vex::PORT16); //chassis
vex::motor LBM(vex::PORT18); //chassis
vex::motor RFM(vex::PORT9); //chassis
vex::motor RBM(vex::PORT19); //chassis
vex::motor CML(vex::PORT20); //cube intaker
vex::motor CMR(vex::PORT10); //cube intaker
vex::motor CHL(vex::PORT7); //cube holder
vex::motor CHR(vex::PORT8); //cube holder

// Sensors
vex::limit CubeHolderLimit(Brain.ThreeWirePort.A);
vex::limit CubeDetectorLimit(Brain.ThreeWirePort.B);

#endif