# 2019VexRoboticsCompetition_KCIS-14683C
This program controls our VEX EDR robot, 14683C, in 2019-2020 VEX Robotics Competition Tower Takeover. The code is written of C++, and the IDE is the Vexcode application from VEX company. Our robot ultimatedly went to the fourth rank in Formosa VEX Tower Takeover 2019.

### Features
 1. Even though the program isn't fully completed, it is flexible enough to put any new feature based on the original construction.
 2. Using sensors to avoid serious robot collision, but I haven't done it. You may write it in the 'emergency.cpp' file.
 3. As the program uses module styling, it is easy to customize autonomous script by scripting style.
 4. Using one code to print massages on the screen, and the screen will automatically scroll down to show up overflow info.
 5. The program has designed a inspection period so that you may write your own inspection code to check the availability of each motor and sensor.
 
### Sources
+ robot-config.cpp - port settings
+ main.cpp - the main program to control the bot
+ modules/
  + chassis.cpp - the module to control the wheels
  + cubeHolder.cpp - the module to control the cube holder
  + cubeIntaker.cpp - the module to control the cube intaker
  + joystick.cpp - the module to control the display of joystick
  + visions.cpp - empty template
+ services/
  + autonScript.cpp - the module to let player choosing specific running script for autonomous period
  + emergency.cpp - empty template(suppose to detect the axises of the robot, avoding collision)
  + inspection.cpp - empty template(suppose to inspect all the sensors an motor to make sure everything works)
+ utilities/
  + display.cpp - a module to print messages on the screen like a console
  + log.cpp - empty template(suppose to log info. into a SD card for debugging)
  + pid.cpp - a module to run PID controlling
  + utility.cpp - string manipulation tools
