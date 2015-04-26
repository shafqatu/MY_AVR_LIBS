#include "LiquidCrystal_I2C.h"
#include "TWI_driver.h"
#include <avr/io.h>
#include <string.h>
#include <stdlib.h>

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set:
//    DL = 1; 8-bit interface data
//    N = 0; 1-line display
//    F = 0; 5x8 dot character font
// 3. Display on/off control:
//    D = 0; Display off
//    C = 0; Cursor off
//    B = 0; Blinking off
// 4. Entry mode set:
//    I/D = 1; Increment by 1
//    S = 0; No shift
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).


void su_lcd_reset(void)
{
	
	send_to_lcd(0x00);
	_delay_ms(20);
	
	send_to_lcd(0x30 | En);
	send_to_lcd(0x30);
	_delay_ms(10);
	
	send_to_lcd(0x30 | En);
	send_to_lcd(0x30);
	_delay_ms(1);
	
	send_to_lcd(0x30 | En);
	send_to_lcd(0x30);
	_delay_ms(1);
	
	send_to_lcd(0x28 | En);
	send_to_lcd(0x28);
	_delay_ms(5);

}

void su_lcd_cmd(unsigned char cmd)
{
	unsigned char upper_4;
	unsigned char lower_4;
	
	upper_4 = (cmd & 0xF0);
	lower_4 = (cmd & 0x0F)<<4;
	
	send_to_lcd((upper_4 | En | LCD_BACKLIGHT));
	send_to_lcd((upper_4 | LCD_BACKLIGHT));
	
	send_to_lcd((lower_4 | En | LCD_BACKLIGHT));
	send_to_lcd((lower_4 | LCD_BACKLIGHT));
	
	_delay_ms(5);
}

void su_lcd_write(unsigned char data)
{
	uint8_t upper_4;
	uint8_t lower_4;
	
	upper_4 = (data & 0xF0);
	lower_4 = (data & 0x0F)<<4;
	
	send_to_lcd((upper_4 | En | LCD_BACKLIGHT | Rs));
	send_to_lcd((upper_4 | LCD_BACKLIGHT | Rs));
	
	send_to_lcd((lower_4 | En | LCD_BACKLIGHT | Rs));
	send_to_lcd((lower_4 | LCD_BACKLIGHT | Rs));
	
	_delay_ms(5);
	
}

void su_lcd_init()
{
		su_lcd_reset();
		su_lcd_cmd(0x01);
		su_lcd_cmd(0x06);
		su_lcd_cmd(0x0F);  
}

void su_lcd_goto_line(uint8_t line)
{
	if (line == 1)
	  su_lcd_cmd(0x00);
	else
		su_lcd_cmd(0xC0);
}

void su_lcd_write_string(char str[LCD_LEN])
{
	uint8_t i= 0;
	unsigned char c[1];
	for (i = 0; i < strlen(str); i++)
	{
		
		su_lcd_write(str[i]);
	}
}

void send_to_lcd(unsigned char data)
{ 
		Send_start();
		Send_adr(0x4E);
		Send_byte(data);
		Send_stop();
		_delay_ms(1);
}

