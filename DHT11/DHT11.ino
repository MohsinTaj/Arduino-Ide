int motorpin1 = 9 ;
int motorpin2 = 8 ;
int motorpin3 = 7 ;
int motorpin4 = 6 ;
int enable1 = 10 ;
int enable2 = 5 ;
void fwd();
void bckwd();
void turnright();
void turnleft();
void stop();
void setup() {
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  pinMode(motorpin3, OUTPUT);
  pinMode(motorpin4, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
}
void loop() {
  fwd();
  delay(3000);
  Serial.print("Motor is running forward");
  bckwd();
  delay(3000);
  Serial.print("Motor is running backward");
  turnright();
  delay(3000);
  Serial.print("Motor is turningright");
  turnleft();
  delay(3000);
  Serial.print("Motor is turningleft");
  stop();
  delay(3000);
  Serial.print("Motor is stopped");
}
void fwd() {
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);
  analogWrite(enable1, 255);
  analogWrite(enable2, 255);
}
void bckwd()
{
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);
  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);
  analogWrite(enable1, 255);
  analogWrite(enable2, 255);
}
void turnright()
{
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);
  analogWrite(enable1, 255);
  analogWrite(enable2, 255);
}
void turnleft()
{
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);
  analogWrite(enable1, 255);
  analogWrite(enable2, 255);
}
void stop()
{
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, LOW);
}
