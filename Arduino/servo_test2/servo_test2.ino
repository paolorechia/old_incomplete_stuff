#include <Servo.h>

#define pino_servo 11

Servo servo;
int pulse = 5;
int pause = 1500;
int pos;

void setup() {

  pinMode(1, OUTPUT);
  servo.attach(pino_servo);
  Serial.begin(19200);
  Serial.println("Ready");
  servo.write(0);
}

void loop() {
 for(pos = 0; pos < 90; pos++)
  {
    servo.write(pos);
  delay(pulse);
  }
delay(pause);
  for(pos = 90; pos >= 0; pos--)
  {
    servo.write(pos);
    delay(pulse);
  }
  
  

}


