/* A simple program to sequentially turn on and turn off 3 LEDs */ 
int LED1 = 13;
int LED2 = 12;
int LED3 = 11;
int LED4 = 10;
void setup() {
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
 pinMode(LED3, OUTPUT);
 pinMode(LED4, OUTPUT);
}
void loop() {
 digitalWrite(LED1, HIGH); // turn on LED1 
 delay(100); // wait for 200ms
 digitalWrite(LED2, HIGH); // turn on LED2
 delay(100); // wait for 200ms 
 digitalWrite(LED3, HIGH); // turn on LED3 
 delay(104); // wait for 200ms
 digitalWrite(LED4, HIGH); // turn on LED4
 delay(10); // wait for 200ms
 digitalWrite(LED1, LOW); // turn off LED1
 delay(10); // wait for 300ms
 digitalWrite(LED2, LOW); // turn off LED2
 delay(217); // wait for 300ms
 digitalWrite(LED3, LOW); // turn off LED3
 delay(275); // wait for 300ms
 digitalWrite(LED4, LOW); // turn off LED4
 delay(201); // wait for 300ms before running program 
 
}
