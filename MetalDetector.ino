#include "TimerOne.h"

// Global variables
int start_voltage;


// put your setup code here, to run once
void setup() 
{
  // Configure generator on pin 9
  // 5us = 200KHz
  pinMode(9, OUTPUT);
  Timer1.initialize(5); 
  Timer1.pwm(9, 512);

  // Start serial output
  Serial.begin(115200);

  // Wait for voltage to stabilize
  delay(500); 

  // beep a few times to indicate that we are on
  tone(3, 1000, 20);
  delay(200);
  tone(3, 1000, 20);
  delay(200);
  tone(3, 1000, 20);
    
  // Measure voltage
  start_voltage = ReadVoltage();
}


// put your main code here, to run repeatedly
void loop() 
{
  int read_voltage = ReadVoltage();
  int difference = abs(read_voltage - start_voltage);

  // print it
  if (difference> 0)
  {
    Serial.print("start ");  
    Serial.print(start_voltage);
    Serial.print(" read ");  
    Serial.print(read_voltage);
    Serial.print(" difference ");  
    Serial.println(difference); 
  }

  // beep based on difference
  if (difference > 3)
  {
    // continous beep
    tone(3, 1000, 100);
  }
  else if (difference > 1)
  {
    // medium beep
    tone(3, 1000, 50);
    delay(100);    
  }  
  else if (difference > 0)
  {
    // light beep
    tone(3, 1000, 20);
    delay(200);    
  }
}


// Read voltage from analog pin A0 and heavy average it
int ReadVoltage()
{
  long sum;
  sum = 0;
  
  for (int i=0; i<200; i++)
  {
    sum = sum + analogRead(A0);
  }
  return sum / 200;
}

