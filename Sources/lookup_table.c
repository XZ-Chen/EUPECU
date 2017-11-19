/****************************************************************************

			Copyright (c) GL Automotive 2009

File Name		 :	lookup_table.c

Engineer		 :	

Location		 :	R&D Dept.

Date Created	 :	

Current Revision :	Revision: 2.0 

Notes	:					

*-----------------------Revisions------------------------------------------*

Date            Engineer       Description

--------------  -------------  ---------------------------------------------
****************************************************************************/
#include "lookup_table.h"

void get_ratio_u8(unsigned char value,unsigned char table[],unsigned char *ratio,\
				unsigned char *lower,unsigned char upper)
{//table value increase by degrees
	unsigned char mid,low;
	low = 0;
	*ratio = 0;
	*lower = 0;
	if (value >= table[upper])//table value increase by degrees
	{
		*lower = upper - 1;
		*ratio = 255;
	}
	else if (value <= table[low])
	{
		*lower =0;
//		upper = 1;
		*ratio = 0;
	}
	else                
	{
		while (upper >= low)
		{
			mid = (low + upper) >> 1;
			if (value >= table[mid])
			{
				low = ++mid;
			}
			else
			{
				upper = --mid;
			}
		}
		/* upper is now less than lower and the 2 points surround
		   the actual value so return upper as lower.*/ 
		/* calculate the ratio of xvalue between upper and lower */
//		*test_ratio =((unsigned short)(((test_value - table[upper]) * 0x100)+

//				  ((table[lower]-table[upper]+1)>>1))/(table[lower] - table[upper]));
		/*  To eliminate chance of errors set lower to actual lower*/
		low = upper;
		*lower = low;
		*ratio =(unsigned char)(((unsigned short)(value - table[low]) * 0xff)/(table[low+1] - table[low]));
	}	
}




void get_ratio_s8(char value,char table[],unsigned char *ratio,\
				unsigned char *lower,unsigned char upper)
{//table value increase by degrees
	unsigned char mid,low;
	low = 0;
	*ratio = 0;
	*lower = 0;
	if (value >= table[upper])//table value increase by degrees
	{
		*lower = upper - 1;
		*ratio = 255;
	}
	else if (value <= table[low])
	{
		*lower =0;
//		upper = 1;
		*ratio = 0;
	}
	else                
	{
		while (upper >= low)
		{
			mid = (low + upper) >> 1;
			if (value >= table[mid])
			{
				low = ++mid;
			}
			else
			{
				upper = --mid;
			}
		}
		/* upper is now less than lower and the 2 points surround
		   the actual value so return upper as lower.*/ 
		/* calculate the ratio of xvalue between upper and lower */
//		*test_ratio =((unsigned short)(((test_value - table[upper]) * 0x100)+

//				  ((table[lower]-table[upper]+1)>>1))/(table[lower] - table[upper]));
		/*  To eliminate chance of errors set lower to actual lower*/
		low = upper;
		*lower = low;
		*ratio =(unsigned char)(((unsigned short)(value - table[low]) * 0x100)/(table[low+1] - table[low]));
	}	
}



void get_ratio_u16(unsigned short value,unsigned short table[],unsigned char *ratio,\
				unsigned char *lower,unsigned char upper)
{//table value increase by degrees
	unsigned char mid,low;
	low = 0;
	*ratio = 0;
	*lower = 0;
	if (value >= table[upper])//table value increase by degrees
	{
		*lower = upper - 1;
		*ratio = 255;
	}
	else if (value <= table[low])
	{
		*lower =0;
//		upper = 1;
		*ratio = 0;
	}
	else                
	{
		while (upper >= low)
		{
			mid = (low + upper) >> 1;
			if (value >= table[mid])
			{
				low = ++mid;
			}
			else
			{
				upper = --mid;
			}
		}
		/* upper is now less than lower and the 2 points surround
		   the actual value so return upper as lower.*/ 
		/* calculate the ratio of xvalue between upper and lower */
//		*test_ratio =((unsigned short)(((test_value - table[upper]) * 0x100)+

//				  ((table[lower]-table[upper]+1)>>1))/(table[lower] - table[upper]));
		/*  To eliminate chance of errors set lower to actual lower*/
		low = upper;
		*lower = low;
		*ratio =(unsigned char)(((unsigned int)(value - table[low]) * 0xff)/(table[low+1] - table[low]));
	}	
}



void get_ratio_s16(short value,short table[],unsigned char *ratio,\
				unsigned char *lower,unsigned char upper)
{//table value increase by degrees
	unsigned char mid,low;
	low = 0;
	*ratio = 0;
	*lower = 0;
	if (value >= table[upper])//table value increase by degrees
	{
		*lower = upper - 1;
		*ratio = 255;
	}
	else if (value <= table[low])
	{
		*lower =0;
//		upper = 1;
		*ratio = 0;
	}
	else                
	{
		while (upper >= low)
		{
			mid = (low + upper) >> 1;
			if (value >= table[mid])
			{
				low = ++mid;
			}
			else
			{
				upper = --mid;
			}
		}
		/* upper is now less than lower and the 2 points surround
		   the actual value so return upper as lower.*/ 
		/* calculate the ratio of xvalue between upper and lower */
//		*test_ratio =((unsigned short)(((test_value - table[upper]) * 0x100)+

//				  ((table[lower]-table[upper]+1)>>1))/(table[lower] - table[upper]));
		/*  To eliminate chance of errors set lower to actual lower*/
		low = upper;
		*lower = low;
		*ratio =(unsigned char)(((unsigned short)(value - table[low]) * 0x100)/(table[low+1] - table[low]));
	}	
}



//------------x-U8, y-   ,z-U8---------------------------

unsigned char look1D_U8_U8(unsigned char xvalue,unsigned char xtable[],unsigned char xsize,unsigned char ztable[])
{//x-eng_water_temp, type: int, size: 6
//z-eng_spd_gaol ,type: unsigned int ,size:6

	unsigned char lower, ratio;
	unsigned char temp;
	/*  get lower and ratio updates */
	get_ratio_u8(xvalue,xtable,&ratio,&lower,xsize);

	/*  take care of slope in ztable */
	{
		if (ztable[lower] > ztable[lower +1])
		{
		//	temp = ztable[lower] - mult12(ratio,(ztable[lower]-ztable[lower+1]));
			temp = ztable[lower] - (unsigned char)(((unsigned short)ratio * (ztable[lower]-ztable[lower+1]))/0xff);
		}
		else
		{
			temp = ztable[lower] +(unsigned char)(((unsigned short)ratio * (ztable[lower+1]-ztable[lower]))/0xff);
		}
	}
	return(temp);
}


//------------x-U8, y-   ,z-U16---------------------------

unsigned short look1D_U8_U16 (unsigned char xvalue,unsigned char xtable[],unsigned char xsize,\
									unsigned short ztable[])
{//x-eng_water_temp, type: int, size: 6
//z-eng_spd_gaol ,type: unsigned int ,size:6

	unsigned char lower, ratio;
	unsigned short temp;
	/*  get lower and ratio updates */
	get_ratio_u8(xvalue,xtable,&ratio,&lower,xsize);

	/*  take care of slope in ztable */
	{
		if (ztable[lower] > ztable[lower +1])
		{
		//	temp = ztable[lower] - mult12(ratio,(ztable[lower]-ztable[lower+1]));
			temp = ztable[lower] - (unsigned short)(((unsigned int)ratio * (ztable[lower]-ztable[lower+1]))/0xff);
		}
		else
		{
			temp = ztable[lower] +(unsigned short)(((unsigned int)ratio * (ztable[lower+1]-ztable[lower]))/0xff);
		}
	}
	return(temp);
}


//------------x-U16, y-   ,z-U8---------------------------

unsigned char look1D_U16_U8(unsigned short xvalue,unsigned short xtable[],unsigned char xsize,\
								unsigned char ztable[])
{
	unsigned char lower, ratio;
	unsigned char temp;
	/*  get lower and ratio updates */
	get_ratio_u16(xvalue,xtable,&ratio,&lower,xsize);

	/*  take care of slope in ztable */
	if (ztable[lower] > ztable[lower +1])
	{
	//	temp = ztable[lower] - mult12(ratio,(ztable[lower]-ztable[lower+1]));
		temp = ztable[lower] - (unsigned char)(((unsigned short)ratio * (ztable[lower]-ztable[lower+1]))/0xff);
	}
	else
	{
		temp = ztable[lower] + (unsigned char)(((unsigned short)ratio * (ztable[lower+1]-ztable[lower]))/0xff);
	}
	return (temp);
}



//------------x-U16, y-   ,z-U16---------------------------
unsigned short look1D_U16_U16(unsigned short xvalue,unsigned short xtable[],unsigned char xsize,\
									unsigned short ztable[])
{
	unsigned char lower, ratio;
	unsigned short temp;
	/*  get lower and ratio updates */
	get_ratio_u16(xvalue,xtable,&ratio,&lower,xsize);

	/*  take care of slope in ztable */
	if (ztable[lower] > ztable[lower +1])
	{
	//	temp = ztable[lower] - mult12(ratio,(ztable[lower]-ztable[lower+1]));
		temp = ztable[lower] - (unsigned short)(((unsigned int)ratio * (ztable[lower]-ztable[lower+1]))/0xff);
	}
	else
	{
		temp = ztable[lower] +(unsigned short)(((unsigned int)ratio * (ztable[lower+1]-ztable[lower]))/0xff);
	}
	return(temp);
}

//------------x-U8, y-U8   ,z-U8---------------------------


unsigned char look2D_U8_U8_U8(unsigned char xvalue,unsigned char yvalue, \
						unsigned char xtable[],unsigned char xsize,\
						unsigned char ytable[],unsigned char ysize,unsigned char ztable[])
{
	unsigned char ratiox,lowerx;
	unsigned char ratioy,lowery;
	unsigned short  temp;
	unsigned short temp_xy1,temp_xy2,temp_xy;

	get_ratio_u8(xvalue,xtable,&ratiox,&lowerx,xsize);
	get_ratio_u8(yvalue,ytable,&ratioy,&lowery,ysize);

	temp=lowery * (xsize+1) + lowerx;

	if(ztable[temp] > ztable[temp+ 1]) 
	{
		temp_xy1 = ztable[temp]-((unsigned short)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy1 = ztable[temp]+((unsigned short)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	temp=(lowery+1)*(xsize+1)+lowerx;

	if(ztable[temp] > ztable[temp+1]) 
	{
		temp_xy2 = ztable[temp]-((unsigned short)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy2 = ztable[temp]+((unsigned short)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	
	if(temp_xy1 > temp_xy2) 
	{
		temp_xy = temp_xy1-(unsigned short)ratioy*(temp_xy1-temp_xy2)/0xff;
	} 
	else 
	{
		temp_xy = temp_xy1+(unsigned short)ratioy*(temp_xy2-temp_xy1)/0xff;
	}

	return temp_xy;
}




//------------x-U8, y-U8   ,z-U16---------------------------



unsigned short look2D_U8_U8_U16(unsigned char xvalue,unsigned char yvalue, \
						unsigned char xtable[],unsigned char xsize,\
						unsigned char ytable[],unsigned char ysize,unsigned short ztable[])
{
	unsigned char ratiox,lowerx;
	unsigned char ratioy,lowery;
	unsigned short  temp;
	unsigned short temp_xy1,temp_xy2,temp_xy;

	get_ratio_u8(xvalue,xtable,&ratiox,&lowerx,xsize);
	get_ratio_u8(yvalue,ytable,&ratioy,&lowery,ysize);

	temp=lowery * (xsize+1) + lowerx;

	if(ztable[temp] > ztable[temp+ 1]) 
	{
		temp_xy1 = ztable[temp]-((unsigned int)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy1 = ztable[temp]+((unsigned int)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	temp=(lowery+1)*(xsize+1)+lowerx;

	if(ztable[temp] > ztable[temp+1]) 
	{
		temp_xy2 = ztable[temp]-((unsigned int)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy2 = ztable[temp]+((unsigned int)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	
	if(temp_xy1 > temp_xy2) 
	{
		temp_xy = temp_xy1-(unsigned int)ratioy*(temp_xy1-temp_xy2)/0xff;
	} 
	else 
	{
		temp_xy = temp_xy1+(unsigned int)ratioy*(temp_xy2-temp_xy1)/0xff;
	}

	return temp_xy;
}



//------------x-U8, y-U16   ,z-U8---------------------------

unsigned char look2D_U8_U16_U8(unsigned char xvalue,unsigned short yvalue, \
						unsigned char xtable[],unsigned char xsize,\
						unsigned short ytable[],unsigned char ysize,unsigned char ztable[])
{
	unsigned char ratiox,lowerx;
	unsigned char ratioy,lowery;
	unsigned short  temp;
	unsigned short temp_xy1,temp_xy2,temp_xy;

	get_ratio_u8(xvalue,xtable,&ratiox,&lowerx,xsize);
	get_ratio_u16(yvalue,ytable,&ratioy,&lowery,ysize);

	temp=lowery * (xsize+1) + lowerx;

	if(ztable[temp] > ztable[temp+ 1]) 
	{
		temp_xy1 = ztable[temp]-((unsigned short)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy1 = ztable[temp]+((unsigned short)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	temp=(lowery+1)*(xsize+1)+lowerx;

	if(ztable[temp] > ztable[temp+1]) 
	{
		temp_xy2 = ztable[temp]-((unsigned short)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy2 = ztable[temp]+((unsigned short)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	
	if(temp_xy1 > temp_xy2) 
	{
		temp_xy = temp_xy1-(unsigned short)ratioy*(temp_xy1-temp_xy2)/0xff;
	} 
	else 
	{
		temp_xy = temp_xy1+(unsigned short)ratioy*(temp_xy2-temp_xy1)/0xff;
	}
//	temp = known_ratio_look3d(xtable, ytable, ztable);

	return temp_xy;

}




//------------x-U8, y-U16   ,z-U16---------------------------





unsigned short look2D_U8_U16_U16(unsigned char xvalue,unsigned short yvalue, \
						unsigned char xtable[],unsigned char xsize,\
						unsigned short ytable[],unsigned char ysize,unsigned short ztable[])
{
	unsigned char ratiox,lowerx;
	unsigned char ratioy,lowery;
	unsigned short  temp;
	unsigned short temp_xy1,temp_xy2,temp_xy;

	get_ratio_u8(xvalue,xtable,&ratiox,&lowerx,xsize);
	get_ratio_u16(yvalue,ytable,&ratioy,&lowery,ysize);

	temp=lowery * (xsize+1) + lowerx;

	if(ztable[temp] > ztable[temp+ 1]) 
	{
		temp_xy1 = ztable[temp]-((unsigned int)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy1 = ztable[temp]+((unsigned int)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	temp=(lowery+1)*(xsize+1)+lowerx;

	if(ztable[temp] > ztable[temp+1]) 
	{
		temp_xy2 = ztable[temp]-((unsigned int)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy2 = ztable[temp]+((unsigned int)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	
	if(temp_xy1 > temp_xy2) 
	{
		temp_xy = temp_xy1-(unsigned int)ratioy*(temp_xy1-temp_xy2)/0xff;
	} 
	else 
	{
		temp_xy = temp_xy1+(unsigned int)ratioy*(temp_xy2-temp_xy1)/0xff;
	}

	return temp_xy;
}





//------------x-U16, y-U8   ,z-U8---------------------------




unsigned char look2D_U16_U8_U8(unsigned short xvalue,unsigned char yvalue, \
						unsigned short xtable[],unsigned char xsize,\
						unsigned char ytable[],unsigned char ysize,unsigned char ztable[])
{
	unsigned char ratiox,lowerx;
	unsigned char ratioy,lowery;
	unsigned int  temp;
	unsigned int temp_xy1,temp_xy2,temp_xy;

	get_ratio_u16(xvalue,xtable,&ratiox,&lowerx,xsize);
	get_ratio_u8(yvalue,ytable,&ratioy,&lowery,ysize);

	temp=lowery * (xsize+1) + lowerx;

	if(ztable[temp] > ztable[temp+ 1]) 
	{
		temp_xy1 = ztable[temp]-((unsigned short)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy1 = ztable[temp]+((unsigned short)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	temp=(lowery+1)*(xsize+1)+lowerx;

	if(ztable[temp] > ztable[temp+1]) 
	{
		temp_xy2 = ztable[temp]-((unsigned short)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy2 = ztable[temp]+((unsigned short)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	
	if(temp_xy1 > temp_xy2) 
	{
		temp_xy = temp_xy1-(unsigned short)ratioy*(temp_xy1-temp_xy2)/0xff;
	} 
	else 
	{
		temp_xy = temp_xy1+(unsigned short)ratioy*(temp_xy2-temp_xy1)/0xff;
	}

	return temp_xy;
}




//------------x-U16, y-U8   ,z-U16---------------------------


unsigned short look2D_U16_U8_U16(unsigned short xvalue,unsigned char yvalue, \
						unsigned short xtable[],unsigned char xsize,\
						unsigned char ytable[],unsigned char ysize,unsigned short ztable[])
{
	unsigned char ratiox,lowerx;
	unsigned char ratioy,lowery;
	unsigned short  temp;
	unsigned short temp_xy1,temp_xy2,temp_xy;

	get_ratio_u16(xvalue,xtable,&ratiox,&lowerx,xsize);
	get_ratio_u8(yvalue,ytable,&ratioy,&lowery,ysize);

	temp=lowery * (xsize+1) + lowerx;

	if(ztable[temp] > ztable[temp+ 1]) 
	{
		temp_xy1 = ztable[temp]-((unsigned int)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy1 = ztable[temp]+((unsigned int)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	temp=(lowery+1)*(xsize+1)+lowerx;

	if(ztable[temp] > ztable[temp+1]) 
	{
		temp_xy2 = ztable[temp]-((unsigned int)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy2 = ztable[temp]+((unsigned int)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	
	if(temp_xy1 > temp_xy2) 
	{
		temp_xy = temp_xy1-(unsigned int)ratioy*(temp_xy1-temp_xy2)/0xff;
	} 
	else 
	{
		temp_xy = temp_xy1+(unsigned int)ratioy*(temp_xy2-temp_xy1)/0xff;
	}

	return temp_xy;
}



//------------x-U16, y-U16   ,z-U8---------------------------


unsigned char look2D_U16_U16_U8(unsigned short xvalue,unsigned short yvalue, \
						unsigned short xtable[],unsigned char xsize,\
						unsigned short ytable[],unsigned char ysize,unsigned char ztable[])
{
	unsigned char ratiox,lowerx;
	unsigned char ratioy,lowery;
	unsigned short  temp;
	unsigned short temp_xy1,temp_xy2,temp_xy;

	get_ratio_u16(xvalue,xtable,&ratiox,&lowerx,xsize);
	get_ratio_u16(yvalue,ytable,&ratioy,&lowery,ysize);

	temp=lowery * (xsize+1) + lowerx;
	
	if(ztable[temp] > ztable[temp+ 1])
	{
		temp_xy1 = ztable[temp]-((unsigned short)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else
	{
		temp_xy1 = ztable[temp]+((unsigned short)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	temp=(lowery+1)*(xsize+1)+lowerx;

	if(ztable[temp] > ztable[temp+1]) 
	{
		temp_xy2 = ztable[temp]-((unsigned short)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	}
	else
	{
		temp_xy2 = ztable[temp]+((unsigned short)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	
	if(temp_xy1 > temp_xy2) 
	{
		temp_xy = temp_xy1-(unsigned short)ratioy*(temp_xy1-temp_xy2)/0xff;
	}
	else
	{
		temp_xy = temp_xy1+(unsigned short)ratioy*(temp_xy2-temp_xy1)/0xff;
	}
	
	return temp_xy;
}




//------------x-U16, y-U16   ,z-U16---------------------------

unsigned short look2D_U16_U16_U16(unsigned short xvalue,unsigned short yvalue, \
						unsigned short xtable[],unsigned char xsize,\
						unsigned short ytable[],unsigned char ysize,unsigned short ztable[])
{
	unsigned char ratiox,lowerx;
	unsigned char ratioy,lowery;
	unsigned short  temp;
	unsigned short temp_xy1,temp_xy2,temp_xy;

	get_ratio_u16(xvalue,xtable,&ratiox,&lowerx,xsize);
	get_ratio_u16(yvalue,ytable,&ratioy,&lowery,ysize);

	temp=lowery * (xsize+1) + lowerx;

	if(ztable[temp] > ztable[temp+ 1]) 
	{
		temp_xy1 = ztable[temp]-((unsigned int)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy1 = ztable[temp]+((unsigned int)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	temp=(lowery+1)*(xsize+1)+lowerx;

	if(ztable[temp] > ztable[temp+1]) 
	{
		temp_xy2 = ztable[temp]-((unsigned int)ratiox*(ztable[temp]-ztable[temp+1]))/0xff;
	} 
	else 
	{
		temp_xy2 = ztable[temp]+((unsigned int)ratiox*(ztable[temp+1]-ztable[temp]))/0xff;
	}
	
	if(temp_xy1 > temp_xy2) 
	{
		temp_xy = temp_xy1-(unsigned int)ratioy*(temp_xy1-temp_xy2)/0xff;
	} 
	else 
	{
		temp_xy = temp_xy1+(unsigned int)ratioy*(temp_xy2-temp_xy1)/0xff;
	}

	return temp_xy;
}



