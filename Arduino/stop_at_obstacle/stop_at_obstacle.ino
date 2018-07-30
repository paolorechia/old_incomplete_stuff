#define size 64

int trigPin = 3;    //Trig - green Jumper
int echoPin = 2;    //Echo - yellow Jumper
int duration, cm, inches;
int distance = -1;
int vetor[size];
bool moving = false;
//motor A
int enA = 10;
int in1 = 7;
int in2 = 6;

//motor B
int enB = 9;
int in3 = 5;
int in4 = 4;

int i;

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
  setup_engines();
  Serial.begin (9600);
  i = 0;
}

long sensor(int i){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
//  delay(250);
  if (cm > 2000)
    cm = -1;
  vetor[i] = cm;
}

void setup_engines(){
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turn_on(){
  // liga motor A
  digitalWrite(enA, HIGH);
  // liga motor B
  digitalWrite(enB, HIGH);
}

void speed(int x){
  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
  delay(x);
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
}

void stop(){
   // desliga motores
  digitalWrite(in2, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

int estimate_distance(){
  int aux;
  for (int j = 0; j < size; j++){
    for (int k = j + 1; k < size; k++)
      if (vetor[j] > vetor[k]){
        aux=vetor[j];
        vetor[j]=vetor[k];
        vetor[k]=aux;
      }
  }
  return vetor[size/2];
}

void loop() {
  i++;
  i%= size;
  sensor(i);
  if (i == 0){
    distance = estimate_distance();
    Serial.println(distance);
  }
  if (distance > 0){
    if (distance < 30){
      if (moving == true){
        stop();
        Serial.println(" Stop!");
        moving = false;
      }
    }
    else{
      if (moving == false){
        turn_on();
        moving = true;
        Serial.println("Turn on!");
      }
    }
  }
}
