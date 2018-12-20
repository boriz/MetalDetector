#include "TimerOne.h"

// Initialize global constants
const int TIMER_PERIOD_US = 50; // Frequency generator period in microseconds
const int GEN_PIN = 9;          // Frequency generator pin
const int LED_PIN = 4;          // LED pin
const int SPEAKER_PIN = 3;      // Speaker pin
const int SPEAKER_FREQ = 1000;  // Beep frequency
const int FB_PIN = A0;          // Analog feedback pin
const int THRESHOLD1 = 1;       // Slow beeep ADC/voltage threshold 
const int THRESHOLD2 = 2;       // Medium beep ADC/voltage threshold 
const int THRESHOLD3 = 4;       // Continous beep ADC/voltage threshold 
const int SERIAL_BAUD = 115200; // Serial port baudrate
const int AVG_COUNT = 200;      // How many times to read/average ADC voltage


// Global variables
int start_voltage;


// put your setup code here, to run once
void setup() 
{
  // Configure output pins
  pinMode(GEN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Configure generator to selected frequency and 50% duty cycle
  Timer1.initialize(TIMER_PERIOD_US); 
  Timer1.pwm(GEN_PIN, 512);

  // Start serial output
  Serial.begin(SERIAL_BAUD);

  // Wait for voltage to stabilize
  delay(100); 

  // beep to indicate that we are on
  digitalWrite(LED_PIN, HIGH);
  tone(SPEAKER_PIN, SPEAKER_FREQ, 3000);
  delay(2000);
  digitalWrite(LED_PIN, LOW);
      
  // Calibrate voltage
  delay(100);
  start_voltage = ReadVoltage();
}


// Main functionality
void loop() 
{
  // Reads current voltage level
  int read_voltage = ReadVoltage();
  
  // Compare to the start voltage
  int difference = abs(read_voltage - start_voltage);
  
  // print it if above minimum threshold
  if (difference> THRESHOLD1)
  {
    Serial.print("start "); 
    Serial.print(start_voltage);
    Serial.print(" read ");  
    Serial.print(read_voltage);
    Serial.print(" difference ");  
    Serial.println(difference); 
  }

  // beep based on difference
  if (difference > THRESHOLD3)
  {
    // continous beep
    digitalWrite(LED_PIN, HIGH);
    tone(SPEAKER_PIN,SPEAKER_FREQ, 100);
  }
  else if (difference > THRESHOLD2)
  {
    // medium beep
    digitalWrite(LED_PIN, HIGH);
    tone(SPEAKER_PIN, SPEAKER_FREQ, 50);
    delay(50);
    digitalWrite(LED_PIN, LOW);
    delay(50);    
  }  
  else if (difference > THRESHOLD1)
  {
    // light beep
    digitalWrite(LED_PIN, HIGH);
    tone(SPEAKER_PIN, SPEAKER_FREQ, 20);
    delay(20);
    digitalWrite(LED_PIN, LOW);
    delay(180);    
  }
  else 
  {
    // Pull LED off if no metal is dtected
    digitalWrite(LED_PIN, LOW);
  }
}


// Read voltage from analog pin A0 and heavy average it
int ReadVoltage()
{
  long sum;
  sum = 0;
  
  for (int i=0; i < AVG_COUNT; i++)
  {
    sum = sum + analogRead(FB_PIN);
  }
  return sum / AVG_COUNT;
}
