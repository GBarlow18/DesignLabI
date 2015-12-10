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
Adafruit_DCMotor *ML = AFMS.getMotor(2);
Adafruit_DCMotor *MR = AFMS.getMotor(1);

//Naming Sensor Inputs for Later
int sensorL = A0;
int sensorC = A1;
int sensorR = A2;

//Black Threshold for line following sensor reads
int BT = 500;    

void setup() {
  // put your setup code here, to run once:
  
  //Connect to the Motor Controller
  AFMS.begin();     
 
 //Set Motor Speeds to 100 (Value between 0 and 255)
  ML->setSpeed(125);
  MR->setSpeed(125);   

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Reading Data from Line Following Sensors
  int sensorValueL = analogRead(sensorL);
  int sensorValueC = analogRead(sensorC);
  int sensorValueR = analogRead(sensorR);

    //Turn right if right sensor is over the line
  if (sensorValueR > BT){
    goRight();
  }
  else {  
    //Turn left if left sensor is over the line
    if (sensorValueL > BT){
      goLeft();
    }
    
    //If neither the left or right sensors are over the line then go straight ahead
    else {
      goStraight();
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
