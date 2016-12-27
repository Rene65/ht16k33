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
  Serial.println(F("Function 8x8 display direct alphabet"));
  for (int n=10; n<41; n++) {
    Serial.println(n);
    HT.set8x8MatrixNow(0,n);
    HT.set8x8MatrixNow(1,n);
    delay(1000);
    }

  delay(5000);

  Serial.println(F("Function writing characters"));
  String teststring = "HT16K33";
  for (int n=0; n<teststring.length(); n++) {
    HT.set8x8MatrixChar(0, teststring[n]);
    HT.set8x8MatrixChar(1, teststring[n]);
    delay(1000);
  }

  delay(5000);

  Serial.println(F("Function 8x8 matrix test scroll up"));
  for (int n=0; n<10; n++) {
    Serial.println(n);
    //HT.set8x8Matrix(0,n);
    HT.set8x8MatrixScrollUp(0,n, 50); //speed = 50ms
    HT.set8x8MatrixScrollUp(1,n, 50); //speed = 50ms
    //HT.sendLed();
    delay(1000);
    }

  delay(5000);

  Serial.println(F("Function 8x8 matrix test scroll down"));
  for (int n=8; n>=0; n--) {
    Serial.println(n);
    //HT.set8x8Matrix(0,n);
    HT.set8x8MatrixScrollDown(0,n, 50); //speed = 50ms
    HT.set8x8MatrixScrollDown(1,n, 50); //speed = 50ms
    //HT.sendLed();
    delay(1000);
    }

} // loop  
    
