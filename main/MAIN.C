

#include "timer.h"
#include "modbus_uart.h"
#include "modbus.h"

u16 Reg[]={0x0000,   //本设备寄存器中的值
           0x0001,
           0x0002,
           0x0003,
           0x0004,
           0x0005,
           0x0006,
           0x0007,
           0x0008,
           0x0009,
           0x000A,	
          };	


void delay(u32 x)
{

 while(x--);
}
void Isr_Init()
{
	NVIC_InitTypeDef  isr;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //  a bbb 
	
	isr.NVIC_IRQChannel=TIM2_IRQn;
	isr.NVIC_IRQChannelCmd=ENABLE;
	isr.NVIC_IRQChannelPreemptionPriority=1;
	isr.NVIC_IRQChannelSubPriority=2;	
	NVIC_Init(&isr);   //	
	
	isr.NVIC_IRQChannel=USART2_IRQn;
	isr.NVIC_IRQChannelCmd=ENABLE;
	isr.NVIC_IRQChannelPreemptionPriority=1;
	isr.NVIC_IRQChannelSubPriority=0;	
	NVIC_Init(&isr);   //
	
		
}



void TIM2_IRQHandler()//定时器2的中断服务子函数  1ms一次中断
{
  u8 st;
  st= TIM_GetFlagStatus(TIM2, TIM_FLAG_Update);	
	if(st==SET)
	{
	  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		if(modbus.timrun!=0)
		{
		  modbus.timout++; 
		  if(modbus.timout>=8)  //间隔时间达到了时间
			{
				modbus.timrun=0;//关闭定时器--停止定时
				modbus.reflag=1;  //收到一帧数据
			}
		}  		
	}	
}



int main()
{
  Timer2_Init();  
  Mosbus_Init();
	
	
	Isr_Init();
  while(1)
	{
		Mosbus_Event();  //处理MODbus数据

	}
}

