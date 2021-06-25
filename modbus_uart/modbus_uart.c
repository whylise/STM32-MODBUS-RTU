#include "modbus_uart.h"
#include "modbus.h"


void RS485_Init()
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
    
  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_IN_FLOATING;//GPIO_Mode_AF_OD;//
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    
     RS485_RT_0; //使MAX485芯片处于接收状态
	
       //USART1_TX   PB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//GPIO_Mode_Out_PP;//GPIO_Mode_IN_FLOATING;//GPIO_Mode_AF_OD;//
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;//
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ??

   
    USART_InitStructure.USART_BaudRate = 9600;//?????9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
    USART_DeInit(USART2);
    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE); 
    USART_Cmd(USART2, ENABLE);
    USART_ClearFlag(USART2,USART_FLAG_TC );

//		GetAdd_rs485();
//		RS485_IsrInit();  //485?????
}

void RS485_byte(u8 d)  //485发送一个字节
{
  
 // RS485_RT_1;  //??
  USART_SendData(USART2, d);
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
  USART_ClearFlag(USART2,USART_FLAG_TC );
   
 // RS485_RT_0;  //?
  
}


void USART2_IRQHandler() //MODBUS字节接收中断
{
    u8 st,sbuf;
    st=USART_GetITStatus(USART2, USART_IT_RXNE);
    if(st==SET)  //
   {   		 
		  sbuf=USART2->DR;
     if( modbus.reflag==1)  //有数据包正在处理
		 {
		   return ;
		 }			 
		  modbus.rcbuf[modbus.recount++]=sbuf;
      modbus.timout=0;  
      if(modbus.recount==1)  //收到主机发来的一帧数据的第一字节
			{
			  modbus.timrun=1;  //启动定时
			}
   } 
}



