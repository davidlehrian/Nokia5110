/*
* Nokia5110.cpp
*
* Created: 2/16/2015 09:27:05 PM
* Author: Lehrian
* Most of this code was shamelessly lifted from the Garage Lab 
* http://thegaragelab.com/nokia-5110-lcd-displays-on-the-attiny/ code written by ShaneG.
* I made a few modifications to use Arduino core routines instead of the core routines
* from Garage Lab.  This code has been tested with the ATtiny85 and a Nokia 5110 screen.  
*/
/*--------------------------------------------------------------------------*
* Nokia LCD Interface
*---------------------------------------------------------------------------*
* 26-Apr-2014 ShaneG
*
* Simple routines for controlling a Nokia LCD.
*--------------------------------------------------------------------------*/


#include "Arduino.h"
#include "Nokia5110.h"

void lcdWrite(byte cd, byte data);

const uint8_t SMALL_FONT[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, // 20
	0x00, 0x00, 0x5f, 0x00, 0x00, // 21 !
	0x00, 0x07, 0x00, 0x07, 0x00, // 22 "
	0x14, 0x7f, 0x14, 0x7f, 0x14, // 23 #
	0x24, 0x2a, 0x7f, 0x2a, 0x12, // 24 $
	0x23, 0x13, 0x08, 0x64, 0x62, // 25 %
	0x36, 0x49, 0x55, 0x22, 0x50, // 26 &
	0x00, 0x05, 0x03, 0x00, 0x00, // 27 '
	0x00, 0x1c, 0x22, 0x41, 0x00, // 28 (
	0x00, 0x41, 0x22, 0x1c, 0x00, // 29 )
	0x14, 0x08, 0x3e, 0x08, 0x14, // 2a *
	0x08, 0x08, 0x3e, 0x08, 0x08, // 2b +
	0x00, 0x50, 0x30, 0x00, 0x00, // 2c ,
	0x08, 0x08, 0x08, 0x08, 0x08, // 2d -
	0x00, 0x60, 0x60, 0x00, 0x00, // 2e .
	0x20, 0x10, 0x08, 0x04, 0x02, // 2f /
	0x3e, 0x51, 0x49, 0x45, 0x3e, // 30 0
	0x00, 0x42, 0x7f, 0x40, 0x00, // 31 1
	0x42, 0x61, 0x51, 0x49, 0x46, // 32 2
	0x21, 0x41, 0x45, 0x4b, 0x31, // 33 3
	0x18, 0x14, 0x12, 0x7f, 0x10, // 34 4
	0x27, 0x45, 0x45, 0x45, 0x39, // 35 5
	0x3c, 0x4a, 0x49, 0x49, 0x30, // 36 6
	0x01, 0x71, 0x09, 0x05, 0x03, // 37 7
	0x36, 0x49, 0x49, 0x49, 0x36, // 38 8
	0x06, 0x49, 0x49, 0x29, 0x1e, // 39 9
	0x00, 0x36, 0x36, 0x00, 0x00, // 3a :
	0x00, 0x56, 0x36, 0x00, 0x00, // 3b ;
	0x08, 0x14, 0x22, 0x41, 0x00, // 3c <
	0x14, 0x14, 0x14, 0x14, 0x14, // 3d =
	0x00, 0x41, 0x22, 0x14, 0x08, // 3e >
	0x02, 0x01, 0x51, 0x09, 0x06, // 3f ?
	0x32, 0x49, 0x79, 0x41, 0x3e, // 40 @
	0x7e, 0x11, 0x11, 0x11, 0x7e, // 41 A
	0x7f, 0x49, 0x49, 0x49, 0x36, // 42 B
	0x3e, 0x41, 0x41, 0x41, 0x22, // 43 C
	0x7f, 0x41, 0x41, 0x22, 0x1c, // 44 D
	0x7f, 0x49, 0x49, 0x49, 0x41, // 45 E
	0x7f, 0x09, 0x09, 0x09, 0x01, // 46 F
	0x3e, 0x41, 0x49, 0x49, 0x7a, // 47 G
	0x7f, 0x08, 0x08, 0x08, 0x7f, // 48 H
	0x00, 0x41, 0x7f, 0x41, 0x00, // 49 I
	0x20, 0x40, 0x41, 0x3f, 0x01, // 4a J
	0x7f, 0x08, 0x14, 0x22, 0x41, // 4b K
	0x7f, 0x40, 0x40, 0x40, 0x40, // 4c L
	0x7f, 0x02, 0x0c, 0x02, 0x7f, // 4d M
	0x7f, 0x04, 0x08, 0x10, 0x7f, // 4e N
	0x3e, 0x41, 0x41, 0x41, 0x3e, // 4f O
	0x7f, 0x09, 0x09, 0x09, 0x06, // 50 P
	0x3e, 0x41, 0x51, 0x21, 0x5e, // 51 Q
	0x7f, 0x09, 0x19, 0x29, 0x46, // 52 R
	0x46, 0x49, 0x49, 0x49, 0x31, // 53 S
	0x01, 0x01, 0x7f, 0x01, 0x01, // 54 T
	0x3f, 0x40, 0x40, 0x40, 0x3f, // 55 U
	0x1f, 0x20, 0x40, 0x20, 0x1f, // 56 V
	0x3f, 0x40, 0x38, 0x40, 0x3f, // 57 W
	0x63, 0x14, 0x08, 0x14, 0x63, // 58 X
	0x07, 0x08, 0x70, 0x08, 0x07, // 59 Y
	0x61, 0x51, 0x49, 0x45, 0x43, // 5a Z
	0x00, 0x7f, 0x41, 0x41, 0x00, // 5b [
	0x02, 0x04, 0x08, 0x10, 0x20, // 5c �
	0x00, 0x41, 0x41, 0x7f, 0x00, // 5d ]
	0x04, 0x02, 0x01, 0x02, 0x04, // 5e ^
	0x40, 0x40, 0x40, 0x40, 0x40, // 5f _
	0x00, 0x01, 0x02, 0x04, 0x00, // 60 `
	0x20, 0x54, 0x54, 0x54, 0x78, // 61 a
	0x7f, 0x48, 0x44, 0x44, 0x38, // 62 b
	0x38, 0x44, 0x44, 0x44, 0x20, // 63 c
	0x38, 0x44, 0x44, 0x48, 0x7f, // 64 d
	0x38, 0x54, 0x54, 0x54, 0x18, // 65 e
	0x08, 0x7e, 0x09, 0x01, 0x02, // 66 f
	0x0c, 0x52, 0x52, 0x52, 0x3e, // 67 g
	0x7f, 0x08, 0x04, 0x04, 0x78, // 68 h
	0x00, 0x44, 0x7d, 0x40, 0x00, // 69 i
	0x20, 0x40, 0x44, 0x3d, 0x00, // 6a j
	0x7f, 0x10, 0x28, 0x44, 0x00, // 6b k
	0x00, 0x41, 0x7f, 0x40, 0x00, // 6c l
	0x7c, 0x04, 0x18, 0x04, 0x78, // 6d m
	0x7c, 0x08, 0x04, 0x04, 0x78, // 6e n
	0x38, 0x44, 0x44, 0x44, 0x38, // 6f o
	0x7c, 0x14, 0x14, 0x14, 0x08, // 70 p
	0x08, 0x14, 0x14, 0x18, 0x7c, // 71 q
	0x7c, 0x08, 0x04, 0x04, 0x08, // 72 r
	0x48, 0x54, 0x54, 0x54, 0x20, // 73 s
	0x04, 0x3f, 0x44, 0x40, 0x20, // 74 t
	0x3c, 0x40, 0x40, 0x20, 0x7c, // 75 u
	0x1c, 0x20, 0x40, 0x20, 0x1c, // 76 v
	0x3c, 0x40, 0x30, 0x40, 0x3c, // 77 w
	0x44, 0x28, 0x10, 0x28, 0x44, // 78 x
	0x0c, 0x50, 0x50, 0x50, 0x3c, // 79 y
	0x44, 0x64, 0x54, 0x4c, 0x44, // 7a z
	0x00, 0x08, 0x36, 0x41, 0x00, // 7b {
	0x00, 0x00, 0x7f, 0x00, 0x00, // 7c |
	0x00, 0x41, 0x36, 0x08, 0x00, // 7d ,
	0x10, 0x08, 0x08, 0x10, 0x08, // 7e left arrow
	0x78, 0x46, 0x41, 0x46, 0x78, // 7f right arrow
	};

	/** Send a data byte to the LCD
	*
	* @param data the data byte to send.
	*/
	void lcdData(uint8_t data) {
		// Bring CD high for sending data
		lcdWrite(HIGH, data);
	}

	/** Send a command byte to the LCD
	*
	* @param cmd the command byte to send.
	*/
	void lcdCommand(uint8_t cmd) {
		// Bring CD low for sending a command
		lcdWrite(LOW, cmd);
	}

	/** Write a byte to the LCD
	* @param cd high for data, low for command
	* @param data the data or command byte to send.
	*/
	void lcdWrite(byte cd, byte data)
	{
		// Change to use Arduino core routine  DML 2/16/2015
		digitalWrite(PIN_DC, cd);
		// Change to use Arduino core routine  DML 2/16/2015
		// Send the data
		shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
	}

	/** Write a single character
	*
	* Display a single ASCII character at the position described by the row and
	* column parameters. Note that the row indicates an 8 pixel high character
	* row while the column represents individual pixels. This code uses a built
	* in character set where each character is 5 pixels wide and adds a single
	* column of pixels as spacing giving a total width of 6 pixels.
	*
	* @param row the row number (0 to 5) to display the character.
	* @param col the column position (0 to 83) for the start of the left side of
	*            the character.
	* @param ch  the character to display. If the character is out of range it
	*            will be replaced with the '?' character.
	* @param invert if true the colors are inverted and the character will be
	*               displayed as white on black.
	*/
	void lcdPrintChar(uint8_t row, uint8_t col, char ch, bool invert) {
		// Make sure it is on the screen
		if ((row >= LCD_ROW) || (col >= LCD_COL))
		return;
		// If the character is invalid replace it with the '?'
		if ((ch < 0x20) || (ch > 0x7f))
		ch = '?';
		// Set the starting address
		lcdCommand(0x80 | col);
		lcdCommand(0x40 | (row % LCD_ROW));
		// And send the column data
		const uint8_t *chdata = SMALL_FONT + ((ch - 0x20) * 5);
		for (uint8_t pixels = 0; (pixels < DATA_WIDTH) && (col < LCD_COL); pixels++, col++, chdata++) {
			uint8_t data = pgm_read_byte_near(chdata);
			lcdData(invert ? ~data : data);
		}
		// Add the padding byte
		if (col < LCD_COL)
		lcdData(invert ? 0xFF : 0x00);
	}

	/** Write a nul terminated string
	*
	* Display a string of ASCII characters at the position described by the row
	* and column parameters. Note that the row indicates an 8 pixel high character
	* row while the column represents individual pixels. This code uses a built
	* in character set where each character is 6 pixels wide.
	*
	* This function does not perform any word wrapping or other text layout
	* functions. If the string exceeds the size of the display it will simply
	* be clipped.
	*
	* @param row the row number (0 to 5) to display the character.
	* @param col the column position (0 to 83) for the start of the left side of
	*            the character.
	* @param str the string to display. If a character in the string is out of
	*            range it will be replaced with the '?' character.
	* @param invert if true the colors are inverted and the character will be
	*               displayed as white on black.
	*/
	void lcdPrint(uint8_t row, uint8_t col, const char *str, bool invert) {
		for (; (*str != '\0') && (col < LCD_COL); col += CHAR_WIDTH, str++)
		lcdPrintChar(row, col, *str, invert);
	}

	/** Clear the screen
	*
	* Clear the entire display.
	*
	* @param invert if true the colors are inverted and the screen will be filled
	*               with black.
	*/
	void lcdClear(bool invert) {
		uint8_t fill = invert ? 0xFF : 0x00;
		// Set the position
		lcdCommand(0x80);
		lcdCommand(0x40);
		// Fill in the whole display
		for (uint16_t index = 0; index < (LCD_COL * LCD_ROW); index++)
		lcdData(fill);
	}
	
	/** Clear a single row
	*
	* Clears a single character row from the left edge of the screen to the right.
	*
	* @param row the row number (0 to 5) to clear.
	* @param invert if true the colors are inverted and the screen will be filled
	*               with black.
	*/
	void lcdClearRow(uint8_t row, bool invert) {
		uint8_t fill = invert?0xFF:0x00;
		// Set the position
		lcdCommand(0x80);
		lcdCommand(0x40 | (row % LCD_ROW));
		// Fill in the row
		for(uint8_t index = 0; index < LCD_COL; index++)
		lcdData(fill);
	}
	
	/** Write a nul terminated string from PROGMEM
	*
	* Display a string of ASCII characters at the position described by the row
	* and column parameters. Note that the row indicates an 8 pixel high character
	* row while the column represents individual pixels. This code uses a built
	* in character set where each character is 6 pixels wide.
	*
	* This function does not perform any word wrapping or other text layout
	* functions. If the string exceeds the size of the display it will simply
	* be clipped.
	*
	* @param row the row number (0 to 5) to display the character.
	* @param col the column position (0 to 83) for the start of the left side of
	*            the character.
	* @param str the string to display. If a character in the string is out of
	*            range it will be replaced with the '?' character.
	* @param invert if true the colors are inverted and the character will be
	*               displayed as white on black.
	*/
	void lcdPrintP(uint8_t row, uint8_t col, const char *str, bool invert) {
		while(col<LCD_COL) {
			char ch = pgm_read_byte_near(str);
			if(ch=='\0')
			return;
			lcdPrintChar(row, col, ch, invert);
			col += CHAR_WIDTH;
			str++;
		}
	}

	/** Display an arbitrary graphic on the display
	*
	* This function is used to display user defined graphics held in PROGMEM to
	* the display. The first byte of the graphic indicates the height (in 8 pixel
	* rows) and the width (in pixel columns) packed as HHWWWWWW giving a maximum
	* size of 4 rows (32 pixels) by 64 pixels for a single image. Images that
	* will display off the edge of the screen are clipped. The packed version of
	* the width and height are 1 less than the actual width and height.
	*
	* The image is packed as a sequence of 8 pixel vertical strips.
	*
	* @param row the row number (0 to 5) to start the top left of the image.
	* @param col the column number (0 to 83) to start the top left of the image.
	* @param img pointer to the image in PROGMEM.
	* @param invert if true the pixel colors will be inverted.
	*/
	void lcdImageP(uint8_t row, uint8_t col, const uint8_t *img, bool invert) {
		// Break out the width and height
		uint8_t data = pgm_read_byte_near(img++);
		uint8_t height = (data >> 6) + 1;
		uint8_t width = (data & 0x03F) + 1;
		while((height>0)&&(row<LCD_ROW)) {
			// Set the starting address
			lcdCommand(0x80 | col);
			lcdCommand(0x40 | row);
			// Send the data (up to the end of the screen)
			for(uint8_t offset=0; offset<width; offset++, img++) {
				if((col+offset)<LCD_COL) {
					if(invert)
					lcdData(~pgm_read_byte_near(img));
					else
					lcdData(pgm_read_byte_near(img));
				}
			}
			height--;
			row++;
		}
	}

	/** Initialize the LCD
	*
	* Sets up the pins required to communicate with the LCD screen and then does
	* the actual chipset initialization. The pin numbers to use are defined in
	* @ref Nokia5110.h.
	*/
	void lcdInitialize(void)
	{
		// Set up the output pins,
		pinMode(PIN_RESET, OUTPUT);
		pinMode(PIN_DC, OUTPUT);
		pinMode(PIN_SDIN, OUTPUT);
		pinMode(PIN_SCLK, OUTPUT);
		// Ensure all pins are 'low' to start
		digitalWrite(PIN_DC, LOW);
		digitalWrite(PIN_SDIN, LOW);
		digitalWrite(PIN_SCLK, LOW);
		digitalWrite(PIN_RESET, LOW);
		digitalWrite(PIN_RESET, HIGH);
		lcdCommand(0x21 );  // LCD Extended Commands.
		lcdCommand(0xA1 );  // Set LCD Vop (Contrast).
		lcdCommand(0x04 );  // Set Temp coefficent. //0x04
		lcdCommand(0x14 );  // LCD bias mode 1:48. //0x13
		lcdCommand(0x20 );  // LCD Basic Commands
		lcdCommand(0x0C );  // LCD in normal mode.
	}
