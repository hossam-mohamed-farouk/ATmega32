/*
 * TMU.c
 *
 * Created: 10/21/2019 5:24:54 PM
 * Author : H
 */ 

#include <avr/io.h>
#include "TMU.h"
#define  F_CPU 1000000UL

void led_toggle_A(void)
{
	PORTA^=0xff;
}

void led_toggle_B(void)
{
	PORTB^=0xff;
}

void led_toggle_C(void)
{
	PORTC^=0xff;
}

void led_toggle_D(void)
{
	PORTD^=0xff;	
}

int main(void)
{
	timer_obj t_1,t_2,t_3,t_4;
	DDRA=0xff;
	DDRB=0xff;
	DDRC=0xff;
	DDRD=0xff;

	tmu_init(_1MS);
	start_timer(&t_1,250,PERIODIC,led_toggle_A);
    start_timer(&t_2,500,PERIODIC,led_toggle_B);
	start_timer(&t_3,2030,PERIODIC,led_toggle_C);		//At _1MS 2030 ~= 1_Second
	start_timer(&t_4,126000,PERIODIC,led_toggle_D);  
	
	/* Replace with your application code */
	while (1) 
    {
		tmu_dispatch();
    }
	
}

