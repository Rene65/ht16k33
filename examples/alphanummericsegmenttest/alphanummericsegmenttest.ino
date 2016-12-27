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

  HT.clearAll();
  Serial.println(F("Turn on all LEDs"));
  // first light up all LEDs
  for (led=0; led<16; led++) {
    HT.setLedNow(led);
    delay(1000);
  } // for led



  Serial.println(F("Function alphanummeric segment  and write direct to display without sendled() test"));
  HT.clearAll();
  boolean decimalpoint = true;
  for (int n=32; n<128; n++) {
    Serial.println(n);
    HT.set14SegNow(0,n);
    delay(1000);
    }
  delay(5000);


} // loop  
