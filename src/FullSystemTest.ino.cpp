# 1 "/tmp/tmp4auxvysw"
#include <Arduino.h>
# 1 "/home/hephaestus/git/RBE1001LibTemplate/src/FullSystemTest.ino"
#include <Arduino.h>
#include <RBE1001Lib.h>
#include "Motor.h"
#include "Rangefinder.h"
#include <ESP32Servo.h>
#include <ESP32AnalogRead.h>

Motor left_motor;
Motor right_motor;

Rangefinder rangefinder1;

Servo lifter;

ESP32AnalogRead leftLineSensor;
ESP32AnalogRead rightLineSensor;
ESP32AnalogRead servoPositionFeedback;
bool upDown=false;
void setup();
void loop();
#line 23 "/home/hephaestus/git/RBE1001LibTemplate/src/FullSystemTest.ino"
void setup() {

  Serial.begin(115200);
  Motor::allocateTimer(0);
  ESP32PWM::allocateTimer(1);

  right_motor .attach(MOTOR_RIGHT_PWM, MOTOR_RIGHT_DIR, MOTOR_RIGHT_ENCA, MOTOR_RIGHT_ENCB);
  left_motor .attach(MOTOR_LEFT_PWM, MOTOR_LEFT_DIR, MOTOR_LEFT_ENCA, MOTOR_LEFT_ENCB);
  rangefinder1 .attach(SIDE_ULTRASONIC_TRIG, SIDE_ULTRASONIC_ECHO);
  lifter .attach(SERVO_PIN);
  leftLineSensor .attach(LEFT_LINE_SENSE);
  rightLineSensor .attach(RIGHT_LINE_SENSE);
  servoPositionFeedback .attach(SERVO_FEEDBACK_SENSOR);

}






void loop() {
 upDown=!upDown;
 int loopTime = 4000;
 int servoRange =180;

 right_motor.setSetpointWithSinusoidalInterpolation(upDown?360:0, loopTime);
 left_motor.setSetpointWithLinearInterpolation(upDown?360:0, loopTime);

 for(int i=0;i<servoRange;i++){
  delay(loopTime/servoRange);
  Serial.println("\n");
  Serial.print("Range 1 "+String(rangefinder1.getDistanceCM()));


  Serial.print("\tCount 1 "+String(left_motor.getCurrentDegrees())+
      "\t Count 2 "+String(right_motor.getCurrentDegrees()));
  Serial.print("\t Line left "+String(leftLineSensor.readVoltage()));

  Serial.print( "\t Line right "+String(rightLineSensor.readVoltage()));
  Serial.print("\t Servo Read "+String(servoPositionFeedback.readVoltage()));
  Serial.print("\t Servo write "+String(i));
  lifter.write(i);
 }




 }