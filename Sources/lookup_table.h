#ifndef _LOOKUP_TABLE_H
#define _LOOKUP_TABLE_H

extern unsigned char look1D_U8_U8(unsigned char xvalue,unsigned char xtable[],unsigned char xsize,unsigned char ztable[]);

extern unsigned short look1D_U8_U16 (unsigned char xvalue,unsigned char xtable[],unsigned char xsize,unsigned short ztable[]);
extern unsigned char look1D_U16_U8(unsigned short xvalue,unsigned short xtable[],unsigned char xsize,\
								unsigned char ztable[]);
extern unsigned short look1D_U16_U16(unsigned short xvalue,unsigned short xtable[],unsigned char xsize,\
									unsigned short ztable[]);


extern unsigned char look2D_U8_U8_U8(unsigned char xvalue,unsigned char yvalue, \
						unsigned char xtable[],unsigned char xsize,\
						unsigned char ytable[],unsigned char ysize,unsigned char ztable[]);

extern unsigned short look2D_U8_U8_U16(unsigned char xvalue,unsigned char yvalue, \
						unsigned char xtable[],unsigned char xsize,\
						unsigned char ytable[],unsigned char ysize,unsigned short ztable[]);

extern unsigned char look2D_U8_U16_U8(unsigned char xvalue, unsigned short yvalue, \
						unsigned char xtable[],unsigned char xsize,\
						unsigned short ytable[],unsigned char ysize,unsigned char ztable[]);
extern unsigned short look2D_U8_U16_U16(unsigned char xvalue,unsigned short yvalue, \
						unsigned char xtable[],unsigned char xsize,\
						unsigned short ytable[],unsigned char ysize,unsigned short ztable[]);

extern unsigned char look2D_U16_U8_U8(unsigned short xvalue,unsigned char yvalue, \
						unsigned short xtable[],unsigned char xsize,\
						unsigned char ytable[],unsigned char ysize,unsigned char ztable[]);

extern unsigned short look2D_U16_U8_U16(unsigned short xvalue,unsigned char yvalue, \
						unsigned short xtable[],unsigned char xsize,\
						unsigned char ytable[],unsigned char ysize,unsigned short ztable[]);
extern unsigned char look2D_U16_U16_U8(unsigned short xvalue,unsigned short yvalue, \
						unsigned short xtable[],unsigned char xsize,\
						unsigned short ytable[],unsigned char ysize,unsigned char ztable[]);
extern unsigned short look2D_U16_U16_U16(unsigned short xvalue,unsigned short yvalue, \
						unsigned short xtable[],unsigned char xsize,\
						unsigned short ytable[],unsigned char ysize,unsigned short ztable[]);
						
#endif