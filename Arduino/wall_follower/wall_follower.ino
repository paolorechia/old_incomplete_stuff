#include <MsTimer2.h>

#include "TimerOne.h"

#define N 14
int trigPin = 3;    
int echoPin = 2;    
int pulseArray[N];
int i;
int distance = 0;
int obstacleCount = 0;
long duration, cm;

bool blocked = false;
bool moving = false;
//motor A
int enA = 10;
int in1 = 7;
int in2 = 6;

//motor B
int enB = 12;
int in3 = 5;
int in4 = 4;

void setup(){
//  engines setup
//  pinMode(enA, OUTPUT);
//  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  setup_engines();

  //ultrassonic interrupt
  //Define inputs and outputs
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  MsTimer2::set(20, sendPulse); // 20ms period
  MsTimer2::start();


  //engines interrupt
  pinMode(13, OUTPUT);
  Timer1.initialize(1300000);         // initialize timer1
  Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(travaRoda);  // attaches callback() as a timer overflow interrupt

  
  Serial.begin (9600);
  
}


// engines functions
void setup_engines(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turn_off(){
   // desliga motores
  if (moving){
    // desliga motor A
    digitalWrite(enA, LOW);
    // desliga motor B
    digitalWrite(enB, LOW);
    moving = false;
  }
}
void turn_on(){
  if (!moving && !blocked){
    // liga motor A
    digitalWrite(enA, HIGH);
    // liga motor B
    digitalWrite(enB, HIGH);
    moving = true;
  }
}

void turn(char side, int t = 1000){
  // turn right
  if (moving){
    if (side == "r"){
        digitalWrite(enA, LOW);
        delay(t);
        digitalWrite(enA, HIGH);
      }
      // turn left
      else if (side == "l"){
        digitalWrite(enB, LOW);
        delay(t);
        digitalWrite(enB, HIGH);
      }
        // invalid argument
      else
        return;
    }
  else{
    if (side == "r"){
      digitalWrite(enA, LOW);
      digitalWrite(enB, HIGH);
      delay(t);     
      digitalWrite(enB, LOW);
      }
      // turn left
      else if (side == "l"){
        digitalWrite(enB, LOW);
        digitalWrite(enA, HIGH);

        delay(t);
        digitalWrite(enA, LOW);
      }
        // invalid argument
      else
        return;
    }
}
void travaRoda(){
  // desliga BUILDIN_LED por diversao
  digitalWrite(13, LOW);
  // desliga motorB e marca como bloqueado
  blocked = true;
  digitalWrite(enB, LOW);
  Timer1.initialize(200000);
  Timer1.attachInterrupt(desbloqueiaRoda);
}
void desbloqueiaRoda(){
  // reativa LED por diversao
  digitalWrite(13, HIGH);
  // desbloqueia roda e reativa motorB se veiculo estiver em movimento
  blocked = false;
  if (moving){
    digitalWrite(enB, HIGH);
  }
  Timer1.initialize(2100000);         // initialize timer1
  Timer1.attachInterrupt(travaRoda);   // attaches callback2() as a timer overflow interrupt
}

// ultrassonic functions
void sendPulse(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  int distance = (duration/2) / 29.1;
    pulseArray[i] = distance;
    i++;
    i %= N;
}

int estimateDistance(){
  int aux;
  for (int j = 0; j < N; j++){
    for (int k = j + 1; k < N; k++)
      if (pulseArray[j] > pulseArray[k]){
        aux=pulseArray[j];
        pulseArray[j]=pulseArray[k];
        pulseArray[k]=aux;
      }
  }
  return pulseArray[N/2];
}



void loop(){
  if (i == N - 1){
    distance = estimateDistance();
    Serial.print("Distance : ");
    Serial.println(distance);

  }
   if (distance < 30 && obstacleCount  < 300){
        turn_off();
  //      Serial.println("Turn off!");
        obstacleCount++;

    }
   else if (distance >= 30){
        turn_on();
        obstacleCount = 0;
  //      Serial.println("Turn on!");
   }
   if (obstacleCount == 300){
      digitalWrite(enA, LOW);
      digitalWrite(enB, HIGH);

   }

}
