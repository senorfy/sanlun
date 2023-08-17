/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		KEA128_adc
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/


#include "KEA128_adc.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC初始化
//  @param      adcn_ch         选择ADC通道
//  @return     void
//  @since      v2.0
//  Sample usage:               adc_init(ADC0_SE8);
//-------------------------------------------------------------------------------------------------------------------
void adc_init(ADCn_Ch adcn_ch)
{
    SIM->SCGC |= SIM_SCGC_ADC_MASK;         //开启ADC时钟
    
    ADC->APCTL1 |= 1<<adcn_ch;              //使能ADC引脚
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC采集
//  @param      adcn_ch         选择ADC通道
//  @param      bit             选择精度ADC_8bit、ADC_10bit、ADC_12bit
//  @return     void
//  @since      v2.0
//  Sample usage:               uint16 dat = adc_once(ADC0_SE8,ADC_12bit);//采集ADC0_SE8电压，精度12位
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_once(ADCn_Ch adcn_ch, ADC_nbit bit)
{
    uint16 result;
    ADC->SC3 = (0
                | ADC_SC3_ADIV(0)           //分频系数
                | ADC_SC3_MODE(bit)         //分辨率
                | ADC_SC3_ADICLK(0)         //使用总线时钟最为ADC得时钟源
                );
        
    
    ADC->SC2 = ADC_SC2_REFSEL(0);           //基准电压选择

    ADC->SC1 = ADC_SC1_ADCH(adcn_ch);       //启动转换
    
    while(!(ADC->SC1 & ADC_SC1_COCO_MASK)); //等待转换完成
    result = ADC->R;
    return (result & ADC_R_ADR_MASK);       //返回结果    
}
  /*************************************************************************
*  函数名称：ad_ave
*  功能说明：多次采样，取平均值
*  参数说明： adcn_ch 通道号
*            bit     精度（ ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ）
*            N       均值滤波次数(范围:0~255)
*  for example       adc_once(ADC_CHANNEL_AD4,ADC_12BIT,10);
*************************************************************************/
uint32  adc_get(ADCn_Ch adcn_ch, ADC_nbit bit) //均值滤波
{
    uint32 ad_collect[5];
    for(int i=0;i<5;i++)
      ad_collect[i]=adc_once(adcn_ch, bit);
    uint32 temp=0;
        for(int i=0;i<5;i++)   
        {   
            for(int j=i+1;j<5;j++)
            {
                if(ad_collect[i]>ad_collect[j])   
                {   
                    temp=ad_collect[i];   
                    ad_collect[i]=ad_collect[j];   
                    ad_collect[j]=temp;   
                }
            }
        } 
        uint32  sum=0;
        for(int i=1;i<3;i++)
        {
            sum+=ad_collect[i];
        }
        sum/=3;
    return sum;
}
   /*************************************************************************
*  函数名称：ad_ave
*  功能说明：多次采样，取平均值
*  参数说明： adcn_ch 通道号
*            bit     精度（ ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ）
*            N       均值滤波次数(范围:0~255)
*  for example       adc_once(ADC_CHANNEL_AD4,ADC_12BIT,10);
*************************************************************************/
char coe[7] = {1,2,3,4,3,2,1};
int8 sum_coe1 = 1+2+3+4+3+2+1;

uint32  adc_get1(ADCn_Ch adcn_ch, ADC_nbit bit)//加权递推平均滤波法 
{
   int32 value_buf[7];
   int32  sum=0;
   for (int8 count=0;count<7;count++)
   {
      value_buf[count] = adc_once(adcn_ch, bit);
   }
   for (int8 count=0;count<7;count++)
   {
      sum += value_buf[count]*coe[count];
   }
      sum /= sum_coe1;
   return (5000*sum)/((1<<8)-1);   
}




//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC停止采集
//  @param      adcn_ch         选择ADC通道
//  @param      bit             选择精度ADC_8bit、ADC_10bit、ADC_12bit
//  @return     void
//  @since      v2.0
//  Sample usage:               adc_stop(adc0);
//-------------------------------------------------------------------------------------------------------------------
void adc_stop(void)
{
    ADC->SC1 = ADC_SC1_ADCH(0xFF); 
}
