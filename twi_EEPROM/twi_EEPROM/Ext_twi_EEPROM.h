/*
 * Ext_twi_EEPROM.h
 *
 * Created: 6/17/2021 6:23:07 PM
 *  Author: Hossam Mohamed
 */ 

/**************************************************************************************/
//This EEPROM conneced to the microcontroller via TWI protocol						  */
//After init the EEPROM you can Write byet or page or array of bytes into the eeprom  */
//and also yo can read from it														  */
/**************************************************************************************/

#ifndef EXT_TWI_EEPROM_H_
#define EXT_TWI_EEPROM_H_
#include "hal_twi.h"
#include "data_types.h"

#define EEPROM_SLA	0XA2	//0b1010 0000	//0XA0 -> for page 1 and 0XA2 -> for page 2
#define MAX_ROM_ADD 0xFFFF  //Half of full memory size
#define PAGE_SIZE 256

typedef enum
{
	TWI_EEPROM_NO_ERR,
	TWI_EEPROM_ERR
}twi_eeprom_ret_t;

twi_eeprom_ret_t twi_eeprom_init(twi_t* twi_obj);
twi_eeprom_ret_t twi_eeprom_write_byte(U_16 rom_addr,U_8 data);
twi_eeprom_ret_t twi_eeprom_write_array(U_16 rom_begin_addr,U_8* data, U_16 data_length);
twi_eeprom_ret_t twi_eeprom_write_page(U_16 rom_begin_addr,U_8* data, U_16 no_of_bytes);

twi_eeprom_ret_t twi_eeprom_read_byte(U_16 rom_addr, U_8* data);








#endif /* EXT_TWI_EEPROM_H_ */