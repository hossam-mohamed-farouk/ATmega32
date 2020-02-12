/*
 * LCD.h
 *
 * Created: 10/26/2019 8:10:06 PM
 *  Author: H
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 8000000UL
#include <util/delay.h>
#include "common.h"
#define DIR_OFFSET 1
#define OUTPUT_OFFSET 2
#define  MAX_NO_OF_LCD 4

//LCD Command List
#define LCD_MOVE_DISP_RIGHT	        (0x1C)
#define LCD_MOVE_DISP_LEFT   		(0x18)
#define LCD_MOVE_CURSOR_RIGHT   	(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  	(0x10)
#define LCD_DISP_OFF_CURSOR_OFF  	(0x08)
#define LCD_DISP_OFF_CURSOR_ON  	(0x0A)
#define LCD_DISP_ON_CURSOR_BLINK  	(0x0E)
#define LCD_DISP_ON_CURSOR_BLIN  	(0x0F)
#define LCD_DISP_ON_CURSOR_OFF   	(0x0C)
#define LCD_DECREMENT_CURSOR   		(0x04)
#define LCD_SHIFT_DISPLAY_RIGHT   	(0x05)
#define LCD_INCREMENT_CURSOR   		(0x06)
#define LCD_SHIFT_DISPLAY_LEFT   	(0x07)
#define LCD_BEGIN_AT_FIRST_RAW		(0x80)
#define LCD_BEGIN_AT_SECOND_RAW		(0xC0)
#define LCD_CLEAR_SCREEN			(0x01)

typedef enum
{
	D=0x30,
	C=0x33,
	B=0x36,
	A=0x39,
}port_base;

typedef enum
{
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7
}pin_no;

typedef enum
{
	four_bits_mode,
	eight_bits_mode
}data_mode_type;

typedef struct
{
	port_base lcd_port_base;
	port_base lcd_c_base;
	pin_no en_pin;
	pin_no rs_pin;
	data_mode_type mode_type;
}lcd_info_t;

bool_t lcd_init(lcd_info_t* lcd_info);
bool_t lcd_cmd(lcd_info_t* lcd_info,ecore_u8 command);
bool_t lcd_display_char(lcd_info_t* lcd_info,ecore_u8 data);
bool_t lcd_display_string(lcd_info_t* lcd_info,ecore_u8* data);
bool_t lcd_go_to_xy(lcd_info_t* lcd_info,ecore_u8 line,ecore_u8 position);
bool_t lcd_clear_screan(lcd_info_t* lcd_info);

#endif /* LCD_H_ */