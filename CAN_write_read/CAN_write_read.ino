#include <SPI.h>
#include "mcp2515_can.h"
const int SPI_CS_PIN = 10;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
unsigned char flagRecv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];
void setup() {
   Serial.begin(9600);
   while(!Serial){};
   // init can bus : baudrate = 500k
   while (CAN_OK != CAN.begin(CAN_250KBPS)) {
      Serial.println("CAN init fail, retry...");
      delay(100);
   }
   Serial.println("CAN init ok waiting for msg!\n");
   delay(1000);
}
unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  void MCP2515_ISR() {
   flagRecv = 1;
}

void loop() {
//    send data: id = 0x00, standrad frame, data len = 8, stmp: data buf
   stmp[7] = stmp[7] + 1;
   if (stmp[7] == 100) {
      stmp[7] = 0;
      stmp[6] = stmp[6] + 1;
      if (stmp[6] == 100) {
         stmp[6] = 0;
         stmp[5] = stmp[5] + 1;
      }
   }
   CAN.sendMsgBuf(0x18900140, 0, 0, stmp);
   delay(1000); // send data per 100ms
   Serial.println("CAN BUS sendMsgBuf ok!");
   
if (flagRecv) {
      // check if get data
      flagRecv = 0; // clear flag
      Serial.println("into loop");
      // iterate over all pending messages
      // If either the bus is saturated or the MCU is busy,
      // both RX buffers may be in use and reading a single
      // message does not clear the IRQ conditon.
      while (CAN_MSGAVAIL == CAN.checkReceive()) {
         // read data, len: data length, buf: data buf
         Serial.println("checkReceive");
         CAN.readMsgBuf(&len, buf);
         // print the data
         for (int i = 0; i < len; i++) {
            Serial.print(buf[i]); Serial.print("\t");
         }
         Serial.println();
      }}
      else{
        Serial.println("error\n");
        Serial.print(flagRecv);
        Serial.println("\n");
        }
        }
      
    
