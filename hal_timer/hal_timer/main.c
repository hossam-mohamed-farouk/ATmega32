/*
 * hal_timer.c
 *
 * Created: 11/1/2019 7:21:07 PM
 * Author : H
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#define F_CPU 1000000UL
#include "hal_timer.h"
#include "hal_system_errors.h"

#define SET_OUT_DIR(reg,pin_no) reg|=(1<<pin_no)
#define SET_INPUT_DIR(reg,pin_no) reg&=~(1<<pin_no)
#define TOGGEL_LED(reg,pin_no) reg^=(1<<pin_no)

ISR(TIMER2_OVF_vect)
{
	TOGGEL_LED(PORTC,0);
	//TOGGEL_LED(PORTB,0);
	//_delay_ms(20);
}
ISR(TIMER0_COMP_vect)
{
	TOGGEL_LED(PORTB,0);
	//TOGGEL_LED(PORTC,0);
	//_delay_ms(1);
}

int main(void)
{
	//SET_OUT_DIR(DDRB,0);
	//PORTB &= ~(1<<0);
	
	SET_OUT_DIR(DDRC,0);
	PORTC &= ~(1<<0);
	
	
	/*
	gcfg_hal_timer_t my_timer =
	{
		TIMER_2,CLK_DIV_1024,COMPARE_MATCH_OUTPUT_MODE,INTERRUPT_EN
	};
	
	gcfg_hal_timer_t my_timer_2 =
	{
		.t_base = TIMER_2,
		.t_clk = CLK_DIV_1024,
		.t_mode = NORMAL_MODE,
		.int_s = INTERRUPT_EN,
		//.cmp_pin = TOGGLE_OC_ON_COMPARE_MATCH,
		//.cmp_value = 200,
	};
	*/
	gcfg_hal_timer_t my_timer =
	{
		.t_base = TIMER_0,
		.t_clk = CLK_DIV_1024,
		.t_mode = NORMAL_MODE,
		.int_s = INTERRUPT_DIS,
		.cmp_pin = TOGGLE_OC_ON_COMPARE_MATCH,
		.cmp_value = 1,
	};
	
	
	
	//hal_timer_init(&my_timer_2);
	hal_timer_init(&my_timer);
	
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

