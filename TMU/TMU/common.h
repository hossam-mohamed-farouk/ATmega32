/*
 * common.h
 *
 * Created: 10/21/2019 5:36:23 PM
 *  Author: H
 */ 


#ifndef COMMON_H_
#define COMMON_H_

#define NULL ((void*)0)

typedef enum
{
	E_FALSE =0,
	E_TRUE,
}tenum_bool;
typedef tenum_bool bool_t;
typedef unsigned char ecore_u8;
typedef signed char ecore_s8;
typedef unsigned short int ecore_u16;
typedef unsigned long int ecore_u32;
typedef signed long int ecore_s32;

#endif /* COMMON_H_ */