/*
 * Seven Segment Module.c
 *
 * Created: 10/18/2019 5:27:40 AM
 * Author : H
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "seven_seg.h"




int main(void)
{
	ecore_u8 h_1=0;
	ecore_u8 h_2=0;
	ecore_u8 h_3=0;
	ecore_u8 h_4=0;
	ecore_u8 h_5=0;
	ecore_u8 h_6=0;
	
	seven_segment_init(A,COMMON_CATHODE,&h_1);
	seven_segment_display(h_1,h_1);
	
	seven_segment_init(B,COMMON_CATHODE,&h_2);
	seven_segment_display(h_2,h_2);
	
	seven_segment_init(C,COMMON_CATHODE,&h_3);
	seven_segment_display(h_3,h_3);
	
	seven_segment_init(D,COMMON_ANODE,&h_4);
	seven_segment_display(h_4,h_4);
	
	seven_segment_deinit(h_3);

	seven_segment_display(h_3,9);
	/*
	seven_segment_init(C,COMMON_CATHODE,&h_3);
	seven_segment_display(h_3,h_3);
	
	seven_segment_init(B,COMMON_ANODE,&h_5);
	
	seven_segment_init(C,COMMON_CATHODE,&h_6);
    
	seven_segment_display(h_1,6);
	*/
	

	
    /* Replace with your application code */
    while (1) 
    {
		
		
		
    }
}

