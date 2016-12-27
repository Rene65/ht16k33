/****************************************************************
 * Simple test of ht16k33 library turning on and off LEDs
 */

#include "ht16k33.h"
#include <Wire.h>

// Define the class
HT16K33 HT;

/****************************************************************/
void setup() {
  Serial.begin(9600);
  Serial.println(F("ht16k33 light test v0.02"));
  Serial.println();
  // initialize everything, 0x00 is the i2c address for the first one (0x70 is added in the class).
  HT.begin(0x00);
}

/****************************************************************/
void loop() {
  uint8_t led;

  Serial.println(F("Turn on all LEDs"));
  // first light up all LEDs
  for (led=0; led<128; led++) {
    HT.setLedNow(led);
    delay(10);
  } // for led

  Serial.println(F("Clear all LEDs"));
  //Next clear them
  for (led=0; led<128; led++) {
    HT.clearLedNow(led);
    delay(10);
  } // for led

  //Now do one by one, slowly, and print out which one
  for (led=0; led<128; led++) {
    HT.setLedNow(led);
    Serial.print(F("Led no "));
    Serial.print(led,DEC);
    Serial.print(F(": On"));
    delay(100);
    HT.clearLedNow(led);
    Serial.println(F(" Off"));
  } // for led

  Serial.println(F("Function 7segment hexadecimal and write direct to display without sendled() test"));
  HT.clearAll();
  boolean decimalpoint = true;
  for (int n=0; n<16; n++) {
    if (n == 3 or n ==5) {decimalpoint = true;} else {decimalpoint = false;} //Decimal point test
    HT.set7SegNow(0,n, decimalpoint);
    delay(1000);
    }
  delay(5000);

  Serial.println(F("Function 7segment counter test"));
  HT.clearAll();
  delay(2000);
  for (unsigned long n=0; n<100000000; n++) {
    HT.set7Seg(0,(n/10000000)%10, false);
    HT.set7Seg(1,(n/1000000)%10, false);
    HT.set7Seg(2,(n/100000)%10, false);
    HT.set7Seg(3,(n/10000)%10, false);
    HT.set7Seg(4,(n/1000)%10, false);
    HT.set7Seg(5,(n/100)%10, false);
    HT.set7Seg(6,(n/10)%10, false);
    HT.set7Seg(7,n%10, false);
    HT.sendLed();
    //delay(5);
    }
  delay(5000);

  Serial.println(F("Function 7segment custom text test"));
  HT.clearAll();
  HT.set7Seg(0,10, false);     //a
  HT.set7SegRaw(1, 0b01010000); //r
  HT.set7Seg(2,13, false);     //d
  HT.set7SegRaw(3, 0b00011100); //u
  HT.set7SegRaw(4, 0b00000100); //i
  HT.set7SegRaw(5, 0b01010100); //n
  HT.set7SegRaw(6, 0b01011100); //o
  HT.sendLed();
  delay(5000);

} // loop  
    
