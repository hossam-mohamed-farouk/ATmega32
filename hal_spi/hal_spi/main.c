/*
 * hal_spi.c
 *
 * Created: 11/15/2019 7:14:27 PM
 * Author : H
 */ 

#include <avr/io.h>
#include "hal_spi.h"
#define F_CPU 1000000UL
#include <util/delay.h>

#define SET_OUT_DIR(reg,pin_no) reg |= (1<<pin_no)
#define SET_INPUT_DIR(reg,pin_no) reg &= ~(1<<pin_no)
#define TOGGEL_LED(reg,pin_no) reg ^= (1<<pin_no)

int main(void)
{
	//ecore_u8 data_to_send = 4;
	//ecore_u8 received_data;
	ecore_u8 i=0;
	
	//create SPI object
	gcfg_hal_spi_t my_spi;
	my_spi.spi_state = SPI_MASTER;
	my_spi.int_state = SPI_INT_OFF;
	my_spi.data_order = SPI_MSB_TRANS_FIRST;
	my_spi.operating_edge = SPI_TRANS_AT_FALLING; //High
	my_spi.sampling_edge = SPI_LOW_EDGE;  //Idle to active
	my_spi.spi_clock = CLK_DIV_4; 
	my_spi.double_speed = SPI_DOUBLE_SPEED_OFF;
  
  hal_spi_init(&my_spi);
  
  
    while (1) 
    {
		for (i=0;i<9;i++)
		{
			hal_spi_trans(i);
			_delay_ms(1000);
		}
		
    }
}

