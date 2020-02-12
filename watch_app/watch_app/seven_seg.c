/*
 * seven_seg.c
 *
 * Created: 10/18/2019 5:30:08 AM
 *  Author: H
 */ 

#include "seven_seg.h"
#define DIR_OFFSET 1
#define OUTPUT_OFFSET 2
#define MAX_NO_TO_DISPLAY 9


static const ecore_u8 common_cathode_pattern[10]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};

//Each seven_segment must have an struct which save it's information
typedef struct
{
	port_base seven_seg_base;
	seven_segment_type seven_seg_type;
}seven_segment_info;


static ecore_u8 handler_counter = 0;       //Number of initialized seve_segments
static seven_segment_info ga_seven_seg_handlers[MAX_NO_OF_HANDLERS];  //Buffer of initialized seven_segments



bool_t seven_segment_init(port_base base,seven_segment_type type,ecore_u8* handler)
{
	bool_t b_ret_val = E_TRUE;
	
	if((base < INVALID_MAX_INDEX && base > INVALID_MIN_INDEX) && (handler != NULL))
	{
		if (handler_counter < MAX_NO_OF_HANDLERS)
		{
			if ((ga_seven_seg_handlers[handler_counter].seven_seg_base != A) && (ga_seven_seg_handlers[handler_counter].seven_seg_base != B) && (ga_seven_seg_handlers[handler_counter].seven_seg_base != C) && (ga_seven_seg_handlers[handler_counter].seven_seg_base != D))
			//((ga_seven_seg_handlers[handler_counter].seven_seg_type != COMMON_ANODE) && (ga_seven_seg_handlers[handler_counter].seven_seg_type != COMMON_CATHODE))
			{
				(*(volatile ecore_u8*)(base+DIR_OFFSET)) |= 0xff;
				ga_seven_seg_handlers[handler_counter].seven_seg_base=base;
				ga_seven_seg_handlers[handler_counter].seven_seg_type=type;
				*handler = handler_counter;
			}
			else 
			{
				handler_counter ++;
				seven_segment_init(base,type,handler);
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

bool_t seven_segment_display(ecore_u8 handler,ecore_u8 data)
{
	bool_t b_ret_val = E_TRUE;
	if((handler < MAX_NO_OF_HANDLERS) && (data <= MAX_NO_TO_DISPLAY))
	{
		if(ga_seven_seg_handlers[handler].seven_seg_base != 0)
		{
			if(ga_seven_seg_handlers[handler].seven_seg_type == COMMON_CATHODE)
			{
				*(volatile ecore_u8*)(ga_seven_seg_handlers[handler].seven_seg_base+OUTPUT_OFFSET) = common_cathode_pattern[data];

			}
			else if(ga_seven_seg_handlers[handler].seven_seg_type == COMMON_ANODE)
			{
				*(volatile ecore_u8*)(ga_seven_seg_handlers[handler].seven_seg_base+OUTPUT_OFFSET) = ~(common_cathode_pattern[data]);

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

bool_t seven_segment_reset(ecore_u8 handler)
{
	bool_t b_ret_val = E_TRUE;
		if(handler < MAX_NO_OF_HANDLERS)
		{
			if(ga_seven_seg_handlers[handler].seven_seg_base != 0)
			{
				if(ga_seven_seg_handlers[handler].seven_seg_type == COMMON_CATHODE)
				{
					*(volatile ecore_u8*)(ga_seven_seg_handlers[handler].seven_seg_base+OUTPUT_OFFSET) = common_cathode_pattern[0];
				}
				else if(ga_seven_seg_handlers[handler].seven_seg_type == COMMON_ANODE)
				{
					*(volatile ecore_u8*)(ga_seven_seg_handlers[handler].seven_seg_base+OUTPUT_OFFSET) = ~(common_cathode_pattern[0]);
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

bool_t seven_segment_deinit(ecore_u8 handler)
{
	bool_t b_ret_val = E_TRUE;
	if (handler < MAX_NO_OF_HANDLERS)
	{
		seven_segment_reset(handler);
		ga_seven_seg_handlers[handler].seven_seg_base = UNKNOWN_BASE;
		ga_seven_seg_handlers[handler].seven_seg_type = UNKNOWN_TYPE;
		handler_counter = handler;	
	}
	else
	{
		b_ret_val = E_FALSE;
	}
return b_ret_val;
}
