
//Include Libraries needed
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

//Making Directions Shorter for Later
int F = FORWARD;
int B = BACKWARD;
int S = RELEASE;

//Setup for MotorShield including naming motors ML and MR
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *ML = AFMS.getMotor(3);
Adafruit_DCMotor *MR = AFMS.getMotor(4);

//Naming Sensor Inputs for Later
int sensorL = A0;
int sensorC = A1;
int sensorR = A2;

//Black Threshold for line following sensor reads
int BT = 500; 

///State of 0 given because maze hasn't been solved
boolean mazeSolved = 0;

void setup() {
  // put your setup code here, to run once:

  //Connect to the Motor Controller
  AFMS.begin();
 
 //Set Motor Speeds to 100 (Value between 0 and 255)
  ML->setSpeed(100);
  MR->setSpeed(100);   

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //if maze has been solved stop the robot
  if (mazeSolved == 1){
    robotStop();
  }
  
  // if it is not solved follow the mazeSolve function
  else {
    solveMaze();
  }
}

//Function used to decide where robot should go to solve maze
void solveMaze() {
   
  //Reading Data from Line Following Sensors
  int sensorValueL = analogRead(sensorL);
  int sensorValueC = analogRead(sensorC);
  int sensorValueR = analogRead(sensorR);
  
  //If there is only black under the center, then go straight
  if (sensorValueC > BT && sensorValueL < BT && sensorValueR < BT) {
    goStraight();
  }
  
  //IF there is black under all three sensors, go left to follow left hand rule
  if (sensorValueC > BT && sensorValueL > BT && sensorValueR > BT) {
    //while loops used to allow robot to turn only until the center sensor has covered new line
    while (sensorVavleL > BT) {
      goLeft();
    }
    while (sensorValueC < BT) {
      goLeft();
    }
    //Since the end is a circle if at this point the robot has just its left
    //over white then the maze is solved and the integer is changed
    if (sensorValueC > BT && sensorValueL < BT && sensorValueR > BT) {
      mazeSolved = 1;
    }
  }
  
  //If the center and left are over left go left to follow lefthand rule
  if (sensorValueC > BT && sensorValueL > BT && sensorValueR < BT) {
    //while loops used to allow robot to turn only until the center sensor has covered new line
    while (sensorVavleL > BT) {
      goLeft();
    }
    while (sensorValueC < BT) {
      goLeft();
    }
  }
  
  //If the center and right are over black just go straight following left hand rule

  if (sensorValueC > BT && sensorValueL < BT && sensorValueR > BT) {
    goStraight();
  }
  
  //If only the right sensor is over black then now turn right
  //Also used to get back on line if moving to the left
  if (sensorValueC < BT && sensorValueL < BT && sensorValueR > BT) {
    //while loop used to allow robot to turn only until the center sensor has covered new line
    while (sensorValueC < BT) {
      goRight();
    }
  }
  
  //If no sensors are over black, turnaround as stated by left hand rule
  if (sensorValueC < BT && sensorValueL < BT && sensorValueR < BT) {
    //while loop used to allow robot to turn only until the center sensor has covered new line
    while (sensorValueC < BT) {
      turnAround();
    }
  }
}

//Function to tell the robot to move straight ahead
void goStraight(){
  ML->run(F);
  MR->run(F);
  
}

//Function to tell the robot to turn left
void goLeft() {
  ML->run(B);
  MR->run(F);
}

//Function to tell the robot to turn right
void goRight() {
  ML->run(F);
  MR->run(B);
}

//Function to tell the robot to move backwards
void goBackwards() {
  ML->run(B);
  MR->run(B);
}

//Function to tell the robot to turn around
void turnAround() {
  ML->run(F);
  MR->run(B);
}
