#include "timer.h"
void Timer2_Init()    //1ms产生1次更新事件
{
	TIM_TimeBaseInitTypeDef timer;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_DeInit(TIM2);
	timer.TIM_Period=1000-1;//   1ms
	timer.TIM_Prescaler=72-1;// 72M/72=1MHZ-->1us
	timer.TIM_ClockDivision=TIM_CKD_DIV1;
	timer.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&timer);
	
	TIM_Cmd(TIM2,ENABLE);
	
	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);

}



