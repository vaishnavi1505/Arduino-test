//motor of drilling machine connected to arduino is tested here with motor driver BTS7960


#include "BTS7960.h"

const uint8_t EN = 5;  //both enable pins are connected to 5 
const uint8_t L_PWM = 7;
const uint8_t R_PWM = 8;

BTS7960 motorController(EN, L_PWM, R_PWM);

void setup() 
{
}

void loop() 
{
  motorController.Enable();

  for(int speed = 0 ; speed < 255; speed+=10)
  {
  motorController.TurnLeft(speed);
  delay(100);
  }  

  motorController.Stop();
  
  for(int speed = 255 ; speed > 0; speed-=10)
  {
  motorController.TurnLeft(speed);
  delay(100);
  }  
  motorController.Stop();

  motorController.Disable();
  
  delay(5000);
}
