#include <MsTimer2.h>

#include "TimerOne.h"

int trigPin = 3;    
int echoPin = 2;    
long duration, cm;

void setup()
{
  //ultrassonic interrupt
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  MsTimer2::set(20, sendPulse); // 500ms period
  MsTimer2::start();


  //led interrupt
  pinMode(13, OUTPUT);
  Timer1.initialize(1300000);         // initialize timer1
  Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(travaRoda);  // attaches callback() as a timer overflow interrupt

  
  Serial.begin (9600);
  
}
void sendPulse(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}

void travaRoda()
{
  digitalWrite(13, LOW);
  Timer1.initialize(200000);
  Timer1.attachInterrupt(desbloqueiaRoda);
}
void desbloqueiaRoda(){
  digitalWrite(13, HIGH);
  Timer1.initialize(1300000);         // initialize timer1
  Timer1.attachInterrupt(travaRoda);   // attaches callback2() as a timer overflow interrupt
}

long i = 0;

void loop()
{
}
