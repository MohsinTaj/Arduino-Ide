// include the library code:
#include<LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int RS = D2, EN = D3, d4 = D5, d5 = D6, d6 = D7, d7 = D8;

// if you use the NodeMCU 12E the suggested pins are
// const int RS = 4, EN = 0, d4 = 12 , d5 = 13, d6 = 15, d7 = 3;

LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

void setup() {
// set up the LCD's number of columns and rows:
lcd.begin(16, 2);
// Print a message to the LCD.
lcd.print("hello, world!");
}

void loop() {
// set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0):
lcd.setCursor(0, 1);
// print the number of seconds since reset:
lcd.print(millis() / 1000);
}
