/*
 * seven_seg.h
 *
 * Created: 10/18/2019 5:29:47 AM
 *  Author: H
 */ 


#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_
#include "common.h"

#define MAX_NO_OF_HANDLERS 4


typedef enum
{
	UNKNOWN_BASE,
	INVALID_MIN_INDEX=0X2F,
	D=0x30,
	C=0x33,
	B=0x36,
	A=0x39,
	INVALID_MAX_INDEX
}port_base;

typedef enum
{
	COMMON_ANODE,
	COMMON_CATHODE,
	UNKNOWN_TYPE
}seven_segment_type;



bool_t seven_segment_init(port_base base,seven_segment_type type,ecore_u8* handler);
bool_t seven_segment_display(ecore_u8 handler,ecore_u8 data);
bool_t seven_segment_reset(ecore_u8 handler);
bool_t seven_segment_deinit(ecore_u8 handler);


#endif /* SEVEN_SEG_H_ */