 /* Author: Norlinux
 *http://maquina.96.lt
 *http://www.microelectronic.pt
 *https://www.facebook.com/MundoDosMicrocontroladores/
 *Released under GPLv3.
 *Please refer to LICENSE file for licensing information.
 *which can be found at http://www.gnu.org/licenses/gpl.txt
 */
#ifndef LCD_LIB
#define LCD_LIB

#include <inttypes.h>

//Uncomment this if LCD 4 bit interface is used
//******************************************
#define LCD_4bit
//***********************************************
#define LCD_RS	0 	//define MCU pin connected to LCD RS
#define LCD_RW	1 	//define MCU pin connected to LCD R/W
#define LCD_E	2	//define MCU pin connected to LCD E
#define LCD_D0	0	//define MCU pin connected to LCD D0
#define LCD_D1	1	//define MCU pin connected to LCD D1
#define LCD_D2	2	//define MCU pin connected to LCD D1
#define LCD_D3	3	//define MCU pin connected to LCD D2
#define LCD_D4	4	//define MCU pin connected to LCD D3
#define LCD_D5	5	//define MCU pin connected to LCD D4
#define LCD_D6	6	//define MCU pin connected to LCD D5
#define LCD_D7	7	//define MCU pin connected to LCD D6
#define LCD_DATA_PORT PORTC	//define MCU port connected to LCD data pins
#define LCD_CONTROL_PORT PORTC	//define MCU port connected to LCD control pins
#define LCD_DATA_DDR DDRC	//define MCU direction register for port connected to LCD data pins
#define LCD_CONTROL_DDR DDRC	//define MCU direction register for port connected to LCD control pins

#define SET_E		LCD_CONTROL_PORT|=1<<LCD_E
#define SET_RS		LCD_CONTROL_PORT|=1<<LCD_RS
#define CLEAR_E		LCD_CONTROL_PORT&=~(1<<LCD_E)
#define CLEAR_RS	LCD_CONTROL_PORT&=~(1<<LCD_RS)
#define delay_ms(ms) _delay_ms(ms)

/* instruction register bit positions, see HD44780U data sheet */
#define LCD_CLR               0      /* DB0: clear display                  */
#define LCD_HOME              1      /* DB1: return to home position        */
#define LCD_ENTRY_MODE        2      /* DB2: set entry mode                 */
#define LCD_ENTRY_INC         1      /*   DB1: 1=increment, 0=decrement     */
#define LCD_ENTRY_SHIFT       0      /*   DB2: 1=display shift on           */
#define LCD_ON                3      /* DB3: turn lcd/cursor on             */
#define LCD_ON_DISPLAY        2      /*   DB2: turn display on              */
#define LCD_ON_CURSOR         1      /*   DB1: turn cursor on               */
#define LCD_ON_BLINK          0      /*     DB0: blinking cursor ?          */
#define LCD_MOVE              4      /* DB4: move cursor/display            */
#define LCD_MOVE_DISP         3      /*   DB3: move display (0-> cursor) ?  */
#define LCD_MOVE_RIGHT        2      /*   DB2: move right (0-> left) ?      */
#define LCD_FUNCTION          5      /* DB5: function set                   */
#define LCD_FUNCTION_8BIT     4      /*   DB4: set 8BIT mode (0->4BIT mode) */
#define LCD_FUNCTION_2LINES   3      /*   DB3: two lines (0->one line)      */
#define LCD_FUNCTION_10DOTS   2      /*   DB2: 5x10 font (0->5x7 font)      */
#define LCD_CGRAM             6      /* DB6: set CG RAM address             */
#define LCD_DDRAM             7      /* DB7: set DD RAM address             */
#define LCD_BUSY              7      /* DB7: LCD is busy                    */
#define LCD_LINES             2      /*  visible lines                      */
#define LCD_LINE_LENGTH       16     /*  line length (in characters)        */
/* display on/off, cursor on/off, blinking char at cursor position */
#define LCD_DISP_OFF             0x08   /* display off                            */
#define LCD_DISP_ON              0x0C   /* display on, cursor off                 */
#define LCD_DISP_ON_BLINK        0x0D   /* display on, cursor off, blink char     */
#define LCD_DISP_ON_CURSOR       0x0E   /* display on, cursor on                  */
#define LCD_DISP_ON_CURSOR_BLINK 0x0F   /* display on, cursor on, blink char      */
/* move cursor/shift display */
#define LCD_MOVE_CURSOR_LEFT     0x10   /* move cursor left  (decrement)          */
#define LCD_MOVE_CURSOR_RIGHT    0x14   /* move cursor right (increment)          */
#define LCD_MOVE_DISP_LEFT       0x18   /* shift display left                     */
#define LCD_MOVE_DISP_RIGHT      0x1C   /* shift display right                    */
// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAM_ADDRESS		0x00
#define LCD_LINE1_DDRAM_ADDRESS		0x40
#define LCD_LINE2_DDRAM_ADDRESS		0x14
#define LCD_LINE3_DDRAM_ADDRESS		0x54
// progress bar defines
#define PROGRESSPIXELS_PER_CHAR	6


void LCDsendChar(uint8_t);		//forms data ready to send to 74HC164
void LCDcommand(uint8_t);	//forms data ready to send to 74HC164
void LCDinit(void);			//Initializes LCD
void LCDclr(void);				//Clears LCD
void LCDhome(void);			//LCD cursor home
void LCDstring(uint8_t*, uint8_t);	//Outputs string to LCD
void LCDGotoXY(uint8_t, uint8_t);	//Cursor to X Y position
void LCDStringtoLCD(const uint8_t*, uint8_t, uint8_t);//copies flash string to LCD at x,y
void LCDprintXY(const char*,uint8_t, uint8_t);	// print string on lcd (no auto linefeed), in X,Y Position
void LCDdefinechar(const uint8_t *,uint8_t);//write char to LCD CGRAM 
void LCDshiftRight(uint8_t);	//shift by n characters Right
void LCDshiftLeft(uint8_t);	//shift by n characters Left
void LCDcursorOn(void);		//Underline cursor ON
void LCDcursorOnBlink(void);	//Underline blinking cursor ON
void LCDcursorOFF(void);		//Cursor OFF
void LCDblank(void);			//LCD blank but not cleared
void LCDvisible(void);			//LCD visible
void LCDcursorLeft(uint8_t);	//Shift cursor left by n
void LCDcursorRight(uint8_t);	//shif cursor right by n
// displays a horizontal progress bar at the current cursor location
// <progress> is the value the bargraph should indicate
// <maxprogress> is the value at the end of the bargraph
// <length> is the number of LCD characters that the bargraph should cover
//adapted from AVRLIB - displays progress only for 8 bit variables
void LCDprogressBar(uint8_t progress, uint8_t maxprogress, uint8_t length);


#endif

