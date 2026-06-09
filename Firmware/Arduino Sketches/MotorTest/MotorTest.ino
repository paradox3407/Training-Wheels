// declaring pins
const int pwm1 = 3; 
const int int1 = 4; 
const int int2 = 5; 
const int pwm2 = 6; 
const int int3 = 7; 
const int int4 = 8; 

void setup() {
  // declaring pin modes
  pinMode(pwm1, OUTPUT);
  pinMode(int1, OUTPUT);
  pinMode(int2, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(int3, OUTPUT);
  pinMode(int4, OUTPUT);

  // setting direction 
  digitalWrite(int1, HIGH);
  digitalWrite(int2, LOW);
  digitalWrite(int3, LOW);
  digitalWrite(int4, HIGH);

  analogWrite(pwm1, 100);
  analogWrite(pwm2, 100);
}

void loop() {
  // put your main code here, to run repeatedly:

}
