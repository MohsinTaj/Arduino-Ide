#include <SD.h>
#include <SPI.h>
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
File myFile;

PZEM004Tv30 pzem(SDA, SCL);
//SoftwareSerial pzemSWSerial(10,9);
int pinCS = 10; // Pin 10 on Arduino Uno

void setup() {
    
  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
   
}
void loop() {
   float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    // Check if the data is valid
    if(isnan(voltage)){
        voltage=20;
    } else if (isnan(current)) {
        current=30;
    }
  Serial.print(float(pzem.voltage()));
  Serial.print(",");
  Serial.print(float(pzem.current()));
 
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {    
    myFile.print(float(pzem.voltage()));
    myFile.print(",");    
    myFile.print(float(pzem.current()));
    myFile.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
  delay(3000);
}
