#include <DHT.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
#define DHTPIN 2// the output pin of DH11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int ldrPin = A0;
int ledPin=9;
void setup() {
  Serial.begin(9600);
 lcd.begin(16,2);
 dht.begin();
 
}

void loop() {
  
  int ldrStatus = analogRead(ldrPin);
 int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Serial.println("\n");
Serial.print(h);
Serial.println("\n");
Serial.print(t);
Serial.println("\n");
Serial.println("ldr=");
Serial.print(ldrStatus);


  lcd.print("Temp:");
  lcd.print(t);// display the temperature
  lcd.print((char)223);
  lcd.setCursor(0, 1);
  lcd.print("humi:");
  lcd.print(h); // display the humidity
  lcd.print(" ldr:");
  lcd.print(ldrStatus);
  delay(1000);
  lcd.clear();
   if (ldrStatus <= 200) {
digitalWrite(ledPin, HIGH);
  }
  else {
digitalWrite(ledPin, LOW);
  }
}
