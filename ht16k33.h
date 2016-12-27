/*
  ht16k33.h - used to talk to the htk1633 chip to do things like turn on LEDs or scan keys
 * Copyright:  Peter Sjoberg <peters-alib AT techwiz.ca>
 * License: GPLv3
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3 as 
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 *
 *
 * History:
 * 2015-10-04  Peter Sjoberg <peters-alib AT techwiz.ca>
 *             Created using https://www.arduino.cc/en/Hacking/LibraryTutorial and ht16k33 datasheet
 * 2015-11-25  Peter Sjoberg <peters-alib AT techwiz DOT ca>
 *	       first check in to github
 * 2015-12-05  Peter Sjoberg <peters-alib AT techwiz.ca>
 *	       moved displayram to public section
 * 2016-8-9    René Wennekes <rene.wennekes AT gmail.com>
 *             Contribution of 7-segment, 14-segment & matrix display support
 *             Added clearAll() function
 */



#ifndef ht16k33_h
#define ht16k33_h

#include "Arduino.h"

//  --- DP - G - F -E - D - C - B -A
const static uint8_t seg7Chartable[] = {
  0b00111111,  // 0
  0b00000110,  // 1
  0b01011011,  // 2
  0b01001111,  // 3
  0b01100110,  // 4
  0b01101101,  // 5
  0b01111101,  // 6
  0b00000111,  // 7
  0b01111111,  // 8
  0b01101111,  // 9
  0b01110111,  // A
  0b01111100,  // B
  0b01011000,  // C
  0b01011110,  // D
  0b01111001,  // E
  0b01110001,  // F
};     


//14-segment
/*
 *     a
 * f h j k b
 *   g1 g2
 * e l m n c
 *     d 
 *        dp
*/
//0 DP N M L K J H G2 G1 F E D C B A
const uint16_t seg14Chartable[]={
  0b0000000000000001,
  0b0000000000000010,
  0b0000000000000100,
  0b0000000000001000,
  0b0000000000010000,
  0b0000000000100000,
  0b0000000001000000,
  0b0000000010000000,
  0b0000000100000000,
  0b0000001000000000,
  0b0000010000000000,
  0b0000100000000000,
  0b0001000000000000,
  0b0010000000000000,
  0b0100000000000000,
  0b1000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0001001011001001,
  0b0001010111000000,
  0b0001001011111001,
  0b0000000011100011,
  0b0000010100110000,
  0b0001001011001000,
  0b0011101000000000,
  0b0001011100000000,
  0b0000000000000000, //  
  0b0000000000000110, // !
  0b0000001000100000, // "
  0b0001001011001110, // #
  0b0001001011101101, // $
  0b0000110000100100, // %
  0b0010001101011101, // &
  0b0000010000000000, // '
  0b0010010000000000, // (
  0b0000100100000000, // )
  0b0011111111000000, // *
  0b0001001011000000, // +
  0b0000100000000000, // ,
  0b0000000011000000, // -
  0b0000000000000000, // .
  0b0000110000000000, // /
  0b0000110000111111, // 0
  0b0000000000000110, // 1
  0b0000000011011011, // 2
  0b0000000010001111, // 3
  0b0000000011100110, // 4
  0b0010000001101001, // 5
  0b0000000011111101, // 6
  0b0000000000000111, // 7
  0b0000000011111111, // 8
  0b0000000011101111, // 9
  0b0001001000000000, // :
  0b0000101000000000, // ;
  0b0010010000000000, // <
  0b0000000011001000, // =
  0b0000100100000000, // >
  0b0001000010000011, // ?
  0b0000001010111011, // @
  0b0000000011110111, // A
  0b0001001010001111, // B
  0b0000000000111001, // C
  0b0001001000001111, // D
  0b0000000011111001, // E
  0b0000000001110001, // F
  0b0000000010111101, // G
  0b0000000011110110, // H
  0b0001001000000000, // I
  0b0000000000011110, // J
  0b0010010001110000, // K
  0b0000000000111000, // L
  0b0000010100110110, // M
  0b0010000100110110, // N
  0b0000000000111111, // O
  0b0000000011110011, // P
  0b0010000000111111, // Q
  0b0010000011110011, // R
  0b0000000011101101, // S
  0b0001001000000001, // T
  0b0000000000111110, // U
  0b0000110000110000, // V
  0b0010100000110110, // W
  0b0010110100000000, // X
  0b0001010100000000, // Y
  0b0000110000001001, // Z
  0b0000000000111001, // [
  0b0010000100000000, // 
  0b0000000000001111, // ]
  0b0000110000000011, // ^
  0b0000000000001000, // _
  0b0000000100000000, // `
  0b0001000001011000, // a
  0b0010000001111000, // b
  0b0000000011011000, // c
  0b0000100010001110, // d
  0b0000100001011000, // e
  0b0000000001110001, // f
  0b0000010010001110, // g
  0b0001000001110000, // h
  0b0001000000000000, // i
  0b0000000000001110, // j
  0b0011011000000000, // k
  0b0000000000110000, // l
  0b0001000011010100, // m
  0b0001000001010000, // n
  0b0000000011011100, // o
  0b0000000101110000, // p
  0b0000010010000110, // q
  0b0000000001010000, // r
  0b0010000010001000, // s
  0b0000000001111000, // t
  0b0000000000011100, // u
  0b0010000000000100, // v
  0b0010100000010100, // w
  0b0010100011000000, // x
  0b0010000000001100, // y
  0b0000100001001000, // z
  0b0000100101001001, // {
  0b0001001000000000, // |
  0b0010010010001001, // }
  0b0000010100100000, // ~
  0b0011111111111111,
};


const static byte matrix8x8Chartable[41][8]={
	{0b00111100,
	 0b01100110,
	 0b01000110,
	 0b01001010,
	 0b01010010,
	 0b01100010,
	 0b01100110,
	 0b00111100}, //0
	
	{0b00011000,
	 0b00111000,
	 0b01111000,
	 0b00011000,
	 0b00011000,
	 0b00011000,
	 0b00011000,
	 0b01111110},  //1
	 
	{0b00111100,
	 0b01100110,
	 0b01000010,
	 0b00000110,
	 0b00011100,
	 0b00110000,
	 0b01100010,
	 0b01111110},//2
	 
	{0b00111100,
	 0b01100110,
	 0b01000010,
	 0b00001100,
	 0b00001100,
	 0b01000010,
	 0b01100110,
	 0b00111100},//3
	
	{0b00001100,
	 0b00011100,
	 0b00110100,
	 0b01100100,
	 0b01111110,
	 0b00000100,
	 0b00000100,
	 0b00000100},//4
	
	{0b01111110,
	 0b01100010,
	 0b01100000,
	 0b00111100,
	 0b00000110,
	 0b01000010,
	 0b01100110,
	 0b00111100},//5
	
	{0b00111100,
	 0b01100110,
	 0b01100000,
	 0b01111100,
	 0b01100110,
	 0b01000010,
	 0b01100110,
	 0b00111100},//6
	
	{0b01111110,
	 0b00000110,
	 0b00000110,
	 0b00001100,
	 0b00011000,
	 0b00011000,
	 0b00011000,
	 0b00011000},//7
	
	{0b00111100,
	 0b01100110,
	 0b01000010,
	 0b00111100,
	 0b00111100,
	 0b01000010,
	 0b01100110,
	 0b00111100},//8
	
	{0b00111100,
	 0b01100110,
	 0b01000010,
	 0b01100110,
	 0b00111110,
	 0b00000110,
	 0b01100110,
	 0b00111100},//9
	
	{0b00111100,
	 0b01100110,
	 0b01000010,
	 0b01111110,
	 0b01111110,
	 0b01000010,
	 0b01000010,
	 0b01000010},//A
	
	{0b01111100,
	 0b01000110,
	 0b01000010,
	 0b01111100,
	 0b01111100,
	 0b01000010,
	 0b01000110,
	 0b01111100,},//B
	
	{0b00111100,
	 0b01100110,
	 0b01000010,
	 0b01000000,
	 0b01000000,
	 0b01000010,
	 0b01100110,
	 0b00111100,},//C
	
	{0b01111100,
	 0b01000110,
	 0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01000110,
	 0b01111100,},//D
	
	{0b01111110,
	 0b01000000,
	 0b01000000,
	 0b01111000,
	 0b01111000,
	 0b01000000,
	 0b01000000,
	 0b01111110,},//E
	
	{0b01111110,
	 0b01000000,
	 0b01000000,
	 0b01111000,
	 0b01111000,
	 0b01000000,
	 0b01000000,
	 0b01000000,},//F
	
	{0b00111100,
	 0b01100110,
	 0b01000010,
	 0b01000000,
	 0b01001110,
	 0b01000010,
	 0b01100110,
	 0b00111100,},//G
	
	{0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01111110,
	 0b01111110,
	 0b01000010,
	 0b01000010,
	 0b01000010,},//H
	
	{0b00011000,
	 0b00011000,
	 0b00011000,
	 0b00011000,
	 0b00011000,
	 0b00011000,
	 0b00011000,
	 0b00011000,},//I
	
	{0b00000110,
	 0b00000110,
	 0b00000110,
	 0b00000110,
	 0b00000110,
	 0b01000110,
	 0b01101100,
	 0b00111100,},//J
	
	{0b01000110,
	 0b01001100,
	 0b01011000,
	 0b01110000,
	 0b01110000,
	 0b01011000,
	 0b01001100,
	 0b01000110,},//K
	
	{0b01000000,
	 0b01000000,
	 0b01000000,
	 0b01000000,
	 0b01000000,
	 0b01000000,
	 0b01000000,
	 0b01111110,},//L
	
	{0b01000010,
	 0b01100110,
	 0b01011010,
	 0b01011010,
	 0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01000010,},//M
	
	{0b01000010,
	 0b01100010,
	 0b01010010,
	 0b01010010,
	 0b01001010,
	 0b01001010,
	 0b01000110,
	 0b01000010,},//N
	
	{0b00111100,
	 0b01100110,
	 0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01100110,
	 0b00111100,},//O
	
	{0b00111100,
	 0b01100110,
	 0b01000010,
	 0b01100110,
	 0b01111100,
	 0b01000000,
	 0b01000000,
	 0b01000000,},//P
	
	{0b00111100,
	 0b01100110,
	 0b01000010,
	 0b01000010,
	 0b01011010,
	 0b01001110,
	 0b01100110,
	 0b00111100,},//Q
	
	{0b00111100,
	 0b01100110,
	 0b01000010,
	 0b01100110,
	 0b01111100,
	 0b01011000,
	 0b01001100,
	 0b01000110,},//R
	
	{0b00111100,
	 0b01100110,
	 0b01000000,
	 0b00111000,
	 0b00011100,
	 0b00000010,
	 0b01100110,
	 0b00111100,},//S
	
	{0b01111110,
	 0b00011000,
	 0b00011000,
	 0b00011000,
	 0b00011000,
	 0b00011000,
	 0b00011000,
	 0b00011000,},//T
	
	{0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01100110,
	 0b00111100,},//U
	
	{0b01000010,
	 0b01000010,
	 0b01000010,
	 0b00100100,
	 0b00100100,
	 0b00100100,
	 0b00011000,
	 0b00011000,},//V
	
	{0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01000010,
	 0b01011010,
	 0b01011010,
	 0b01011010,
	 0b00111100,},//W
	
	{0b01000010,
	 0b01000010,
	 0b00100100,
	 0b00011000,
	 0b0001000,
	 0b00100100,
	 0b01000010,
	 0b01000010,},//X
	
	{0b01000010,
	 0b01000010,
	 0b01000010,
	 0b00100110,
	 0b00011110,
	 0b00000010,
	 0b01000110,
	 0b00111100,},//Y
	
	{0b01111110,
	 0b00000010,
	 0b00000100,
	 0b00001000,
	 0b00010000,
	 0b00100000,
	 0b01000000,
	 0b01111110,},//Z
	
	{0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000},// blank space 36
	 
	{0b00000000,
	 0b00011000,
	 0b00011000,
	 0b00000000,
	 0b00000000,
	 0b00011000,
	 0b00011000,
	 0b00000000},// : 37
	 
	{0b00000000,
	 0b00000000,
	 0b00000000,
	 0b01111110,
	 0b01111110,
	 0b00000000,
	 0b00000000,
	 0b00000000},// - 38
	
	{0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00011000,
	 0b00011000},// . 39

	{0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00011000,
	 0b00011000,
	 0b00000000,
	 0b00000000,
	 0b00000000}//Dot middle 40
};

class HT16K33
{
 public:
  typedef uint16_t KEYDATA[3];
  typedef uint8_t  DisplayRam_t[16];

  DisplayRam_t displayRam;

  HT16K33(); // the class itself

  void    begin(uint8_t address);
  void    end();
  void    clearAll();
  uint8_t sleep();  // stop oscillator to put the chip to sleep
  uint8_t normal(); // wake up chip and start ocillator
  uint8_t clearLed(uint8_t ledno); // 16x8 = 128 LEDs to turn on, 0-127
  uint8_t setLed(uint8_t ledno); // 16x8 = 128 LEDs to turn on, 0-127
  uint8_t set7Seg(uint8_t dig, uint8_t cha, boolean dp); // position 0-15, 0-15 (0-F Hexadecimal), decimal point
  uint8_t set14Seg(uint8_t dig, uint8_t cha); // position 0-7, see asciifont.h
  uint8_t set8x8Matrix(uint8_t dig, uint8_t cha); //
  boolean getLed(uint8_t ledno,boolean Fresh=false); // check if a specific led is on(true) or off(false)
  uint8_t setDisplayRaw(uint8_t pos, uint8_t val); // load byte "pos" with value "val"
  uint8_t sendLed(); // send whatever led patter you set
  uint8_t setLedNow(uint8_t ledno); //Set a single led and send led in one function
  uint8_t set7SegNow(uint8_t dig, uint8_t cha, boolean dp); // position 0-15, 0-15 (0-F Hexadecimal), decimal point and send led in one function
  uint8_t set7SegRaw(uint8_t dig, uint8_t val); // load byte "pos" with value "val"
  uint8_t set14SegNow(uint8_t dig, uint8_t cha); // position 0-7, see asciifont.h and send led in one function
  uint8_t set8x8MatrixNow(uint8_t dig, uint8_t cha); //
  uint8_t set8x8MatrixScrollUp(uint8_t dig, uint8_t cha, uint8_t speed); //
  uint8_t set8x8MatrixScrollDown(uint8_t dig, uint8_t cha, uint8_t speed); //
  uint8_t set8x8MatrixChar(uint8_t dig, char value); //
  uint8_t clearLedNow(uint8_t ledno); //Clear a single led and send led in one function
  uint8_t setBrightness(uint8_t level); // level 0-16, 0 means display off
  uint8_t keyINTflag(); // INTerrupt flag value, set when a key is pressed
  uint8_t keysPressed(); // report how many keys that are pressed, clear means report as if new
  int8_t  readKey(boolean clear=false);  // read what key was pressed, Fresh=false to go from cache
  void    readKeyRaw(KEYDATA keydata,boolean Fresh=true); //read the raw key info, bitmapped info of all key(s) pressed
  uint8_t setBlinkRate(uint8_t rate); // HT16K33_DSP_{NOBLINK,BLINK2HZ,BLINK1HZ,BLINK05HZ}
  void    displayOn();
  void    displayOff();

 private:
  void _updateKeyram();
  uint8_t _i2c_write(uint8_t val);
  uint8_t _i2c_write(uint8_t cmd,uint8_t *data,uint8_t size,boolean LSB=false);
  uint8_t _i2c_read(uint8_t addr);
  uint8_t _i2c_read(uint8_t addr,uint8_t *data,uint8_t size);

  KEYDATA _keyram;
  uint8_t _address;
};


#endif
