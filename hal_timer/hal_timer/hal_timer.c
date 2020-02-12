/*
 * hal_timer.c
 *
 * Created: 11/1/2019 7:23:11 PM
 *  Author: H
 */ 
#include "hal_timer.h"
#include "hal_system_errors.h"

//genum_timer_base_t timer_obj_addresses[MAX_NO_OF_TIMERS];

ecore_s8 hal_timer_init(gcfg_hal_timer_t* obj)
{
	ecore_s8 ret_val = E_OK;
	if (obj != NULL)
	{
		if (obj->t_base == TIMER_0)
		{
			if (obj->int_s == INTERRUPT_EN)
			{
				if (obj->t_mode == NORMAL_MODE)
				{
					*(volatile ecore_u8*)(0x5f) |= (1<<7);
					*(volatile ecore_u8*)(0x59) |= (1<<0);
					*(volatile ecore_u8*)(0x53) |= (obj->t_clk);
				}
				else if (obj->t_mode == COMPARE_MATCH_OUTPUT_MODE)
				{
					*(volatile ecore_u8*)(0x5f) |= (1<<7);
					*(volatile ecore_u8*)(0x59) |= (1<<1);
					*(volatile ecore_u8*)(0x5c) = (obj->cmp_value);
					*(volatile ecore_u8*)(0x53) |= (obj->t_clk);
				}
				else
				{
					ret_val = INVALID_ARG;
				}
			}
			else if (obj->int_s == INTERRUPT_DIS)
			{
				if (obj->t_mode == NORMAL_MODE)
				{
					*(volatile ecore_u8*)(0x53) |= (obj->t_clk);
				}
				else if (obj->t_mode == COMPARE_MATCH_OUTPUT_MODE)
				{
					*(volatile ecore_u8*)(0x53) |= 0b00001000;
					*(volatile ecore_u8*)(0x53) |= (1<<7);
					*(volatile ecore_u8*)(0x5c) = (obj->cmp_value);
					*(volatile ecore_u8*)(0x53) |= (obj->cmp_pin);
					*(volatile ecore_u8*)(0x53) |= (obj->t_clk);
				}
				else
				{
					ret_val = INVALID_ARG;
				}
			}
		}
		else if (obj->t_base == TIMER_2)
		{
			if (obj->int_s == INTERRUPT_EN)
			{
				if (obj->t_mode == NORMAL_MODE)
				{
					*(volatile ecore_u8*)(0x5f) |= (1<<7);
					*(volatile ecore_u8*)(0x59) |= (1<<6);
					*(volatile ecore_u8*)(0x45) |= (obj->t_clk);
				}
				else if (obj->t_mode == COMPARE_MATCH_OUTPUT_MODE)
				{
					*(volatile ecore_u8*)(0x5f) |= (1<<7);
					*(volatile ecore_u8*)(0x59) |= (1<<7);
					*(volatile ecore_u8*)(0x43) = (obj->cmp_value);
					*(volatile ecore_u8*)(0x45) |= (obj->t_clk);
				}
				else
				{
					ret_val = INVALID_ARG;
				}
			}
			else if (obj->int_s == INTERRUPT_DIS)
			{
				if (obj->t_mode == NORMAL_MODE)
				{
					*(volatile ecore_u8*)(0x45) |= (obj->t_clk);
				}
				else if (obj->t_mode == COMPARE_MATCH_OUTPUT_MODE)
				{
					*(volatile ecore_u8*)(0x45) |= 0b00001000;
					*(volatile ecore_u8*)(0x45) |= (1<<7);
					*(volatile ecore_u8*)(0x43) = (obj->cmp_value);
					*(volatile ecore_u8*)(0x45) |= (obj->cmp_pin);
					*(volatile ecore_u8*)(0x45) |= (obj->t_clk);
				}
				else
				{
					ret_val = INVALID_ARG;
				}
			}
		}
	}
	else
	{
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

ecore_s8 hal_timer_deinit(gcfg_hal_timer_t * obj)
{
	ecore_s8 ret_val = E_OK;
	if (obj != NULL)
	{
		if (obj->t_base == TIMER_0)
		{
			*(volatile ecore_u8*)(0x53) =0x00;
		} 
		else if (obj->t_base == TIMER_2)
		{
			*(volatile ecore_u8*)(0x45) =0x00;
		}
		else
		{
			ret_val = INVALID_ARG;
		}
	} 
	else
	{
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

ecore_s8 hal_timer_read(gcfg_hal_timer_t * obj,ecore_u8 *value)
{
	ecore_s8 ret_val = E_OK;
	if ((obj != NULL)&&(value != NULL))
	{
		if (obj->t_base == TIMER_0)
		{
			*value = *(volatile ecore_u8*)(0x52);
		} 
		else if (obj->t_base == TIMER_2)
		{
			*value = *(volatile ecore_u8*)(0x44);
		}
	} 
	else
	{
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

ecore_s8 hal_timer_update(gcfg_hal_timer_t * obj,ecore_u8 value)
{
	ecore_s8 ret_val = E_OK;
	if (obj != NULL)
	{
		if (obj->t_base == TIMER_0)
		{
			*(volatile ecore_u8*)(0x52) = value;
		}
		else if (obj->t_base == TIMER_2)
		{
			*(volatile ecore_u8*)(0x44) = value;
		}
	}
	else
	{
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

ecore_s8 hal_timer_update_cmp(gcfg_hal_timer_t * obj,ecore_u8 value)
{
	ecore_s8 ret_val = E_OK;
	if (obj != NULL)
	{
		if (obj->t_base == TIMER_0)
		{
			*(volatile ecore_u8*)(0x5c) = value;
		}
		else if (obj->t_base == TIMER_2)
		{
			*(volatile ecore_u8*)(0x43) = value;
		}
	}
	else
	{
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

ecore_s8 hal_timer_is_timer_finish(gcfg_hal_timer_t * obj,bool_t *res)
{
	ecore_s8 ret_val = E_OK;
	if ((obj != NULL)&&(res != NULL))
	{
		if (obj->t_base == TIMER_0)
		{
			if (obj->t_mode == NORMAL_MODE)
			{
				if ((*(volatile ecore_u8*)(0x58)|(1<<0)) == 1)
				{
					*res = E_TRUE;
				} 
				else
				{
					*res = E_FALSE;
				}
			} 
			else if (obj->t_mode == COMPARE_MATCH_OUTPUT_MODE)
			{
				if ((*(volatile ecore_u8*)(0x58)|(1<<1)) == 1)
				{
					*res = E_TRUE;
				} 
				else
				{
					*res = E_FALSE;
				}
			}
		}
		else if (obj->t_base == TIMER_2)
		{
			if (obj->t_mode == NORMAL_MODE)
			{
				if ((*(volatile ecore_u8*)(0x58)|(1<<6)) == 1)
				{
					*res = E_TRUE;
				}
				else
				{
					*res = E_FALSE;
				}
			}
			else if (obj->t_mode == COMPARE_MATCH_OUTPUT_MODE)
			{
				if ((*(volatile ecore_u8*)(0x58)|(1<<7)) == 1)
				{
					*res = E_TRUE;
				}
				else
				{
					*res = E_FALSE;
				}
			}
		}
	}
	else
	{
		ret_val = INVALID_ARG;
	}
	return ret_val;
}
