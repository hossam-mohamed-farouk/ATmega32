/*
 * hal_spi.c
 *
 * Created: 11/15/2019 7:16:24 PM
 *  Author: H
 */ 
#include "hal_spi.h"
#include "hal_system_errors.h"
#include <avr/interrupt.h>

gcfg_hal_spi_t* g_obj_adress;

ISR(SPI_STC_vect)
{
	g_obj_adress->spi_cb_func();
}

ecore_s8 hal_spi_init(gcfg_hal_spi_t* obj)
{
	ecore_s8 ret_val = E_OK;
	if (obj != NULL)
	{
		//SPI status
		if (obj->spi_state == SPI_MASTER)
		{
			*(volatile ecore_u8*)(0x2D) |= (1<<4);
		} 
		else if (obj->spi_state == SPI_SLAVE)
		{
			*(volatile ecore_u8*)(0x2D) &= ~(1<<4);
		}
		//PINS config
		if (obj->spi_state == SPI_MASTER)
		{
			*(volatile ecore_u8*)(0x37) |= (1<<4) | (1<<5) | (1<<7);  //SS & MOSI & SCK o/p
			*(volatile ecore_u8*)(0x37) &= ~(1<<6); //MISO i/p
		//	*(volatile ecore_u8*)(0x38) |= (1<<6); //MISO pullup-res
		} 
		else if (obj->spi_state == SPI_SLAVE)
		{
			*(volatile ecore_u8*)(0x37) |= (1<<6) ;  //MISO o/p
			*(volatile ecore_u8*)(0x37) &= ~(1<<4); //SS i/p
			*(volatile ecore_u8*)(0x37) &= ~(1<<5); //MOSI i/p
			*(volatile ecore_u8*)(0x37) &= ~(1<<7); //SCK i/p
		}
		//Interrupt config  
		if (obj->int_state == SPI_INT_ON)
		{
			*(volatile ecore_u8*)(0x2D) |= (1<<7);
		} 
		else if (obj->int_state == SPI_INT_OFF)
		{
			*(volatile ecore_u8*)(0x2D) &= ~(1<<7);
		}
		//Data order
		if (obj->data_order == SPI_LSB_TRANS_FIRST)
		{
			*(volatile ecore_u8*)(0x2D) |= (1<<5);
		} 
		else if (obj->data_order == SPI_MSB_TRANS_FIRST)
		{
			*(volatile ecore_u8*)(0x2D) &= ~(1<<5);
		}
		//Operating edge config
		if (obj->operating_edge == SPI_TRANS_AT_FALLING)
		{
			*(volatile ecore_u8*)(0x2D) |= (1<<2);
		} 
		else if (obj->operating_edge == SPI_TRANS_AT_RISING)
		{
			*(volatile ecore_u8*)(0x2D) &= ~(1<<2);
		}
		//Sampling edge config (WHEN NO DATA SENDING)
		if (obj->sampling_edge == SPI_HIGH_EDGE)
		{
			*(volatile ecore_u8*)(0x2D) |= (1<<3);
		}
		else if (obj->sampling_edge == SPI_LOW_EDGE)
		{
			*(volatile ecore_u8*)(0x2D) &= ~(1<<3);
		}
		//CLK select
		if (obj->spi_state == SPI_MASTER)
		{
			*(volatile ecore_u8*)(0x2D) |= (obj->spi_clock);
			//Double speed mode
			if (obj->double_speed == SPI_DOUBLE_SPEED_ON)
			{
				*(volatile ecore_u8*)(0x2E) |= (1<<0);
			}
			else if (obj->double_speed == SPI_DOUBLE_SPEED_OFF)
			{
				*(volatile ecore_u8*)(0x2E) &= ~(1<<0);
			}
		} 
		//Enable SPI
		*(volatile ecore_u8*)(0x2D) |= (1<<6);
	} 
	else
	{
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

ecore_s8 hal_spi_trans(ecore_u16 data)
{
	ecore_s8 ret_val = E_OK;
	*(volatile ecore_u8*)(0x2F) = data;
	while(((*(volatile ecore_u8*)(0x2E)) && (1<<7)) == 0);
	return ret_val;
}

ecore_s8 hal_spi_receive(ecore_u16* data)
{
	ecore_s8 ret_val = E_OK;
	if (data != NULL)
	{
		while(!((*(volatile ecore_u8*)(0x2E)) & (1<<7)));
		*data= *(volatile ecore_u8*)(0x2F);
	} 
	else
	{
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

ecore_s8 hal_spi_deinit()
{
	ecore_s8 ret_val = E_OK;
	*(volatile ecore_u8*)(0x2D) = 0;
	*(volatile ecore_u8*)(0x2F) = 0;
	*(volatile ecore_u8*)(0x2E) = 0;
	return ret_val;
}