/*
 * Ext_twi_EEPROM.c
 *
 * Created: 6/17/2021 6:22:56 PM
 *  Author: Hossam Mohamed
 */ 

#include "Ext_twi_EEPROM.h"

twi_eeprom_ret_t twi_eeprom_init(twi_t* twi_obj)
{
	if (twi_obj != NULL)
	{
		twi_init(twi_obj);
		return TWI_EEPROM_NO_ERR;
	} 
	else
	{
		return TWI_EEPROM_ERR;
	}
}

twi_eeprom_ret_t twi_eeprom_write_byte(U_16 rom_addr,U_8 data)
{
	if ((data <= 255) && (rom_addr <= MAX_ROM_ADD))
	{
		U_8 d_to_send = 0;
		
		twi_send_start();
		
		twi_send_slave_add_rw(EEPROM_SLA, WRITE_DATA);
		
		d_to_send = (rom_addr)>>8;
		twi_ms_byte(&d_to_send);
		
		d_to_send = (U_8)rom_addr;
		twi_ms_byte(&d_to_send);
		
		d_to_send = data;
		twi_ms_byte(&d_to_send);
		
		twi_send_stop();
		_delay_ms(10);
		return TWI_EEPROM_NO_ERR;
	} 
	else
	{
		return TWI_EEPROM_ERR;
	}
}

twi_eeprom_ret_t twi_eeprom_write_array(U_16 rom_begin_addr,U_8* data, U_16 data_length)
{
	if ((data != NULL) && (data_length > 0) && ((rom_begin_addr+data_length) <= MAX_ROM_ADD))    
	{
		U_16 i = 0;
		for (i=0; i<data_length; i++)
		{
			twi_eeprom_write_byte(rom_begin_addr+i,data[i]);
		}
		return TWI_EEPROM_NO_ERR;
	} 
	else
	{
		return TWI_EEPROM_ERR;
	}
}

twi_eeprom_ret_t twi_eeprom_write_page(U_16 rom_begin_addr,U_8* data, U_16 no_of_bytes)
{
	if ((no_of_bytes > 0) && (no_of_bytes < 256) && (data != NULL) && ((rom_begin_addr+no_of_bytes) <= PAGE_SIZE))
	{
		U_16 i = 0;
		U_8 d_to_send = 0;
		
		twi_send_start();
		
		twi_send_slave_add_rw(EEPROM_SLA, WRITE_DATA);
		
		d_to_send = (rom_begin_addr)>>8;
		twi_ms_byte(&d_to_send);
		
		d_to_send = (U_8)rom_begin_addr;
		twi_ms_byte(&d_to_send);
		
		for (i=0; i<no_of_bytes; i++)
		{
			d_to_send = data[i];
			twi_ms_byte(&d_to_send);
		}
		
		twi_send_stop();
		_delay_ms(10);
		return TWI_EEPROM_NO_ERR;
	}
	else
	{
		return TWI_EEPROM_ERR;
	}
}



twi_eeprom_ret_t twi_eeprom_read_byte(U_16 rom_addr, U_8* data)
{
	if (data != NULL)
	{
		U_8 r_data = 0;
		U_8 d_to_send = 0;
		
		twi_send_start();

		twi_send_slave_add_rw(EEPROM_SLA, WRITE_DATA);
		
		d_to_send = 0x00;
		twi_ms_byte(&d_to_send);
		d_to_send = rom_addr;
		twi_ms_byte(&d_to_send);
		
		twi_send_restart();
		
		twi_send_slave_add_rw(EEPROM_SLA, READ_DATA);
		
		twi_mr_byte(&r_data, NOT_ACK);
		twi_send_stop();
		
		_delay_ms(10);
		*data = r_data;
		return TWI_EEPROM_NO_ERR;
	}
	else
	{
		return TWI_EEPROM_ERR;
	}
}
