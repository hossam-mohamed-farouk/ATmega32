/*
 * GPIO.c
 *
 * Created: 10/17/2019 2:48:43 AM
 *  Author: H
 */ 
#include <stdio.h>
#include "GPIO.h"

#define DIR_OFFSET 1
#define OUTPUT_OFFSET 2

bool_t port_direction(port_base base,ecore_u8 state)
{
	bool_t b_ret_val = E_TRUE;
	if((base==A)||(base==B)||(base==C)||(base==D))
	{
		if(state==INPUT)
		{
			(*(volatile ecore_u8*)(base+DIR_OFFSET)) &=0x00;
		}
		else if(state==OUTPUT)
		{
			(*(volatile ecore_u8*)(base+DIR_OFFSET)) |=0xff;
		}
		else
		{
			b_ret_val = E_FALSE; //Incorrect state
		}
	}
	else
	{
		b_ret_val = E_FALSE; //Unknown port base
	}
return b_ret_val;
}

bool_t pin_direction(port_base base,pin_no pin_no,ecore_u8 state)
{
	bool_t b_ret_val = E_TRUE;
	if((base==A)||(base==B)||(base==C)||(base==D))
	{
		if((pin_no>=PIN_0)&&(pin_no<=PIN_7))
		{
			if(state==INPUT)
			{
				(*(volatile ecore_u8*)(base+DIR_OFFSET)) &=~(1<<pin_no);
			}
			else if(state==OUTPUT)
			{
				(*(volatile ecore_u8*)(base+DIR_OFFSET)) |=(1<<pin_no);
			}
			else
			{
				b_ret_val = E_FALSE; //Incorrect state
			}
		}
		else
		{
			b_ret_val = E_FALSE; //Unknown pin number
		}
	}
	else
	{
		b_ret_val = E_FALSE; //Unknown port base
	}
	return b_ret_val;
}

bool_t pin_set(port_base base,pin_no pin_no)
{
	bool_t b_ret_val = E_TRUE;
	if((base==A)||(base==B)||(base==C)||(base==D))
	{
		(*(volatile ecore_u8*)(base+OUTPUT_OFFSET))|=(1<<pin_no);
			
	}
	else
	{
		b_ret_val = E_FALSE; //Unknown port base
	}
	return b_ret_val;
}

bool_t pin_clear(port_base base,pin_no pin_no)
{
	bool_t b_ret_val = E_TRUE;
	if((base==A)||(base==B)||(base==C)||(base==D))
	{	
		(*(volatile ecore_u8*)(base+OUTPUT_OFFSET))&=~(1<<pin_no);		
	}
	else
	{
		b_ret_val = E_FALSE; //Unknown port base
	}
	return b_ret_val;
}

bool_t port_write(port_base base,ecore_u8 value)
{
	bool_t b_ret_val = E_TRUE;
	if((base==A)||(base==B)||(base==C)||(base==D))
	{
		(*(volatile ecore_u8*)(base+OUTPUT_OFFSET)) = value;
	}
	else
	{
		b_ret_val = E_FALSE; //Unknown port base
	}
	return b_ret_val;
}

bool_t port_read(port_base base,ecore_u8* r_value)
{
	bool_t b_ret_val = E_TRUE;
	if((base==A)||(base==B)||(base==C)||(base==D))
	{
		*r_value=(*(volatile ecore_u8*)(base));
	}
	else
	{
		b_ret_val = E_FALSE; //Unknown port base
	}
	return b_ret_val;
}

bool_t pin_write(port_base base,pin_no pin_no,ecore_u8 value)
{
	bool_t b_ret_val = E_TRUE;
	if((base==A)||(base==B)||(base==C)||(base==D))
	{
		if((pin_no>=PIN_0)&&(pin_no<=PIN_7))
		{
			if(value==0)
			{
				(*(volatile ecore_u8*)(base+OUTPUT_OFFSET))&=(~(1<<pin_no));
			}
			else
			{
				(*(volatile ecore_u8*)(base+OUTPUT_OFFSET)|=(1<<pin_no));
			}
		}
		else
		{
			b_ret_val = E_FALSE; //Unknown pin number
		}
	}
	else
	{
		b_ret_val = E_FALSE; //Unknown port base
	}
	return b_ret_val;
}

bool_t pin_read(port_base base,pin_no pin_no,ecore_u8* r_value)
{
	bool_t b_ret_val = E_TRUE;
	if((base==A)||(base==B)||(base==C)||(base==D))
	{
		if((pin_no>=PIN_0)&&(pin_no<=PIN_7))
		{
			*r_value=(*(volatile ecore_u8*)(base)) & (1<<pin_no);
		}
		else
		{
			b_ret_val = E_FALSE; //Unknown pin number
		}
	}
	else
	{
		b_ret_val = E_FALSE; //Unknown port base
	}
	return b_ret_val;
}


bool_t pull_up_port(port_base base)
{
	bool_t b_ret_val = E_TRUE;
	if((base==A)||(base==B)||(base==C)||(base==D))
	{		
		(*(volatile ecore_u8*)(base+OUTPUT_OFFSET)) |= 0xff;
	}
	else
	{
		b_ret_val = E_FALSE; //Unknown port base
	}
	return b_ret_val;
}


bool_t pull_up_pin(port_base base,pin_no pin_no)
{
	bool_t b_ret_val = E_TRUE;
	if((base==A)||(base==B)||(base==C)||(base==D))
	{
		if((pin_no>=PIN_0)&&(pin_no<=PIN_7))
		{
			(*(volatile ecore_u8*)(base+OUTPUT_OFFSET)) |= (1<<pin_no);
		}
		else
		{
			b_ret_val = E_FALSE; //Unknown pin number
		}
	}
	else
	{
		b_ret_val = E_FALSE; //Unknown port base
	}
	return b_ret_val;
}



