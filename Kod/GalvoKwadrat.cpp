#include <PID_v1.h>


const int encoderPinA = 2;   
const int encoderPinB = 3;   
const int motorPin = 9;     


double Setpoint = 0;        
double Input = 0;           
double Output = 0;          


double Kp = 1.0;           
double Ki = 0.0;            
double Kd = 0.0;            


PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

const int sideLength = 100; 
int currentPosition = 0;    
int targetPosition = 0;     

void setup() {

    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);
    pinMode(motorPin, OUTPUT);

    pid.SetMode(AUTOMATIC);  


    pid.SetOutputLimits(-255, 255);

}

void loop() { // kwadrat 
    if (currentPosition == targetPosition) {
        
        if (currentPosition == 0) {
            targetPosition = sideLength;         // Skręt w prawo
        }
        else if (currentPosition == sideLength) {
            targetPosition = 2 * sideLength;     // Skręt w dół
        }
        else if (currentPosition == 2 * sideLength) {
            targetPosition = 3 * sideLength;     // Skręt w lewo
        }
        else if (currentPosition == 3 * sideLength) {
            targetPosition = 0;                   // skręt w gorę
        }
    }


    int encoderValue = digitalRead(encoderPinA);

    currentPosition = encoderValue;

    Input = currentPosition;

 
    pid.Compute();

 
    if (Output >= 0) {
        analogWrite(motorPin, Output);   
    }
    else {
        analogWrite(motorPin, -Output);  
    }

    delay(10);  
}

/*void loop() //trojkąt  {

  
  if (currentPosition == targetPosition) {
   
    if (currentPosition == 0) {
      targetPosition = sideLength;         // Ruch w przód
    } else if (currentPosition == sideLength) {
      targetPosition = -sideLength;        // Ruch w tył
    } else if (currentPosition == -sideLength) {
      targetPosition = 0;                   // Powrót na początek
    }
  }


 int encoderValue = digitalRead(encoderPinA);

    currentPosition = encoderValue;

    Input = currentPosition;

 
    pid.Compute();

 
    if (Output >= 0) {
        analogWrite(motorPin, Output);   
    }
    else {
        analogWrite(motorPin, -Output);  
    }

    delay(10);  
}
*/
