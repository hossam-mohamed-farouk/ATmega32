/*
 * twi.h
 *
 * Created: 6/16/2021 4:29:39 AM
 *  Author: Hossam Mohamed
 */ 


#ifndef TWI_H_
#define TWI_H_

/************************************************************************************************************/
//TWI device driver for Atmega 32 microcontroller you can use it by creating an object of twi_t				*/
//and then fill it with it's config like twi_bit_rate, twi_priscaler, twi_operation_mode, twi_glob_call,   	*/
//twi_ack_status, and twi_slave_add. then you can use the APIs to init it, edit the config, twi_send_start 	*/
//twi_send_restart, twi_send_stop, twi_send_slave_add_rw, or send and receive data bytes using			   	*/
//master send, master recieve, slave send, slave receive												   	*/
// Each function return the status of it's calling Error or No Error										*/
/************************************************************************************************************/
	

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "data_types.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef enum
{
	TWI_NO_ERR,
	TWI_ERR
}twi_ret_t;


typedef enum
{
	PRISCALER_1 =	0,
	PRISCALER_4 =	1,
	PRISCALER_16 =	2,
	PRISCALER_64 =	3
}twi_priscaler_t;

typedef enum
{
	TWI_POLING,
	TWI_INT
}twi_operation_mode_t;

typedef enum
{
	GLOBAL_CALL_EN,
	GLOBAL_CALL_DIS
}twi_glob_call_status_t;

typedef enum
{
	NOT_ACK,
	ACK
}twi_ack_status_t;

typedef enum
{
	WRITE_DATA,
	READ_DATA
}twi_trasmission_mode_t;

typedef enum{
	//*************************MASTER TRANSMITTER MODE**************************************************//
	TWI_MT_ST_SENT 		   	    = 0x08,	//A START condition has been transmitted
	TWI_MT_RP_ST_SENT 		   	= 0x10, //A repeated START condition has been transmitted
	TWI_MT_SLAW_SENT_ACK_GOT  	= 0x18,	//SLA+W has been transmitted; ACK has been received
	TWI_MT_SLAW_SENT_NACK_GOT 	= 0x20,	//SLA+W has been transmitted; NOT-ACK has been received
	TWI_MT_DATA_SENT_ACK_GOT  	= 0x28,	//Data byte has been transmitted; ACK has been received
	TWI_MT_DATA_SENT_NACK_GOT 	= 0x30,	//Data byte has been transmitted; NOT-ACK has been received
	TWI_MT_ARBITRATION_LOST   	= 0x38,	//SLA+W has been transmitted; NOT-ACK has been received
	//**************************************************************************************************//
	//*************************MASTER RECEIVER MODE*****************************************************//
	TWI_MR_ST_SENT 		   	    = 0x08,	//A START condition has been transmitted
	TWI_MR_RP_ST_SENT 		   	= 0x10, //A repeated START condition has been transmitted
	TWI_MR_ARB_LOST_OR_NACK  	= 0x38,	//Arbitration lost in SLA+R or NOT ACK bit
	TWI_MR_SLAR_SENT_ACK_GOT 	= 0x40,	//SLA+R has been transmitted; ACK has been received
	TWI_MR_SLAR_SENT_NACK_GOT 	= 0x48,	//SLA+R has been transmitted; NOT ACK has been received
	TWI_MR_DATA_GOT_ACK_SENT  	= 0x50,	//Data byte has been received; ACK has been returned
	TWI_MR_DATA_GOT_NACK_SENT 	= 0x58,	//Data byte has been received; NOT ACK has been returned
	//**************************************************************************************************//
	//**************************SLAVE TRANSMITTER MODE***************************************************//
	TWI_ST_SLAR_GOT_ACK_SENT    		= 0xA8,	//Own SLA+R has been received; ACK has been returned
	TWI_ST_ARB_LOST_SLAR_GOT_ACK_SENT 	= 0xB0, //Arbitration lost in SLA+R as master; own SLA+R has been received; ACK has been returned
	TWI_ST_DATA_SENT_ACK_GOT  			= 0xB8,	//Data byte has been transmitted; ACK has been received
	TWI_ST_DATA_SENT_NACK_GOT  			= 0xC0,	//Data byte has been transmitted; NOT ACK has been received
	TWI_ST_DATA_SENT_ACK_RECEIVED	  	= 0xC8,	//Last data byte in TWDR has been transmitted (TWEA = “0”); ACK has been received
	//**************************************************************************************************//
	//**************************SLAVE RECEIVER MODE*****************************************************//
	TWI_SR_SLAW_GOT_ACK_SENT    		= 0x60,	//Own SLA+W has been received; ACK has been returned
	TWI_SR_ARB_LOST_SLAW_GOT_ACK_SENT 	= 0x68, //Arbitration lost in SLA+R/W as master; own SLA+W has been received; ACK has been returned
	TWI_SR_G_CALL_GOT_ACK_SENT	  		= 0x70,	//General call address has been received; ACK has been returned
	TWI_SR_ARB_LOST_G_CALL_GOT_ACK_SENT = 0x78, //Arbitration lost in SLA+R/W as master; General call address has been received; ACK has been returned
	TWI_SR_DATA_GOT_ACK_SENT  			= 0x80,	//Previously addressed with own	SLA+W; data has been received; ACK has been returned
	TWI_SR_DATA_GOT_NACK_SENT 			= 0x88,	//Previously addressed with own	SLA+W; data has been received; NOT ACK has been returned
	TWI_SR_PR_G_CALL_GOT_ACK_SENT		= 0x90,	//Previously addressed with general call; data has been received; ACK has been returned
	TWI_SR_G_CALL_GOT_NACK_SENT		   	= 0x98,	//Previously addressed with general call; data has been received; NOT ACK has been returned
	TWI_SR_STOP_OR_RP_ST_GOT_STILL_SLAVE= 0xA0,	//A STOP condition or repeated START condition has been received while still addressed as slave
	//****************************************************************************************************//
}twi_status_t;

typedef struct  
{
	U_8 twi_bit_rate;
	twi_priscaler_t twi_priscaler;
	twi_operation_mode_t twi_op_mode;
	twi_glob_call_status_t twi_glob_call;
	twi_ack_status_t twi_ack_status;
	U_8 twi_slave_add;
}twi_t;

twi_ret_t twi_init(twi_t* twi_obj);
twi_ret_t twi_edit(twi_t* twi_obj);

twi_ret_t twi_ms_byte(U_8* data_to_send);
twi_ret_t twi_mr_byte(U_8* data_get, twi_ack_status_t ack_or_not);

twi_ret_t twi_ss_byte(U_8* data_to_send);
twi_ret_t twi_sr_byte(U_8* data_get, twi_ack_status_t ack_or_not);

twi_ret_t twi_send_start();
twi_ret_t twi_send_restart();
twi_ret_t twi_send_stop();
twi_ret_t twi_send_slave_add_rw(U_8 s_add_rw, twi_trasmission_mode_t rw_status);

U_8 twi_get_status();
void twi_wait(void);

#endif /* TWI_H_ */