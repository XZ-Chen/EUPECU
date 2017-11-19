#ifndef _TYPEDEFINE_H_
#define _TYPEDEFINE_H_



typedef char INT8;
typedef unsigned char UINT8;
typedef volatile signed char VINT8;
typedef volatile unsigned char VUINT8;

typedef signed short INT16;
typedef unsigned short UINT16;
typedef volatile signed short VINT16;
typedef volatile unsigned short VUINT16;

typedef signed long INT32;
typedef unsigned long UINT32;
typedef volatile signed long VINT32;
typedef volatile unsigned long VUINT32;
typedef float FLOAT32;
typedef double FLOAT64;

#define int8 INT8
#define int16 INT16
#define uint8 UINT8
#define uint16 UINT16
#define uint32 UINT32

#define ON  1
#define OFF 0

//enum  {ON,OFF} bool;

#endif