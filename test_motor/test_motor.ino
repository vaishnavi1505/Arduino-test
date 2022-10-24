// PINOUT
// L_EN -> 6
// R_EN -> 5
// L_PWM -> 9
// R_PWM -> 10
 
#include "BTS7960.h"

const uint8_t R_EN = 5;
const uint8_t L_EN = 6;
const uint8_t L_PWM = 9;
const uint8_t R_PWM = 10;

BTS7960 motor1(L_EN, R_EN, L_PWM, R_PWM);

void setup() 
{
  Serial.begin(9600);

 
}

void loop() 
{
  motor1.Enable();
  

  for(int speed = 0 ; speed < 255; speed+=10)
  {
  motor1.TurnLeft(speed);
  delay(100);
  }  

  motor1.Stop();
  
  for(int speed = 255 ; speed > 0; speed-=10)
  {
  motor1.TurnLeft(speed);
  delay(100);
  }  
  motor1.Stop();

  motor1.Disable();
  
  delay(5000);
}
