/*
 * twi.c
 *
 * Created: 6/16/2021 4:29:26 AM
 *  Author: Hossam Mohamed
 */ 

#include "hal_twi.h"

#define ENABLE_ACK_POS 6
#define GLOBAL_CALL_POS 0

twi_ret_t twi_init(twi_t* twi_obj)
{
	if (twi_obj != NULL)
	{
		TWBR = twi_obj->twi_bit_rate;
		TWSR = twi_obj->twi_priscaler;
				
		TWAR = twi_obj->twi_slave_add; 
		
		if (twi_obj->twi_glob_call == GLOBAL_CALL_EN)
		{
			TWAR |= (1<<GLOBAL_CALL_POS);
		}
		else if(twi_obj->twi_glob_call == GLOBAL_CALL_DIS)
		{
			TWAR &= ~(1<<GLOBAL_CALL_POS); 
		}
		if (twi_obj->twi_ack_status == ACK)
		{
			TWCR |= 1<<TWEA;
		}
		else if (twi_obj->twi_ack_status == NOT_ACK)
		{
			TWCR &= ~(1<<TWEA);
		}
		return TWI_NO_ERR;
	}
	return TWI_ERR;
}

twi_ret_t twi_edit(twi_t* twi_obj)
{
	if (twi_obj != NULL)
	{
		twi_init(twi_obj);
		return TWI_NO_ERR;
	}
	return TWI_ERR;
}

twi_ret_t twi_send_slave_add_rw(U_8 s_add_rw, twi_trasmission_mode_t rw_status)
{
	TWDR = s_add_rw | rw_status;
	TWCR = (1<<TWINT | 1<<TWEN);
	twi_wait();
	if (twi_get_status() == TWI_MT_SLAW_SENT_ACK_GOT || twi_get_status() == TWI_MT_SLAW_SENT_NACK_GOT) 
	{
		return TWI_NO_ERR;
	}
	return TWI_ERR;
}

twi_ret_t twi_ms_byte(U_8* data_to_send)
{
	if (data_to_send != NULL)
	{
		TWDR = *data_to_send;
		TWCR = (1<<TWINT | 1<<TWEN);
		twi_wait();
		if (twi_get_status() == TWI_MT_DATA_SENT_ACK_GOT || twi_get_status() == TWI_MT_DATA_SENT_NACK_GOT)
		{
			return TWI_NO_ERR;
		}
	}
	return TWI_ERR;
}

twi_ret_t twi_sr_byte(U_8* data_get, twi_ack_status_t ack_or_not)
{
	if (data_get != NULL)
	{
		TWCR = (1<<TWINT | 1<<TWEN |1<<TWEA);
		if (ack_or_not == ACK)
		{
			TWCR |= 1<<TWEA;
		}
		twi_wait();
		if (twi_get_status() == TWI_SR_DATA_GOT_ACK_SENT || twi_get_status() == TWI_SR_DATA_GOT_NACK_SENT)
		{
			*data_get = TWDR;
			return TWI_NO_ERR;
		}
	}
	return TWI_ERR;
}

twi_ret_t twi_mr_byte(U_8* data_get, twi_ack_status_t ack_or_not)  
{
	if (data_get != NULL)
	{
		TWCR = (1<<TWINT | 1<<TWEN | 1<<TWEA);
		if (ack_or_not == ACK)
		{
			TWCR |= 1<<TWEA;
		}
		else if (ack_or_not == NOT_ACK)
		{
			TWCR &= ~(1<<TWEA);
		}
		twi_wait();
		if (twi_get_status() == TWI_MR_DATA_GOT_ACK_SENT || twi_get_status() == TWI_MR_DATA_GOT_NACK_SENT) 
		{
			*data_get = TWDR;
			return TWI_NO_ERR;
		}
	}
	return TWI_ERR;
}

twi_ret_t twi_ss_byte(U_8* data_to_send)  
{
	if (data_to_send != NULL)
	{
		TWDR = *data_to_send;
		TWCR = (1<<TWINT | 1<<TWEN);
		twi_wait();
		if (twi_get_status() == TWI_ST_DATA_SENT_ACK_GOT || twi_get_status() == TWI_ST_DATA_SENT_NACK_GOT) 
		{
			return TWI_NO_ERR;
		}
	}
	return TWI_ERR;
}


twi_ret_t twi_send_start()
{
	TWCR = (1<<TWINT | 1<<TWEN | 1<<TWSTA);
	twi_wait();
	if (twi_get_status() == TWI_MT_ST_SENT )
	{
		return TWI_NO_ERR;
	}
	return TWI_NO_ERR;
}

twi_ret_t twi_send_restart()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	twi_wait();
	if (twi_get_status() == TWI_MT_RP_ST_SENT)
	{
		return TWI_NO_ERR;
	}
	return TWI_NO_ERR;
}

twi_ret_t twi_send_stop()
{
	TWCR = (1<<TWINT | 1<<TWEN | 1<<TWSTO);
	return TWI_NO_ERR;
}

U_8 twi_get_status()
{
	return (TWSR&0XF8);
}

void twi_wait(void)
{
	while (!(TWCR & (1<<TWINT)));
}