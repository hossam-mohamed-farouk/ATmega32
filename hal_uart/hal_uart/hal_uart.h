/*
 * hal_uart.h
 *
 * Created: 11/12/2019 6:44:52 PM
 *  Author: H
 */ 


#ifndef HAL_UART_H_
#define HAL_UART_H_

#include "common.h"
#include "hal_system_errors.h"

/******Config Baud Rate******/
#define UART_BAUD 1200
#define UART_FOSC 1000000

typedef enum
{
	TX_OFF = (0<<3),
	TX_ON = (1<<3),
}enum_trans_state_t;
	
typedef enum
{
	RX_OFF = (0<<4),
	RX_ON = (1<<4),
}enum_receive_state_t;
	
typedef enum
{
	UART_TX_INT_OFF = (0<<6),
	UART_TX_INT_ON = (1<<6),
}enum_trans_int_state_t;

typedef enum
{
	UART_RX_INT_OFF = (0<<7),
	UART_RX_INT_ON = (1<<7),
}enum_receive_int_state_t;

typedef enum
{
	UART_ASYNCH_MODE,
	UART_SYNCH_MODE = (1<<6),
}enum_comm_synch_mode_t;

typedef enum
{
	UART_OFF_PARITY = (0b00<<4),
	UART_EVEN_PARITY = (0b10<<4),
	UART_ODD_PARITY = (0b11<<4),
}enum_parity_state_t;

typedef enum
{
	UART_ONE_STOPBIT = (0<<3),
	UART_TWO_STOPBITS = (1<<3),
}enum_stop_bit_t;

typedef enum
{
	UART_5_BIT_CHAR = (0b00<<1),
	UART_6_BIT_CHAR = (0b01<<1),
	UART_7_BIT_CHAR = (0b10<<1),
	UART_8_BIT_CHAR = (0b11<<1),
	UART_9_BIT_CHAR = (0b111<<1),
}enum_char_size_t;

typedef enum
{
	UART_NORMAL_SPEED_MODE,
	UART_DOUBLE_SPEED_MODE,
}enum_comm_speed_mode_t;

typedef struct
{
	enum_trans_state_t trans_state;
	enum_receive_state_t receive_state;
	enum_parity_state_t parity_state;
	enum_comm_synch_mode_t synch_mode;
	enum_comm_speed_mode_t speed_mode;
	enum_trans_int_state_t trans_int_state;
	enum_receive_int_state_t receive_int_state;
	enum_stop_bit_t stop_bit_no;
	enum_char_size_t char_size;
	void(*trans_cb_func)(void);
	void(*receive_cb_func)(void);
}gcfg_hal_uart_t;

ecore_s8 hal_uart_init(gcfg_hal_uart_t* obj);
ecore_s8 hal_uart_trans(ecore_u16 data);
ecore_s8 hal_uart_receive(ecore_u16* data);
ecore_s8 hal_uart_deinit();




#endif /* HAL_UART_H_ */