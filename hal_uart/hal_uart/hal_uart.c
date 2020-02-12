/*
 * hal_uart.c
 *
 * Created: 11/12/2019 6:45:06 PM
 *  Author: H
 */ 

#include "hal_uart.h"
#include <avr/interrupt.h>

gcfg_hal_uart_t* g_obj_adress;

ISR(USART_TXC_vect)
{
	g_obj_adress->trans_cb_func();
}

ISR(USART_RXC_vect)
{
	g_obj_adress->receive_cb_func();
}


ecore_s8 hal_uart_init(gcfg_hal_uart_t* obj)
{
	ecore_s8 ret_val = E_OK;
	if (obj != NULL)
	{
		/******Baud Rate config******/
		ecore_u32 ubrr_val;
		g_obj_adress = obj;
		if ((obj->synch_mode == UART_ASYNCH_MODE) && (obj->speed_mode == UART_NORMAL_SPEED_MODE))
		{
			ubrr_val = (ecore_u32)((UART_FOSC/(16*UART_BAUD))-1);
			*(volatile ecore_u8*)(0x40) = (ecore_u8)(ubrr_val >> 8);
			*(volatile ecore_u8*)(0x29) = (ecore_u8)ubrr_val;
		} 
		else if((obj->synch_mode == UART_ASYNCH_MODE) && (obj->speed_mode == UART_DOUBLE_SPEED_MODE))
		{
			ubrr_val = (ecore_u32)((UART_FOSC/(8*UART_BAUD))-1);
			*(volatile ecore_u8*)(0x40) = (ecore_u8)(ubrr_val >> 8);
			*(volatile ecore_u8*)(0x29) = (ecore_u8)ubrr_val;
		}
		else if(obj->synch_mode == UART_SYNCH_MODE)
		{
			ubrr_val = (ecore_u32)((UART_FOSC/(2*UART_BAUD))-1);
			*(volatile ecore_u8*)(0x40) = (ecore_u8)(ubrr_val >> 8);
			*(volatile ecore_u8*)(0x29) = (ecore_u8)ubrr_val;
		}
		else
		{
			ret_val = INVALID_ARG;
		}
		/*****Char Size******/
		if (obj->char_size != UART_9_BIT_CHAR)
		{
			*(volatile ecore_u8*)(0x40) = (1<<7) | (obj->char_size);
		} 
		else if (obj->char_size == UART_9_BIT_CHAR)
		{
			*(volatile ecore_u8*)(0x40) = (1<<7) | ((obj->char_size)&0b11); //&0b11
			*(volatile ecore_u8*)(0x2A) = (1<<2);
		}
		/*****Double speed config******/
		if (obj->speed_mode == UART_DOUBLE_SPEED_MODE)
		{
			*(volatile ecore_u8*)(0x2B) |= (1<<1);
		} 
		/*****parity config******/
		*(volatile ecore_u8*)(0x40) |= (1<<7) | (obj->parity_state);
		/*****synch comm config******/
		*(volatile ecore_u8*)(0x40) |= (1<<7) | (obj->synch_mode);
		/*****stop_bit config******/
		*(volatile ecore_u8*)(0x40) |= (1<<7) | (obj->stop_bit_no);
		/*****Trans_int config******/
		*(volatile ecore_u8*)(0x2A) |= (obj->trans_int_state);
		/*****Receive_int config******/
		*(volatile ecore_u8*)(0x2A) |= (obj->receive_int_state);
		/*****Receive config******/
		*(volatile ecore_u8*)(0x2A) |= (obj->receive_state);
		/*****Transmit config******/
		*(volatile ecore_u8*)(0x2A) |= (obj->trans_state);
	} 
	else
	{
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

ecore_s8 hal_uart_trans(ecore_u16 data)
{
	ecore_s8 ret_val = E_OK;
	if (g_obj_adress->trans_state == TX_ON)
	{
		while(!(*(volatile ecore_u8*)(0x2B) & (1<<5)));
		if (g_obj_adress->char_size == UART_9_BIT_CHAR)
		{
			*(volatile ecore_u8*)(0x2A) |= ((data >> 8)&1);
		}
		*(volatile ecore_u8*)(0x2C) = (ecore_u8)data;
	}
	else
	{
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

ecore_s8 hal_uart_receive(ecore_u16* data)
{
	ecore_s8 ret_val = E_OK;
	if (data != NULL)
	{
		*data = 0;
		if (g_obj_adress->receive_state == RX_ON)
		{
			while(!((*(volatile ecore_u8*)(0x2B)) & (1<<7)));		 //check rec. flag
			if (g_obj_adress->parity_state != UART_OFF_PATITY)
			{
				if (((*(volatile ecore_u8*)(0x2B) >> 2) & 1) != 1)	//Check parity flag
				{
					if (g_obj_adress->char_size == UART_9_BIT_CHAR)
					{
						*data= ((*(volatile ecore_u8*)(0x2A) & (1<<1)) << 8); //get the MSB
					}
					*data |= *(volatile ecore_u8*)(0x2C);
				}
			}
			else if (g_obj_adress->parity_state == UART_OFF_PATITY)
			{
				if (g_obj_adress->char_size == UART_9_BIT_CHAR)
				{
					*data= ((*(volatile ecore_u8*)(0x2A) & (1<<1)) << 8);  //try it
					*data |= *(volatile ecore_u8*)(0x2C);
				}
				else if (g_obj_adress->char_size != UART_9_BIT_CHAR)
				{
					*data |= *(volatile ecore_u8*)(0x2C);
				}
			}
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

/*
*data = 0;
while(!((*(volatile ecore_u8*)(0x2B)) & (1<<7)));   //check rec. flag
if (((*(volatile ecore_u8*)(0x2B) >> 2) & 1) != 1)  //Check parity flag
{
	if (g_obj_adress->char_size == UART_9_BIT_CHAR)
	{
		*data = ((*(volatile ecore_u8*)(0x2A) & 1) << 8);
	}
	*data |= *(volatile ecore_u8*)(0x2C);
}
*/

ecore_s8 hal_uart_deinit()
{
	ecore_s8 ret_val = E_OK;
	*(volatile ecore_u8*)(0x40) = 0;
	*(volatile ecore_u8*)(0x29) = 0;
	*(volatile ecore_u8*)(0x2A) = 0;
	return ret_val;
}