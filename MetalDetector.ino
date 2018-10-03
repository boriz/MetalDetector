#include "TimerOne.h"

void setup() 
{
  // put your setup code here, to run once:  
  pinMode(9, OUTPUT);
  Timer1.initialize(4); // 4us = 250KHz
  Timer1.pwm(9, 512);
  Serial.begin(115200);
}


void loop() 
{
  // put your main code here, to run repeatedly:
      
  Serial.println(analogRead(A0));   
  delay(500); 

  //tone(9,100000);
  // delayMicroseconds(200);
 
}
