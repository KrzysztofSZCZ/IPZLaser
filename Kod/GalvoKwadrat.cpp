#include <PID_v1.h>

#define MOTOR_PIN_1A 32
#define MOTOR_PIN_1B 25
#define MOTOR_PIN_2A 26
#define MOTOR_PIN_2B 14
#define PWM1 33
#define PWM2 27
#define MOTOR_PWM_FREQ 5000  


double Setpoint1 = 0;
double Input1 = 0;
double Output1 = 0;

double Setpoint2 = 0;
double Input2 = 0;
double Output2 = 0;

PID pid1(&Input1, &Output1, &Setpoint1, 1.0, 0.5, 0.5, DIRECT);
PID pid2(&Input2, &Output2, &Setpoint2, 1.0, 0.5, 0.5, DIRECT);

const int sideLength = 100;
int currentPosition1 = 0;
int currentPosition2 = 0;
int targetPosition1 = 0;
int targetPosition2 = 0;

void setup() {
  pinMode(MOTOR_PIN_1A, OUTPUT);
  pinMode(MOTOR_PIN_2A, OUTPUT);
  pinMode(MOTOR_PIN_1B, OUTPUT);
  pinMode(MOTOR_PIN_2B, OUTPUT);

  ledcSetup(0, MOTOR_PWM_FREQ, 8);
  ledcSetup(1, MOTOR_PWM_FREQ, 8);
  ledcAttachPin(MOTOR_PIN_1A, 0);
  ledcAttachPin(MOTOR_PIN_1B, 1);
  ledcAttachPin(MOTOR_PIN_2A, 2);
  ledcAttachPin(MOTOR_PIN_2B, 3);


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

  int encoder1Value = digitalRead(MOTOR_PIN_1A);
  int encoder2Value = digitalRead(MOTOR_PIN_2A);

  Input1 = encoder1Value;
  Input2 = encoder2Value;

  currentPosition1 = encoder1Value;
  currentPosition2 = encoder2Value;

  pid1.Compute();
  pid2.Compute();

  if (Output1 >= 0) {
    analogWrite(MOTOR_PIN_1, Output1);
  } else {
    analogWrite(MOTOR_PIN_1, -Output1);
  }

  if (Output2 >= 0) {
    analogWrite(MOTOR_PIN_1, Output2);
  } else {
    analogWrite(MOTOR_PIN_2, -Output2);
  }
}
