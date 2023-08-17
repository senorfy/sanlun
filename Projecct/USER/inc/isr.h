#ifndef _isr_h
#define _isr_h

#include "headfile.h"
   
/*****--------------定义变量分界线-------------*****/
   
extern  int8     AD_Time_Flag;    //定时6ms需要的变量

/*****-------------定义函数分界线---------------*****/

void PIT_CH0_IRQHandler(void);  
   
   
   
#endif
