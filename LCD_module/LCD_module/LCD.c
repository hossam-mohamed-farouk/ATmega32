/*
 * LCD.c
 *
 * Created: 10/26/2019 8:10:19 PM
 *  Author: H
 */ 

#include "LCD.h"

static ecore_u8 handler_count=0;

bool_t lcd_init(lcd_info_t* lcd_info)
{
	bool_t b_ret_val = E_TRUE;
	if (handler_count < MAX_NO_OF_LCD)
	{
		if ((lcd_info->lcd_port_base==A)||(lcd_info->lcd_port_base==B)||(lcd_info->lcd_port_base==C)||(lcd_info->lcd_port_base==D))
		{
			if ((lcd_info->lcd_c_base==A)||(lcd_info->lcd_c_base==B)||(lcd_info->lcd_c_base==C)||(lcd_info->lcd_c_base==D))
			{
				if  (((lcd_info->en_pin) >= PIN_0) && ((lcd_info->en_pin) <= PIN_7) && ((lcd_info->rs_pin) >= PIN_0) && ((lcd_info->rs_pin) <= PIN_7))
				{
					(*(volatile ecore_u8*)((lcd_info->lcd_port_base)+DIR_OFFSET)) = 0xff;
					(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+DIR_OFFSET)) |= (1<<(lcd_info->rs_pin));
					(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+DIR_OFFSET)) |= (1<<(lcd_info->en_pin));
					(*(volatile ecore_u8*)((lcd_info->lcd_port_base)+OUTPUT_OFFSET)) = 0x00;
					if (lcd_info->mode_type == eight_bits_mode)
					{
						(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) &= ~(1<<(lcd_info->en_pin));
						_delay_us(2000);
						lcd_cmd(lcd_info,0x38);
						
						lcd_cmd(lcd_info,0x0E);
						lcd_cmd(lcd_info,0x01);
						_delay_us(2000);
						lcd_cmd(lcd_info,0x06);
						handler_count ++;
					}
					else if(lcd_info->mode_type == four_bits_mode)
					{
						(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) &= ~(1<<(lcd_info->en_pin));
						lcd_cmd(lcd_info,0x33);
						lcd_cmd(lcd_info,0x32);
						lcd_cmd(lcd_info,0x28);
						
						lcd_cmd(lcd_info,0x0E);
						lcd_cmd(lcd_info,0x01);
						_delay_us(2000);
						lcd_cmd(lcd_info,0x06);
						handler_count ++;
					}
					else
					{
						b_ret_val = E_FALSE;
					}
				}
				else
				{
					b_ret_val = E_FALSE;
				}
				
			}
			else
			{
				b_ret_val = E_FALSE;
			}
		}
		else
		{
			b_ret_val = E_FALSE;
		}
	}
	else
	{
		b_ret_val = E_FALSE;
	}
	return b_ret_val;
}

bool_t lcd_cmd(lcd_info_t* lcd_info,ecore_u8 command)
{
	bool_t b_ret_val = E_TRUE;
	if(lcd_info->mode_type == eight_bits_mode)
	{
		(*(volatile ecore_u8*)((lcd_info->lcd_port_base)+OUTPUT_OFFSET)) = command;
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) &= ~(1<<(lcd_info->rs_pin));
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) |= (1<<(lcd_info->en_pin));
		_delay_us(1);
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) &= ~(1<<(lcd_info->en_pin));
		_delay_us(100);
		
	}
	else if(lcd_info->mode_type == four_bits_mode)
	{
		(*(volatile ecore_u8*)((lcd_info->lcd_port_base)+OUTPUT_OFFSET)) = command >> 4;
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) &= ~(1<<(lcd_info->rs_pin));
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) |= (1<<(lcd_info->en_pin));
		_delay_us(1);
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) &= ~(1<<(lcd_info->en_pin));
		_delay_us(100);
		(*(volatile ecore_u8*)((lcd_info->lcd_port_base)+OUTPUT_OFFSET)) = command & 0x0F;
		
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) |= (1<<(lcd_info->en_pin));
		_delay_us(1);
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) &= ~(1<<(lcd_info->en_pin));
		_delay_us(100);
	}
	else
	{
		b_ret_val = E_FALSE;
	}
	
	return b_ret_val;
}

bool_t lcd_display_char(lcd_info_t* lcd_info,ecore_u8 data)
{
	bool_t b_ret_val = E_TRUE;
	
	if(lcd_info->mode_type == eight_bits_mode)
	{
		(*(volatile ecore_u8*)((lcd_info->lcd_port_base)+OUTPUT_OFFSET))=data;
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) |= (1<<(lcd_info->rs_pin));
		
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) |= (1<<(lcd_info->en_pin));
		_delay_us(1);
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) &= ~(1<<(lcd_info->en_pin));
		_delay_us(100);
	}
	else if(lcd_info->mode_type == four_bits_mode)
	{
		(*(volatile ecore_u8*)((lcd_info->lcd_port_base)+OUTPUT_OFFSET)) = data >> 4;
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) |= (1<<(lcd_info->rs_pin));
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) |= (1<<(lcd_info->en_pin));
		_delay_us(1);
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) &= ~(1<<(lcd_info->en_pin));
		(*(volatile ecore_u8*)((lcd_info->lcd_port_base)+OUTPUT_OFFSET)) = data & 0x0F;
		
		
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) |= (1<<(lcd_info->en_pin));
		_delay_us(1);
		(*(volatile ecore_u8*)((lcd_info->lcd_c_base)+OUTPUT_OFFSET)) &= ~(1<<(lcd_info->en_pin));
		_delay_us(100);
	}
	else
	{
		b_ret_val = E_FALSE;
	}

	return b_ret_val;
}

bool_t lcd_display_string(lcd_info_t* lcd_info,ecore_u8* data)
{
	bool_t b_ret_val = E_TRUE;
	if(data != NULL)
	{
	    ecore_u8 i=0;
		while(data[i] != 0)
		{
			lcd_display_char(lcd_info,data[i]);
			i++;
		}
	}
	else
	{
		b_ret_val = E_FALSE;
	}
	return b_ret_val;
}

bool_t lcd_go_to_xy(lcd_info_t* lcd_info,ecore_u8 line,ecore_u8 position)
{
	bool_t b_ret_val = E_TRUE;
	if(lcd_info != NULL)
	{
		if(line==0)
		{
			if (position < 16 && position >=0)
			{
				lcd_cmd(lcd_info,0x80+position);
			}
			else
			{
				b_ret_val = E_FALSE;
			}
		}
		else if (line==1)
		{
			if (position < 16 && position >=0)
			{
				lcd_cmd(lcd_info,0xc0+position);
			}
			else
			{
				b_ret_val = E_FALSE;
			}
		}
		else
		{
			b_ret_val = E_FALSE;
		}
	}
	else
	{
		b_ret_val = E_FALSE;
	}
	return b_ret_val;
}

bool_t lcd_clear_screan(lcd_info_t* lcd_info)
{
	bool_t b_ret_val = E_TRUE;
	if(lcd_info != NULL)
	{
		lcd_cmd(lcd_info,LCD_CLEAR_SCREEN);
	}
	else
	{
		b_ret_val = E_FALSE;
	}
	return b_ret_val;
}