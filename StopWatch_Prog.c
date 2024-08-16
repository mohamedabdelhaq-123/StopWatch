#include "MemMap.h"
#include "StdTypes.h"
#include "DIO_Int.h"
#include "SEVEN_SEG_Int.h"
#include "SEVEN_SEG_Cfg.h"

void StopWatch(void)
{
	//ddra=0xff;
	DIO_WritePort(segmentport1,0xff);
	ddrb=0;
	portb=0xff;
	ddrc=0xff;
	ddrd=0xff;
	char x=30,c=0;
	char flag=1,flag1=0,flag2=0;
	while (1)
	{
		while(flag2==0)
		{
			while(get_bit(pinb,6))
			{
				segment_display_MLX(0);
				if(!get_bit(pinb,6))
				{
					flag2^=1;
					while(!get_bit(pinb,6));
					break;
				}
			}

			while(flag2==1)
			{
				segment_display_MLX(c);
				if(!get_bit(pinb,4))
				{
					c=c+10;
					while(!get_bit(pinb,4));
				}
				if(!get_bit(pinb,5))  //reset
				{
					c=c+1;
					while(!get_bit(pinb,5));
				}
				if(!get_bit(pinb,6))
				{
					break;
				}
			}
		}
		while(flag2==1)
		{
			while(flag==0) //reset  & start at 30
			{
				segment_display_MLX(0);
				if(!get_bit(pinb,4))
				{
					flag^=1;
					c=30;
					while(!get_bit(pinb,4));
				}
			}
			while(flag1==1)   // pause=1 or resume=0
			{
				segment_display_MLX(c);
				if(!get_bit(pinb,4))
				{
					flag1^=1;
					while(!get_bit(pinb,4));
				}
			}
			for (x=0;x<50;x++)   // loop takes 1000ms
			{
				if(!get_bit(pinb,5))  //reset
				{
					flag=0;
					while(!get_bit(pinb,5));
					break;
				}
				if(!get_bit(pinb,4))  // pause or resume
				{
					flag1^=1;
					while(!get_bit(pinb,4));
					break;
				}
				segment_display_MLX(c);
			}
			if(c==0)
			{
				segment_display_MLX(0);
				set_bit(portc,5); //buzzer
				flag1=1;
			}
			c--;
		}
	}
}

