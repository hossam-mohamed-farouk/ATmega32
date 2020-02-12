/*
 * Config.h
 *
 * Created: 10/17/2019 2:49:43 AM
 *  Author: H
 */ 
#ifndef CONFIG_H_
#define CONFIG_H_

#define INPUT 0
#define OUTPUT 1

typedef enum
{
	INVALID_MIN_INDEX=0X2F,
	D=0x30,
	C=0x33,
	B=0x36,
	A=0x39,
	INVALID_MAX_INDEX
}port_base;

typedef enum
{
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7
}pin_no;

/*
#define A 0x39
#define B 0x36
#define C 0x33
#define D 0x30
*/


#endif /* CONFIG_H_ */