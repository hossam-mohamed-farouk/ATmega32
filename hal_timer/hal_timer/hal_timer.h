/*
 * hal_timer.h
 *
 * Created: 11/1/2019 7:22:06 PM
 *  Author: H
 */ 


#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_
#include "common.h"

#define MAX_NO_OF_TIMERS 2

typedef enum
{
	TIMER_0 = 0x53,  
	//TIMER_1,
	TIMER_2 = 0x45,
}genum_timer_base_t;  //control reg address

typedef enum
{
	NORMAL_MODE,
	COMPARE_MATCH_OUTPUT_MODE
	//PHASE_CORRECT_PWM,
	//FAST_PWM
}genum_timer_mode_t;

typedef enum
{
	DISABLE_TIMER0=0x00,
	NO_PRESCALER=0x01,
	CLK_DIV_8=0x02,
	CLK_DIV_64=0x03,
	CLK_DIV_256=0x04,
	CLK_DIV_1024=0x05,
	EXTERNAL_CLK_FALLING_EDGE=0x06,
	EXTERNAL_CLK_RISING_EDGE=0x07
} genum_timer_clock_select_t;

typedef enum
{
	INTERRUPT_EN,
	INTERRUPT_DIS
}interrupt_status;

typedef enum
{
	TOGGLE_OC_ON_COMPARE_MATCH = 0x10,
	CLEAR_OC_ON_COMPARE_MATCH = 0x20,
	SET_OC_ON_COMPARE_MATCH = 0x30,
}compare_match_mode_pin;

/*
typedef enum
{
	CLR_AT_CMPR_MATCH_SET_AT_BOTTOM,
	SET_AT_CMPR_MATCH_CLR_AT_BOTTOM
}fast_pwm_mode_pin;

typedef enum
{
	CLR_ON_COMPARE_MATCH_UP_COUNTING,
	CLR_ON_COMPARE_MATCH_DOWN_COUNTING
}phase_correct_pwm_mode_pin;
*/
typedef struct
{
	genum_timer_base_t t_base;
	genum_timer_mode_t t_mode;
	genum_timer_clock_select_t t_clk;
	interrupt_status int_s;
	compare_match_mode_pin cmp_pin;
	ecore_u8 cmp_value;
	//ecore_u8 timer_id;
}gcfg_hal_timer_t;

ecore_s8 hal_timer_init(gcfg_hal_timer_t * obj);
ecore_s8 hal_timer_deinit(gcfg_hal_timer_t * obj);
ecore_s8 hal_timer_read(gcfg_hal_timer_t * obj,ecore_u8 *value);
ecore_s8 hal_timer_update(gcfg_hal_timer_t * obj,ecore_u8 value);
ecore_s8 hal_timer_update_cmp(gcfg_hal_timer_t * obj,ecore_u8 value);
ecore_s8 hal_timer_is_timer_finish(gcfg_hal_timer_t * obj,bool_t *res);



#endif /* HAL_TIMER_H_ */