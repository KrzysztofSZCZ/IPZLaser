#include <PID_v1.h>

const int encoder1PinA = 2;
const int encoder1PinB = 3;
const int motor1Pin = 9;

const int encoder2PinA = 4;
const int encoder2PinB = 5;
const int motor2Pin = 10;

double Setpoint1 = 0;
double Input1 = 0;
double Output1 = 0;

double Setpoint2 = 0;
double Input2 = 0;
double Output2 = 0;

PID pid1(&Input1, &Output1, &Setpoint1, 1.0, 0.0, 0.0, DIRECT);
PID pid2(&Input2, &Output2, &Setpoint2, 1.0, 0.0, 0.0, DIRECT);

const int sideLength = 100;
int currentPosition1 = 0;
int currentPosition2 = 0;
int targetPosition1 = 0;
int targetPosition2 = 0;

void setup() {
  pinMode(encoder1PinA, INPUT);
  pinMode(encoder1PinB, INPUT);
  pinMode(encoder2PinA, INPUT);
  pinMode(encoder2PinB, INPUT);
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);

  pid1.SetMode(AUTOMATIC);
  pid2.SetMode(AUTOMATIC);

  pid1.SetOutputLimits(-255, 255);
  pid2.SetOutputLimits(-255, 255);
}

void loop() {
  if (currentPosition1 == targetPosition1 && currentPosition2 == targetPosition2) {
    if (currentPosition1 == 0 && currentPosition2 == 0) {
      targetPosition1 = sideLength;
      targetPosition2 = 0;
    } else if (currentPosition1 == sideLength && currentPosition2 == 0) {
      targetPosition1 = sideLength;
      targetPosition2 = sideLength;
    } else if (currentPosition1 == sideLength && currentPosition2 == sideLength) {
      targetPosition1 = 0;
      targetPosition2 = sideLength;
    } else if (currentPosition1 == 0 && currentPosition2 == sideLength) {
      targetPosition1 = 0;
      targetPosition2 = 0;
    }
  }

  int encoder1Value = digitalRead(encoder1PinA);
  int encoder2Value = digitalRead(encoder2PinA);

  Input1 = encoder1Value;
  Input2 = encoder2Value;

  currentPosition1 = encoder1Value;
  currentPosition2 = encoder2Value;

  pid1.Compute();
  pid2.Compute();

  if (Output1 >= 0) {
    analogWrite(motor1Pin, Output1);
  } else {
    analogWrite(motor1Pin, -Output1);
  }

  if (Output2 >= 0) {
    analogWrite(motor2Pin, Output2);
  } else {
    analogWrite(motor2Pin, -Output2);
  }
}
