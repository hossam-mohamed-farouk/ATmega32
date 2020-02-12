/*
 * LCD.c
 *
 * Created: 10/26/2019 8:09:02 PM
 * Author : H
 */ 

#include <avr/io.h>
#include "LCD.h"



int main(void)
{
	ecore_u8* x="22";
	ecore_u8 name_1[16]="Hossam Mohamed";
	ecore_u8 name_2[16]="Farouk Kasem";
	lcd_info_t lcd_1;
	lcd_info_t lcd_2;
	
	//LCD_1 struct
	lcd_1.lcd_port_base=A;
	lcd_1.lcd_c_base=D;
	lcd_1.en_pin=PIN_2;
	lcd_1.rs_pin=PIN_3;
	lcd_1.mode_type=four_bits_mode;
	
	//LCD_2 struct
	lcd_2.lcd_port_base=C;
	lcd_2.lcd_c_base=D;
	lcd_2.en_pin=PIN_0;
	lcd_2.rs_pin=PIN_1;
	lcd_2.mode_type=four_bits_mode;
	
	//init and display on lcd_1
	lcd_init(&lcd_1);
	//lcd_cmd(&lcd_1,LCD_BEGIN_AT_SECOND_RAW);
	lcd_display_string(&lcd_1,name_1);
	lcd_cmd(&lcd_1,LCD_BEGIN_AT_SECOND_RAW);
	lcd_display_string(&lcd_1,name_2);
	lcd_cmd(&lcd_1,LCD_DISP_ON_CURSOR_OFF);
	//lcd_display_char(&lcd_1,'5');
	//lcd_display_char(&lcd_1,x);
	
	//init and display on lcd_2
	lcd_init(&lcd_2);
	lcd_go_to_xy(&lcd_2,0,5);
	lcd_display_string(&lcd_2,x);
	//lcd_clear_screan(&lcd_1);
	//lcd_display_string(&lcd_2,x);
	//lcd_cmd(&lcd_2,0x01);
    
    while (1) 
    {
		
		
		
    }
}

