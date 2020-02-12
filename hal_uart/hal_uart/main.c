/*
 * hal_uart.c
 *
 * Created: 11/12/2019 6:40:47 PM
 * Author : H
 */ 

#include <avr/io.h>
#include "hal_uart.h"
#define F_CPU 1000000UL
#include <util/delay.h>

#define SET_OUT_DIR(reg,pin_no) reg |= (1<<pin_no)
#define SET_INPUT_DIR(reg,pin_no) reg &= ~(1<<pin_no)
#define TOGGEL_LED(reg,pin_no) reg ^= (1<<pin_no)

void cb_fun(void)
{
	TOGGEL_LED(PORTA,1);
}

int main(void)
{
	
	(*(volatile ecore_u8*)(0x5F)) |= (1<<7); 
	SET_OUT_DIR(DDRA,1);
	//DDRA = 0xff; 
	ecore_u16 data_to_send ='5';
	ecore_u16 received_data =0 ;
	
	//create uart obj
	gcfg_hal_uart_t my_uart_obj;
	my_uart_obj.trans_state = TX_ON;
	my_uart_obj.trans_int_state = UART_TX_INT_ON;
	my_uart_obj.trans_cb_func = cb_fun;
	
	my_uart_obj.receive_state = RX_OFF;
	my_uart_obj.receive_int_state = UART_RX_INT_OFF;
	//my_uart_obj.receive_cb_func = toggel_port_a;
	
	my_uart_obj.synch_mode = UART_ASYNCH_MODE;
	my_uart_obj.speed_mode = UART_NORMAL_SPEED_MODE;
	my_uart_obj.parity_state = UART_ODD_PARITY;
	my_uart_obj.char_size = UART_8_BIT_CHAR;
	my_uart_obj.stop_bit_no = UART_ONE_STOPBIT;
	
	
	
	
	hal_uart_init(&my_uart_obj);
	
	//hal_uart_deinit();
	
    /* Replace with your application code */
    while (1) 
    {
		 hal_uart_trans(data_to_send);
		//hal_uart_receive(&received_data);
		_delay_ms(1000);
		/*
		if ((received_data == '5')||(received_data == '6'))
		{	
		}
		*/
    }
}
