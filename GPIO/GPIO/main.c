/*
 * GPIO.c
 *
 * Created: 10/17/2019 2:47:52 AM
 * Author : H
 */ 

#include <avr/io.h>
#include "GPIO.h"


int main(void)
{
	
	port_direction(A,INPUT);
	pull_up_port(A);
	port_direction(B,OUTPUT);
	ecore_u8 v_1=0;
	ecore_u8 v_2=0;
	ecore_u8 v_3=0;
	ecore_u8 v_4=0;
	ecore_u8 v_5=0;
	
	//pin_direction(A,PIN_0,OUTPUT);
	//pin_direction(A,PIN_7,INPUT);
	//pull_up(A,PIN_7);
   /*  Replace with your application code */
    while (1) 
    {
		pin_read(A,PIN_0,&v_1);
		pin_read(A,PIN_1,&v_2);
		pin_read(A,PIN_2,&v_3);
		pin_read(A,PIN_3,&v_4);
		pin_read(A,PIN_4,&v_5);
		
		if(v_1==0)
		{
			pin_write(B,PIN_0,1);
		}
		else
		{
			pin_write(B,PIN_0,0);
		}
		if(v_2==0)
		{
			pin_write(B,PIN_1,1);
		}
		else
		{
			pin_write(B,PIN_1,0);
		}
		if(v_3==0)
		{
			pin_write(B,PIN_2,1);
		}
		else
		{
			pin_write(B,PIN_2,0);
		}
		if(v_4==0)
		{
			pin_write(B,PIN_3,1);
		}
		else
		{
			pin_write(B,PIN_3,0);
		}
		if(v_5==0)
		{
			pin_write(B,PIN_4,1);
		}
		else
		{
			pin_write(B,PIN_4,0);
		}
		
    }
	
}
		


