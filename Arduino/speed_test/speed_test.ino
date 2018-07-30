#define size 64
#define LOOP 2048

int LED = 13;
int trigPin = 3;    //Trig - green Jumper
int echoPin = 2;    //Echo - yellow Jumper
int duration, cm, inches;
int distance = -1;
int vetor[size];
bool moving = false;
//motor A (== right)
int enA = 10;
int in1 = 7;
int in2 = 6;

//motor B (== left)
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
  pinMode(LED, OUTPUT);
  setup_engines();
  turn_on();
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
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
//  delay(250);
  if (cm > 2000)
    cm = -1;
  vetor[i] = cm;
}

void setup_engines(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turn_on(){
  // liga motor A
  digitalWrite(enA, HIGH);
  // liga motor B
  digitalWrite(enB, HIGH);
}

void speedA(int x){
  digitalWrite(enA, LOW);
  delayMicroseconds(x);
  digitalWrite(enA, HIGH);
}
void speedB(int x){
  digitalWrite(enB, LOW);
  delayMicroseconds(x);
  digitalWrite(enB, HIGH);
}
void turn(int angulo){

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

void loop(){
   delay(1300);
   digitalWrite(enB, LOW);
   delay(200);
   digitalWrite(enB, HIGH);
}
