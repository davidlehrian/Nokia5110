
#define PIN_RESET 0
#define PIN_DC    1
#define PIN_SDIN  2
#define PIN_SCLK  4

#define LCD_C     LOW
#define LCD_D     HIGH

#define LCD_X     84
#define LCD_Y     48

/** Number of columns */
#define LCD_COL 84

/** Number of text rows */
#define LCD_ROW 6
#define DATA_WIDTH 5
#define CHAR_WIDTH (DATA_WIDTH + 1)

/** Send a command byte to the LCD
*
* @param cmd the command byte to send.
*/
void lcdCommand(uint8_t cmd);

/** Send a data byte to the LCD
*
* @param data the data byte to send.
*/
void lcdData(uint8_t data);

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
void lcdPrintChar(uint8_t row, uint8_t col, char ch, bool invert);
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
void lcdPrint(uint8_t row, uint8_t col, const char *str, bool invert);
/** Clear the screen
*
* Clear the entire display.
*
* @param invert if true the colors are inverted and the screen will be filled
*               with black.
*/
void lcdClear(bool invert);
/** Initialize the LCD
*
* Sets up the pins required to communicate with the LCD screen and then does
* the actual chipset initialization. The pin numbers to use are defined in
* @ref hardware.h.
*/
void lcdInitialize(void);
/** Clear a single row
*
* Clears a single character row from the left edge of the screen to the right.
*
* @param row the row number (0 to 5) to clear.
* @param invert if true the colors are inverted and the screen will be filled
*               with black.
*/
void lcdClearRow(uint8_t row, bool invert);
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
void lcdPrintP(uint8_t row, uint8_t col, const char *str, bool invert);
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
void lcdImageP(uint8_t row, uint8_t col, const uint8_t *img, bool invert);