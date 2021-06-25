#ifndef _modbusuart_
#define _modbusuart_


#include "stm32f10x_conf.h"
void RS485_Init(void);
void RS485_byte(u8 d);  //485发送一个字节

#endif

