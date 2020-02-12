/*
 * watch_app.c
 *
 * Created: 10/30/2019 5:45:45 AM
 * Author : H
 */ 

#include <avr/io.h>
#include "seven_seg.h"
#include "TMU.h"
//Define numbers to display
ecore_u8 sec_0=0;
ecore_u8 sec_1=0;
ecore_u8 min_0=0;
ecore_u8 min_1=0;
//TMU call back function
void sec_inc(void)
{
	sec_0 ++;
}

int main(void)
{
	//Define seven_seg handlers
	ecore_u8 seven_seg_sec_0,seven_seg_sec_1,seven_seg_min_0,seven_seg_min_1;
	//Define timer object
	timer_obj t_1;
	//Init LCDs
	seven_segment_init(A,COMMON_CATHODE,&seven_seg_sec_0);
	seven_segment_init(B,COMMON_CATHODE,&seven_seg_sec_1);
	seven_segment_init(C,COMMON_CATHODE,&seven_seg_min_0);
	seven_segment_init(D,COMMON_CATHODE,&seven_seg_min_1);
	//Init and start the TMU
	tmu_init(_1MS);
	start_timer(&t_1,2850,PERIODIC,sec_inc);
	
   
    while (1) 
    {
		seven_segment_display(seven_seg_sec_0,sec_0);
		seven_segment_display(seven_seg_sec_1,sec_1);
		seven_segment_display(seven_seg_min_0,min_0);
		seven_segment_display(seven_seg_min_1,min_1);
		
		if(sec_0 > 9)
		{
			sec_0 = 0;
			sec_1 ++;
		}
		if ((sec_1 == 6) && (sec_0 == 0))
		{
			sec_1 = 0;
			min_0 ++;
		}
		if(min_0 > 9)
		{
			min_0 = 0;
			min_1 ++;
		}
		if ((min_1 == 6) && (min_0 == 0))
		{
			min_1 =0;
		}
		tmu_dispatch();
    }
}

