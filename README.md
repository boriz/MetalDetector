# MetalDetector
Simple Arduino-based metal detector.  
The antenna is 250mm x 70mm piece of cardboard with approximately 50 turns of 32AWG (0.2mm) wire. Measured antenna inductance is ~1mH.  

Schematic of the device is below:  

![](Schematic.PNG)  

Arduino pin 9 is configured to output 20KHz (50us period) square wave, this AC voltage fed to top of the R3/L1 network.  
At 20KHz the reactance of the inductor is X = 2*pi*f*L1 = 125 Ohms. With R3 resistor, the L1 reactance forms an AC voltage divider.  
By placing a piece of metal near the inductor L1, we are changing its inductance/reactance, and consequently the output voltage of the divider.  
To measure the output voltage of the R3/L1 network, we rectify it with the diode D1 and filter with RC network C1/R2. The resulting DC voltage is sampled by the Arduino ADC (pin A0). This voltage is proportional to the inductance of the L1 and would change if we place a metal nearby.  
Arduino pin 4 is connected to an external LED.  
And pin 3 is connected to a piezo speaker.

Arduino code is very basic.  
Upon boot it samples ADC voltage and uses it as a staring point.  
It continuously samples ADC and if it drifts away from the starting point, the device beeps.
Note: Arduino code is using TimerOne library, you can install it via Sketch/Include Libraries menu.  

Pictures of the actual device are below.  

Coil, Main Board and Arduino Pro-Mini 
![](Coil.jpg)

Arduino and Main Board 
![](ArduinoMainBoard.jpg)

Assembled device (cardboard, hot glue and fancy power switch)
![](Assemble_01.jpg)

