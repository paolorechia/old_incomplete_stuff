int trigPin = 3;    //Trig - green Jumper
int echoPin = 2;    //Echo - yellow Jumper
long duration, cm, inches;
long distance;
bool moving = false;
//motor A
int enA = 10;
int in1 = 7;
int in2 = 6;

//motor B
int enB = 9;
int in3 = 5;
int in4 = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
//  pinMode(enA, OUTPUT);
//  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

long sensor(){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
//  delay(250);
  return cm;
}

void turn_on(){
  // liga motor A
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  // liga motor B
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
  moving = true;
}

void stop(){
   // desliga motores
  digitalWrite(in2, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  moving = false;
}


void loop() {
  distance = sensor();
  if (distance < 150 && distance > 20){
    if (!moving){
      turn_on();
    }
  }
  else{
    stop();
  }
}
