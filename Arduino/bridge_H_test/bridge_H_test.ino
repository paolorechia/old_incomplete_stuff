//motor A
int enA = 10;
int in1 = 7;
int in2 = 6;

//motor B
int enB = 9;
int in3 = 5;
int in4 = 4;


void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void demoA() {
  // liga motor A
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
  analogWrite(enA, 255);


  // liga motor B
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);

  // regula velocidade (0~255)
  analogWrite(enB, 255);

  delay(2000);
  // desliga motor
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void loop() {
  demoA();
  delay(1000);
}
