/*
 * GPIO.h
 *
 * Created: 10/17/2019 2:49:03 AM
 *  Author: H
 */ 
#ifndef GPIO_H_
#define GPIO_H_

#include "common.h"
#include "config.h"

bool_t port_direction(port_base base,ecore_u8 state);
bool_t pin_direction(port_base base,pin_no pin_no,ecore_u8 state);
bool_t pin_set(port_base base,pin_no pin_no);
bool_t pin_clear(port_base base,pin_no pin_no);
bool_t port_write(port_base base,ecore_u8 value);  
bool_t port_read(port_base base,ecore_u8* r_value);
bool_t pin_write(port_base base,pin_no pin_no,ecore_u8 value);  
bool_t pin_read(port_base base,pin_no pin_no,ecore_u8* r_value);
bool_t pull_up_port(port_base base);
bool_t pull_up_pin(port_base base,pin_no pin_no);



#endif /* GPIO_H_ */