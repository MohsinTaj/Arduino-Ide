#include <SPI.h>
#include <mcp2515.h>
#include <SD.h>
double bat_v = 0;
double bat_i = 0;
double soc = 0;


int period = 5000;
unsigned long time_now = 0;
 
struct can_frame canMsg;
struct can_frame canMsg1;
File myFile;
MCP2515 mcp2515(PA4);


void setup() {
   time_now = millis();
   canMsg1.can_id  = 0x18900140 | CAN_EFF_FLAG;
  canMsg1.can_dlc = 0;
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS,MCP_8MHZ);
  mcp2515.setNormalMode();
  
  Serial.println("------- CAN Read ----------");
   Serial.println("\nExample: Write to CAN");
  Serial.println("ID  DLC   DATA\n");
   Serial.print("Initializing SD card...");

  if (!SD.begin(PA15)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
   // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
//  myFile = SD.open("test.csv", FILE_WRITE);
//
//  // if the file opened okay, write to it:
//  if (myFile) {
//    Serial.print("Writing to test.txt...");
//   myFile.print(bat_v);
//    
//   myFile.print(bat_i); 
//   myFile.print(soc);
//     Serial.print(" ");
//    // close the file:
//    myFile.close();
//    Serial.println("done.");
//  } else {
//    // if the file didn't open, print an error:
//    Serial.println("error opening test.txt");
//  }
//
//  // re-open the file for reading:
//  myFile = SD.open("test.txt");
//  if (myFile) {
//    Serial.println("test.txt:");
//
//    // read from the file until there's nothing else in it:
//    while (myFile.available()) {
//      Serial.write(myFile.read());
//    }
//    // close the file:
//    myFile.close();
//  } else {
//    // if the file didn't open, print an error:
//    Serial.println("error opening test.txt");
//  }
}


void loop() {
   if(millis() >= time_now + period){
        time_now += period;
   
 
  mcp2515.sendMessage(&canMsg1);
  Serial.println("Messages sent");
  
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
      Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
//    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
//      Serial.print(canMsg.data[i],HEX);
//      Serial.print(" ");
//    }
 bat_v = 0;
      byte byte0 = canMsg.data[0];
      byte byte1 = canMsg.data[1];
      long x0 = (long)byte0<<8;
      long x1 = (long)byte1;
      bat_v = (x0 | x1)/10.0f;
      Serial.println(bat_v);
     

      bat_i = 0;
      byte byte4 = canMsg.data[4];
      byte byte5 = canMsg.data[5];
      long x4 = (long)byte4<<8;
      long x5 = (long)byte5;
      bat_i = ((x4 | x5)-30000)/10.0f;
      bat_i = bat_i;
      Serial.println(bat_i);

     

     
      soc = 0; // clear it out
      byte byte6 = canMsg.data[6];
      byte byte7 = canMsg.data[7];
      long x6 = (long)byte6<<8;
      long x7 = (long)byte7;
      soc = (x6 | x7)/10.0f;
      Serial.println(soc);

    Serial.println();      
  
 
}
 myFile = SD.open("test.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("voltage= ");
   myFile.print(bat_v);
//     myFile.println("\n");
     myFile.println("current= ");
   myFile.print(bat_i); 
//    myFile.println("\n");
    myFile.println("soc= ");
   myFile.print(soc);
    myFile.println("\n");
     Serial.print(" ");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.csv");
  if (myFile) {
    Serial.println("test.csv:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.csv");
  }
}
   }  
