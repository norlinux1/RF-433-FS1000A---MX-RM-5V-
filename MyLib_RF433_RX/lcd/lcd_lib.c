 /* Author: Norlinux
 *http://maquina.96.lt
 *http://www.microelectronic.pt
 `*https://www.facebook.com/MundoDosMicrocontroladores/
 *Released under GPLv3.
 *Please refer to LICENSE file for licensing information.
 *which can be found at http://www.gnu.org/licenses/gpl.txt
 */
#include "lcd_lib.h"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>


const uint8_t LcdCustomChar[] PROGMEM=//define 8 custom LCD chars
{
	0x00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0x00, 
	0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 
	0X18, 0X18, 0X18, 0X18, 0X18, 0X18, 0X18, 0X18, 
	0X1C, 0X1C, 0X1C, 0X1C, 0X1C, 0X1C, 0X1C, 0X1C, 
	0X1E, 0X1E, 0X1E, 0X1E, 0X1E, 0X1E, 0X1E, 0X1E,
	0X1F, 0X1F, 0X1F, 0X1F, 0X1F, 0X1F, 0X1F, 0X1F, 
	0x00, 0x0A, 0x04, 0x04, 0x11, 0x0E, 0x00, 0x00, //:-)
	0x00, 0x0E, 0x0A, 0x0E, 0x00, 0x00, 0x00, 0x00, //º
};

void LCDsendChar(uint8_t ch)		//Sends Char to LCD
{

#ifdef LCD_4bit
	//4 bit part
	LCD_DATA_PORT=(ch&0b11110000);
	SET_RS;
	SET_E;		
	delay_ms(1);
	CLEAR_E;	
	CLEAR_RS;
	delay_ms(1);
	LCD_DATA_PORT=((ch&0b00001111)<<4);
	SET_RS;
	SET_E;		
	delay_ms(1);
	CLEAR_E;	
	CLEAR_RS;
	delay_ms(1);
#else
	//8 bit part
	LCD_DATA_PORT=ch;
	SET_RS;
	SET_E;		
	delay_ms(1);
	CLEAR_E;	
	CLEAR_RS;
	delay_ms(1);
#endif
}
void LCDcommand(uint8_t cmd)	//Sends Command to LCD
{
#ifdef LCD_4bit	
	//4 bit part
	LCD_DATA_PORT=(cmd&0b11110000);
	SET_E;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
	LCD_DATA_PORT=((cmd&0b00001111)<<4);	
	SET_E;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
#else
	//8 bit part
	LCD_DATA_PORT=cmd;
	SET_E;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);	
#endif
}
void LCDinit(void)//Initializes LCD
{
#ifdef LCD_4bit	
	//4 bit part
	delay_ms(15);
	LCD_DATA_PORT=0x00;
	LCD_CONTROL_PORT=0x00;
	LCD_DATA_DDR|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCD_CONTROL_DDR|=1<<LCD_E|1<<LCD_RW|1<<LCD_RS;
   //---------one------
	LCD_DATA_PORT=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4; //4 bit mode
	SET_E|0<<LCD_RW|0<<LCD_RS;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
	//-----------two-----------
	LCD_DATA_PORT=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4; //4 bit mode
	SET_E|0<<LCD_RW|0<<LCD_RS;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
	//-------three-------------
	LCD_DATA_PORT=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|0<<LCD_D4; //4 bit mode
	SET_E|0<<LCD_RW|0<<LCD_RS;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
	//--------4 bit--dual line---------------
	LCDcommand(0b00101000);
   //-----increment address, invisible cursor shift------
	LCDcommand(0b00001100);
		//init 8 custom chars
	uint8_t ch=0, chn=0;
	while(ch<64)
	{
		LCDdefinechar((LcdCustomChar+ch),chn++);
		ch=ch+8;
	}


#else
	//8 bit part
	delay_ms(15);
	LCD_DATA_PORT=0x00;
	LCD_CONTROL_PORT=0x00;
	LCD_DATA_DDR|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4|1<<LCD_D3
			|1<<LCD_D2|1<<LCD_D1|1<<LCD_D0;
	LCD_CONTROL_DDR|=1<<LCD_E|1<<LCD_RW|1<<LCD_RS;
   //---------one------
	LCD_DATA_PORT=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4|0<<LCD_D3
			|0<<LCD_D2|0<<LCD_D1|0<<LCD_D0; //8 it mode
	SET_E|0<<LCD_RW|0<<LCD_RS;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
	//-----------two-----------
	LCD_DATA_PORT=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4|0<<LCD_D3
			|0<<LCD_D2|0<<LCD_D1|0<<LCD_D0; //8 it mode
	SET_E|0<<LCD_RW|0<<LCD_RS;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
	//-------three-------------
	LCD_DATA_PORT=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4|0<<LCD_D3
			|0<<LCD_D2|0<<LCD_D1|0<<LCD_D0; //8 it mode
	SET_E|0<<LCD_RW|0<<LCD_RS;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
	//--------8 bit dual line----------
	LCD_DATA_PORT=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4|1<<LCD_D3
			|0<<LCD_D2|0<<LCD_D1|0<<LCD_D0; //8 it mode
	SET_E|0<<LCD_RW|0<<LCD_RS;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(1);
   //-----increment address, invisible cursor shift------
	LCD_DATA_PORT=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4|1<<LCD_D3
			|1<<LCD_D2|0<<LCD_D1|0<<LCD_D0; //8 it mode
	SET_E|0<<LCD_RW|0<<LCD_RS;		
	delay_ms(1);
	CLEAR_E;
	delay_ms(5);
		//init custom chars
	uint8_t ch=0, chn=0;
	while(ch<64)
	{
		LCDdefinechar((LcdCustomChar+ch),chn++);
		ch=ch+8;
	}

#endif
}			
void LCDclr(void)				//Clears LCD
{
	LCDcommand(1<<LCD_CLR);
}
void LCDhome(void)			//LCD cursor home
{
	LCDcommand(1<<LCD_HOME);
}
void LCDstring(uint8_t* data, uint8_t nBytes)	//Outputs string to LCD
{
register uint8_t i;

	// check to make sure we have a good pointer
	if (!data) return;

	// print data
	for(i=0; i<nBytes; i++)
	{
		LCDsendChar(data[i]);
	}
}
void LCDGotoXY(uint8_t x, uint8_t y)	//Cursor to X Y position
{
	register uint8_t DDRAM_ADDRESS;
	// remap lines into proper order
	switch(y)
	{
	case 0: DDRAM_ADDRESS = LCD_LINE0_DDRAM_ADDRESS+x; break;
	case 1: DDRAM_ADDRESS = LCD_LINE1_DDRAM_ADDRESS+x; break;
	case 2: DDRAM_ADDRESS = LCD_LINE2_DDRAM_ADDRESS+x; break;
	case 3: DDRAM_ADDRESS = LCD_LINE3_DDRAM_ADDRESS+x; break;
	default: DDRAM_ADDRESS = LCD_LINE0_DDRAM_ADDRESS+x;
	}
	// set data address
	LCDcommand(1<<LCD_DDRAM | DDRAM_ADDRESS);
	
}
//Copies string from flash memory to LCD at x y position
//const uint8_t welcomeln1[] PROGMEM="AVR LCD DEMO\0";
//LCDStringtoLCD(welcomeln1, 3, 1);	
void LCDStringtoLCD(const uint8_t *FlashLoc, uint8_t x, uint8_t y)
{
	uint8_t i;
	LCDGotoXY(x,y);
	for(i=0;(uint8_t)pgm_read_byte(&FlashLoc[i]);i++)
	{
		LCDsendChar((uint8_t)pgm_read_byte(&FlashLoc[i]));
	}
}

void LCDdefinechar(const uint8_t *pc,uint8_t char_code){
	uint8_t a, pcc;
	uint16_t i;
	a=(char_code<<3)|0x40;
	for (i=0; i<8; i++){
		pcc=pgm_read_byte(&pc[i]);
		LCDcommand(a++);
		LCDsendChar(pcc);
		}
}

void LCDshiftLeft(uint8_t n)	//Scrol n of characters Right
{
	for (uint8_t i=0;i<n;i++)
	{
		//LCDcommand(0x1E);
		LCDcommand(LCD_MOVE_DISP_RIGHT);
	}
}
void LCDshiftRight(uint8_t n)	//Scrol n of characters Left
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(LCD_MOVE_DISP_LEFT);
	}
}
void LCDcursorOn(void) //displays LCD cursor
{
	LCDcommand(LCD_DISP_ON_CURSOR);
}
void LCDcursorOnBlink(void)	//displays LCD blinking cursor
{
	LCDcommand(LCD_DISP_ON_CURSOR_BLINK);
	//LCDcommand(LCD_DISP_ON_BLINK);
}
void LCDcursorOFF(void)	//turns OFF cursor
{
	LCDcommand(LCD_DISP_ON );
}
void LCDblank(void)		//blanks LCD
{
	LCDcommand(LCD_DISP_OFF);
}
void LCDvisible(void)		//Shows LCD
{
	LCDcommand(LCD_DISP_ON );
}
void LCDcursorLeft(uint8_t n)	//Moves cursor by n poisitions left
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(LCD_MOVE_CURSOR_LEFT);
	}
}
void LCDcursorRight(uint8_t n)	//Moves cursor by n poisitions left
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(LCD_MOVE_CURSOR_RIGHT);
	}
}
//adapted fro mAVRLIB
void LCDprogressBar(uint8_t progress, uint8_t maxprogress, uint8_t length)
{
	uint8_t i;
	uint16_t pixelprogress;
	uint8_t c;

	// draw a progress bar displaying (progress / maxprogress)
	// starting from the current cursor position
	// with a total length of "length" characters
	// ***note, LCD chars 0-5 must be programmed as the bar characters
	// char 0 = empty ... char 5 = full

	// total pixel length of bargraph equals length*PROGRESSPIXELS_PER_CHAR;
	// pixel length of bar itself is
	pixelprogress = ((progress*(length*PROGRESSPIXELS_PER_CHAR))/maxprogress);
	
	// print exactly "length" characters
	for(i=0; i<length; i++)
	{
		// check if this is a full block, or partial or empty
		// (u16) cast is needed to avoid sign comparison warning
		if( ((i*(uint16_t)PROGRESSPIXELS_PER_CHAR)+5) > pixelprogress )
		{
			// this is a partial or empty block
			if( ((i*(uint16_t)PROGRESSPIXELS_PER_CHAR)) > pixelprogress )
			{
				// this is an empty block
				// use space character?
				c = 0;
			}
			else
			{
				// this is a partial block
				c = pixelprogress % PROGRESSPIXELS_PER_CHAR;
			}
		}
		else
		{
			// this is a full block
			c = 5;
		}
		
		// write character to display
		LCDsendChar(c);
	}

}
void LCDprintXY(const char *s,uint8_t x, uint8_t y)
/* print string on lcd (no auto linefeed) in X,Y position*/
{
	LCDGotoXY(x,y);
	register char c;
	while ( (c = *s++) )
	LCDsendChar(c);
}