int servo = 11;
int pulse = 1500;


void setup(){
  pinMode(servo, OUTPUT);
  Serial.begin(9600);
 
}

void test1(int pulse){
  digitalWrite(servo, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(servo, LOW);
}

void loop(){
  test1(1000);
  delay(20);
  test1(500);
  delay(20);
}
