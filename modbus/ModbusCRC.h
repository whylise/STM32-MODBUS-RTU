#ifndef _MODBUS_CRC_H_
#define _MODBUS_CRC_H_
//==========================================
//#include "_TYPE.h"
//==========================================
#include "stm32f10x_conf.h"

 #define uint u16
 #define uchar u8
//------------------------------------------
//#ifdef _MODBUS_CRC_C_
//#define  global	   idata
//#else
//#define  global extern	 idata
//#endif
//------------------------------------------

 //==========================================
//#undef 	global
//==========================================
 uint crc16( uchar *puchMsg, uint usDataLen );
//==========================================
#endif

