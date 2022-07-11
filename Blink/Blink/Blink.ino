int a=13;
int irs=6;
int ir=HIGH;
void setup()
{
  Serial.begin(9600);
  pinMode(a,OUTPUT);
  pinMode(irs,INPUT);
}
void loop()
{
  ir=digitalRead(irs);
  if(ir==LOW)
  {
    digitalWrite(a,HIGH);
    Serial.println("obstacle");
  }
  else{
     digitalWrite(a,LOW);
    Serial.println("CLEAR");
  }
  delay(500);
}
exit ();
