/*
 * GccApplication1.c
 *
 * Created: 6/16/2021 2:46:57 AM
 * Author : Hossam Mohamed
 */ 

#include <avr/io.h>
#include "Ext_twi_EEPROM.h"


//EEPROM main
#if 1
int main(void)
{
	//char data = 0;
	char readed_data = 0;
	//char arr[5] ={1,2,3,4,5};
	char arr[256] = {0};
	int i = 0;
	
	twi_t my_twi;
	my_twi.twi_bit_rate = 32;
	my_twi.twi_priscaler = PRISCALER_1;
	my_twi.twi_glob_call = GLOBAL_CALL_EN;
	my_twi.twi_slave_add = 0x44;
	
	
	twi_eeprom_init(&my_twi);
	twi_eeprom_write_byte(0xffff, 5);
	
	//twi_eeprom_write_array(0,&i,5);
	twi_eeprom_write_page(0,(U_8*)arr,255);
	
	while (1)
	{
			for (i=0; i<10; i++)
			{
				if (i == 9)
				{
					i = 0;
				}
				twi_eeprom_read_byte(i, (U_8*)&readed_data);
				PORTD = readed_data;
				_delay_ms(500);
			}
	}
	
	return 0;
}
#endif

//Master transmitter node
#if 0
int main(void)
{
	char data = 0;
	twi_t my_twi;
	my_twi.twi_ack_status = ACK;
	my_twi.twi_bit_rate = 32;
	my_twi.twi_priscaler = PRISCALER_1;
	my_twi.twi_glob_call = GLOBAL_CALL_EN;
	my_twi.twi_slave_add = 0x44;
	
	twi_init(&my_twi);
	twi_send_start();
	twi_send_slave_add_rw(0x30, WRITE_DATA);
	//twi_ms_byte(&data);
	
	//twi_send_restart();
	
	//twi_send_stop();
	//twi_send_start();
	
	//twi_send_slave_add_rw(0x30, WRITE_DATA);
	
    /* Replace with your application code */
    while (1) 
    {
		twi_ms_byte(&data);
		data ++;
		
		if (data == 5)
		{
			//twi_send_stop();
			//twi_send_start();
			twi_send_restart();
			twi_send_slave_add_rw(0x22, WRITE_DATA);
		}
		if (data == 10)
		{
			data = 0;
			//twi_send_stop();
			//twi_send_start();
			twi_send_restart();
			twi_send_slave_add_rw(0x30, WRITE_DATA);			
		}
		_delay_ms(500);
    }
}
#endif

//Master receiver node
#if 0
int main(void)
{
	char data = 0;
	twi_ret_t s = -1;
	twi_t my_twi;
	my_twi.twi_ack_status = ACK;
	my_twi.twi_bit_rate = 32;
	my_twi.twi_priscaler = PRISCALER_1;
	my_twi.twi_glob_call = GLOBAL_CALL_EN;
	my_twi.twi_slave_add = 0x44;
	
	twi_init(&my_twi);
	twi_send_start();
	twi_send_slave_add_rw(0x22, READ_DATA);
	//twi_ms_byte(&data);
	
	//twi_send_restart();
	
	//twi_send_stop();
	//twi_send_start();
	
	//twi_send_slave_add_rw(0x30, WRITE_DATA);
	
	/* Replace with your application code */
	while (1)
	{
		twi_mr_byte(&data);
				
		//_delay_ms(500);
	}
}
#endif

//Slave1 node
#if 0
int main(void)
{
	twi_t slave_twi;
	slave_twi.twi_ack_status = ACK;
	slave_twi.twi_glob_call = GLOBAL_CALL_EN;
	slave_twi.twi_slave_add = 0x22;
	
	twi_init(&slave_twi);
	
	DDRA = 0xff;
	char data = 0;
	/* Replace with your application code */
	while (1)
	{
		if (twi_sr_byte(&slave_twi, &data) == TWI_NO_ERR)
		{
			PORTA = data;
		}
		//twi_ss_byte(&data);
	}
}

#endif

//Slave node2
#if 0
int main(void)
{
	twi_t slave2_twi;
	slave2_twi.twi_ack_status = ACK;
	slave2_twi.twi_glob_call = GLOBAL_CALL_EN;
	slave2_twi.twi_slave_add = 0x30;
	
	twi_init(&slave2_twi);
	
	DDRA = 0xff;
	char data = 0;
	/* Replace with your application code */
	while (1)
	{
		if (twi_sr_byte(&slave2_twi, &data) == TWI_NO_ERR)
		{
			PORTA = data;
		}
		//twi_ss_byte(&data);
	}
}
#endif