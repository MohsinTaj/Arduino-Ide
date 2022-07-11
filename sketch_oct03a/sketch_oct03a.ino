int value;
int enA;//Enable1 L298 Pin enA 
int in1; //Motor1  L298 Pin in1 
int in2; //Motor1  L298 Pin in1 
int in3; //Motor2  L298 Pin in1 
int in4; //Motor2  L298 Pin in1 
int enB; //Enable2 L298 Pin enB 
void forward();
void backward();

void setup() {
Serial.begin(9600);
pinMode(13, OUTPUT); // put your setup code here, to run once:
pinMode(10, OUTPUT); // declare as output for L298 Pin enA 
pinMode(9, OUTPUT); // declare as output for L298 Pin in1 
pinMode(8, OUTPUT); // declare as output for L298 Pin in2 
pinMode(7, OUTPUT); // declare as output for L298 Pin in3   
pinMode(6, OUTPUT); // declare as output for L298 Pin in4 
pinMode(5, OUTPUT); // declare as output for L298 Pin enB 
}
void loop() {
 // put your main code here, to run repeatedly:
if(Serial.available()>0)
 { 
 value= Serial.read(); // reading the data received from the bluetooth module
 Serial.println(13);
 Serial.print("\n");
if(value=='1' ){
void forword()  //forword
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
} 
if(value=='2' ){
void backword() //backword
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 

 }}
}
