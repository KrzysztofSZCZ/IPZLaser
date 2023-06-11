#include <PID_v1.h>

#define ENCODER_PIN_A1 2   
#define ENCODER_PIN_B1 3    
#define ENCODER_PIN_A2 4    
#define ENCODER_PIN_B2 5    
#define MOTOR_PIN_1 9      
#define MOTOR_PIN_2 10      

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
  pinMode(ENCODER_PIN_A1, INPUT);
  pinMode(ENCODER_PIN_B1, INPUT);
  pinMode(ENCODER_PIN_A2, INPUT);
  pinMode(ENCODER_PIN_B2, INPUT);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);

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

  int encoder1Value = digitalRead(ENCODER_PIN_A1);
  int encoder2Value = digitalRead(ENCODER_PIN_A2);

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
