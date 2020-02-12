/*
 * TMU.c
 *
 * Created: 10/21/2019 5:36:53 PM
 *  Author: H
 */ 

#include "TMU.h"
#include <avr/interrupt.h>
#define MAX_NO_OF_TIMERS 1

static timer_obj* timers_adresses_buffer[MAX_NO_OF_TIMERS]; 
static ecore_u8 index_counter=0;


ISR(TIMER0_OVF_vect)
{
	 
	for (volatile ecore_u8 i=0;i<index_counter;i++)
	{
		if (timers_adresses_buffer[i] != NULL)
		{
			(timers_adresses_buffer[i]->remining_time) --;
		}
	}
	TCNT0=0;
}

bool_t tmu_init(timer_resolution tmu_resoltion)
{
	bool_t b_ret_val = E_TRUE;
	for(ecore_u8 i = 0; i < MAX_NO_OF_TIMERS; i++)
	{
		timers_adresses_buffer[i] = NULL;
	}
	(*(volatile ecore_u8*)(0x53)) = 0;//TCCR0 = 0;
	(*(volatile ecore_u8*)(0x52)) = 0; //TCNT0 = 0
	(*(volatile ecore_u8*)(0x5F)) |= (1<<7);    //En global interrupt (SREG pin I)
	(*(volatile ecore_u8*)(0x59)) |= (1<<0); //TIMSK |= (1<<0);
	
	if (tmu_resoltion == _1MS)
	{
		(*(volatile ecore_u8*)(0x53)) = 0x01;
	} 
	else if (tmu_resoltion == _8MS)
	{
		(*(volatile ecore_u8*)(0x53)) = 0x02;
	}
	else if (tmu_resoltion == _64MS)
	{
		(*(volatile ecore_u8*)(0x53)) = 0x03;
	}
	else if (tmu_resoltion == _256MS)
	{
		(*(volatile ecore_u8*)(0x53)) = 0x04;
	}
	else if (tmu_resoltion == _1024MS)
	{
		(*(volatile ecore_u8*)(0x53)) = 0x05;
	}
	else
	{
		b_ret_val = E_FALSE;
	}
	
	return b_ret_val;
}

bool_t start_timer(timer_obj* t_obj,ecore_u32 time,timer_type t_type,void(*cb_func)(void))
{
	bool_t b_ret_val = E_TRUE;
	if ((t_obj != NULL) && (cb_func != NULL))
	{
		if ((t_type == PERIODIC) || (t_type == ONE_SHOT))
		{
			t_obj->o_t_type = t_type;
			t_obj->o_cb_func = cb_func;
			t_obj->o_time = time;
			t_obj->remining_time = time;
			timers_adresses_buffer[index_counter]=t_obj;
			index_counter ++;
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

bool_t stop_timer(timer_obj* t_obj)
{
	bool_t b_ret_val = E_TRUE;	 
	if (t_obj != NULL)
	{
		for (ecore_u8 i=0;i<index_counter;i++)
		{
			if (timers_adresses_buffer[i] == t_obj)
			{
				timers_adresses_buffer[i] =NULL;
				break;
			}
		}
	} 
	else
	{
		b_ret_val = E_FALSE;
	}
	return b_ret_val;
}

bool_t tmu_dispatch(void)
{
	bool_t b_ret_val=E_TRUE;
	for (ecore_u8 i=0;i<index_counter;i++)
	{
		if (timers_adresses_buffer[i] != NULL)
		{
			if ((timers_adresses_buffer[i]->remining_time) <= 0)
			{
				if (timers_adresses_buffer[i]->o_t_type == PERIODIC)
				{
					timers_adresses_buffer[i]->o_cb_func();
					timers_adresses_buffer[i]->remining_time=timers_adresses_buffer[i]->o_time;
				}
				else if (timers_adresses_buffer[i]->o_t_type == ONE_SHOT)
				{
					timers_adresses_buffer[i]->o_cb_func();
					stop_timer(timers_adresses_buffer[i]);
				}
				else
				{
					b_ret_val = E_FALSE;
				}
			}
		}
			
	}
	return b_ret_val;
}
		

bool_t tmu_deinit(void)
{
	bool_t b_ret_val=E_TRUE;
	(*(volatile ecore_u8*)(0x53)) = 0;  //TCCR0=0x00;
	for(int i = 0; i < MAX_NO_OF_TIMERS; i++)
	 {
		timers_adresses_buffer[i] = NULL;
	 }
	 return b_ret_val;
}
