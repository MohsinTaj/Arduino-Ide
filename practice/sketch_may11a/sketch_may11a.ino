#include <SPI.h>
#include "mcp2515_can.h"
const int SPI_CS_PIN = 10;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
unsigned char flagRecv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];
void setup() {
   Serial.begin(115200);
   while(!Serial){};
   // init can bus : baudrate = 500k
   while (CAN_OK != CAN.begin(CAN_500KBPS)) {
      Serial.println("CAN init fail, retry...");
      delay(100);
   }
   Serial.println("CAN init ok!");
}
unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
void loop() {
   // send data: id = 0x00, standrad frame, data len = 8, stmp: data buf
   stmp[7] = stmp[7] + 1;
   if (stmp[7] == 100) {
      stmp[7] = 0;
      stmp[6] = stmp[6] + 1;
      if (stmp[6] == 100) {
         stmp[6] = 0;
         stmp[5] = stmp[5] + 1;
      }
   }
   CAN.sendMsgBuf(0x00, 0, 8, stmp);
    CAN.readMsgBuf(&len, buf);
   delay(100); // send data per 100ms
   Serial.println("CAN BUS sendMsgBuf ok!");
}
