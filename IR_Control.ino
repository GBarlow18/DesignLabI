
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

//Pins designated for components used (Bumpers and the LDR)
int Bumper1 = 6;
int Bumper2 = 10;
int LDR = A4;
//Threshold to decide when under bright light from LDR Reading
int LT = 960;

void setup() {
  // put your setup code here, to run once:
  
 //Connect to the Motor Controller
 AFMS.begin();     
 
 //Set Motor Speeds to 125 (Value between 0 and 255)
  ML->setSpeed(125);
  MR->setSpeed(125);   
  
  //Set pin mode for bumper switches
  pinMode(Bumper1, INPUT);
  pinMode(Bumper2, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //robot will always start loop going forward
  goStraight();
  
  //State of 0 given to bumper states for open switch
  boolean Bumper1State = LOW;
  boolean Bumper2State = LOW;
  
  //Read outputs from switches and sensor
  int sensorValue = analogRead(LDR);   
  Bumper1State = digitalRead(Bumper1);
  Bumper2State = digitalRead(Bumper2);
  
  //If LDR output reads higher than threshold than stop the robot
  if (sensorValue > LT) {
    robotStop();
    delay(5000);
  }
  
  //If either bumper is triggered, backup up then turnaround
  if (Bumper1State == HIGH || Bumper2State == HIGH) {
    goBackwards();
    delay(1000);
    turnAround();
  }
}

//Function to tell the robot to move straight ahead
void goStraight(){
  ML->run(F);
  MR->run(F);
}

//Function to tell the robot to move backwards
void goBackwards() {
  ML->run(B);
  MR->run(B);
}

//Function to tell the robot to stop
void robotStop() {
  ML->run(S);
  MR->run(S);
}

//Function to tell the robot to turn around
void turnAround() {
  ML->run(F);
  MR->run(B);
  delay(1000);
}
