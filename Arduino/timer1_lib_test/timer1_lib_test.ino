 
#include "TimerOne.h"
 
void setup()
{
  pinMode(13, OUTPUT);
  Timer1.initialize(1000000);         // initialize timer1, and set a 1/2 second period
//  Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}
 
void callback()
{
  digitalWrite(13, digitalRead(13) ^ 1);
}
 
void loop()
{
  // your program here...
}
