/*
 * TMU.h
 *
 * Created: 10/21/2019 5:36:38 PM
 *  Author: H
 */ 
//  NOTE:->  Timer_0 Reserved For this module

#ifndef TMU_H_
#define TMU_H_
#include "common.h"

typedef enum
{
	PERIODIC,
	ONE_SHOT
}timer_type;

typedef enum
{
	_1MS,
	_8MS,
	_64MS,
	_256MS,
	_1024MS
} timer_resolution;

typedef struct
{
	ecore_u8 timer_id;
	void(*o_cb_func)(void);
	timer_type o_t_type;
	ecore_u32 o_time;	
	ecore_s32 remining_time;
	//ecore_u16 expected_counter;
}timer_obj;


bool_t tmu_init(timer_resolution tmu_resolution);
bool_t start_timer(timer_obj* t_obj,ecore_u32 time,timer_type t_type,void(*cb_func)(void));
bool_t stop_timer(timer_obj* t_obj);
bool_t tmu_dispatch(void);
bool_t tmu_deinit(void);

#endif /* TMU_H_ */