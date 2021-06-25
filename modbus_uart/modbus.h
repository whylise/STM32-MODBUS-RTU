#ifndef _modbus_
#define _modbus_

#include "stm32f10x_conf.h"
#define RS485_RT_1 GPIO_SetBits(GPIOA, GPIO_Pin_5)     //485����״̬
#define RS485_RT_0 GPIO_ResetBits(GPIOA, GPIO_Pin_5)   //485�ý���״̬
typedef struct
{
 u8 myadd;//���豸�ĵ�ַ
 u8 rcbuf[100]; //MODBUS���ջ�����
 u16 timout;//MODbus�����ݶ���ʱ��	
 u8 recount;//MODbus�˿��Ѿ��յ������ݸ���
 u8 timrun;//MODbus��ʱ���Ƿ��ʱ�ı�־
 u8  reflag;//�յ�һ֡���ݵı�־
 u8 Sendbuf[100]; //MODbus���ͻ�����	

}MODBUS;


extern MODBUS modbus;
void Mosbus_Init(void);
void Mosbus_Event(void);
	

#endif

