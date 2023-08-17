 #include "Speed_Control.h"

/*-----------------------电机pwm和编码器初始化------------------------------------*/
void FTM_Init(void)     
{
    ftm_pwm_init(ftm2,ftm_ch0,15000,0);
    ftm_pwm_init(ftm2,ftm_ch1,15000,0);
    ftm_pwm_init(ftm2,ftm_ch2,15000,0);
    ftm_pwm_init(ftm2,ftm_ch3,15000,0);
    ftm_count_init(ftm0);
    ftm_count_init(ftm1);
    gpio_init(C5,GPI,0);    //用于判断方向                  C5接编码器DIR
    port_pull(C5); 
    gpio_init(H5,GPI,0);    //用于判断方向                  H5接编码器DIR
    port_pull(H5);
}
/*--------------------- 左边编码器采集-----------------------------------*/
int16 speed_collect_L()     
{
  int16 bianmaqi_L=0;
  bianmaqi_L=ftm_count_get(ftm0);
  ftm_count_clean(ftm0);
  temp1_Dir=gpio_get(C5);
  if(temp1_Dir==1)  
    return  bianmaqi_L;
  else
    return (-1)*bianmaqi_L;
}
/*---------------------右边编码器采集------------------------------------*/
int16 speed_collect_R()        
{
  int16 bianmaqi_R=0;
  bianmaqi_R=ftm_count_get(ftm1);
  ftm_count_clean(ftm1);
  temp2_Dir=gpio_get(H5);
  if(temp2_Dir==0)
     return   bianmaqi_R;
  else
     return  (-1)*bianmaqi_R;
}
/*----------------------获取编码器的速度-------------------------------------*/
      void   get_speed()  
{
      static int16   SPEED_ERROR[4]={0};
      ActualSpeed_L = speed_collect_L();
      ActualSpeed_R = speed_collect_R();
      Car_Actual_Speed=(int)((ActualSpeed_L+ActualSpeed_R)*0.5);//算出两个轮的平均速度
      SPEED_ERROR[3]=SPEED_ERROR[2];
      SPEED_ERROR[2]=SPEED_ERROR[1];
      SPEED_ERROR[1]=SPEED_ERROR[0];
      SPEED_ERROR[0]=Car_Actual_Speed;
      Car_Actual_Speed=(int)(SPEED_ERROR[0]*0.4+SPEED_ERROR[1]*0.3+SPEED_ERROR[2]*0.2+SPEED_ERROR[3]*0.1);     
}
/*------------------------速度环控制变量-----------------------------------*/
  float  F_P,F_I;
void Speed_Control(void)  
{       
  //static float PreError[20]={0};
//  float  SpeedError;
//  float  F_P,F_I;
   SpeedError=(Car_Set_Speed - Car_Actual_Speed)*1.0; 
   F_P=SpeedError*PID_SPEED_P;
   F_I=SpeedError*PID_SPEED_I;
   SpeedControlIntegral+=F_I; 
   if(SpeedControlIntegral>360)
     SpeedControlIntegral=360;
   if(SpeedControlIntegral<320)
     SpeedControlIntegral=320;
   if(Speed_Flag==4)
     SpeedControlIntegral=0;
  //求出最近20个偏差的总和作为积分项
  //float SpeedControlIntegral=0;
//   for(int8 i=0;i<19;i++)
//   {
//     PreError[i]=PreError[i+1]; 
//     SpeedControlIntegral+=PreError[i];
//   }
//    PreError[19]=SpeedError;
//    SpeedControlIntegral+=PreError[19];
   
  //速度更新
  SpeedControlOutOld=SpeedControlOutNew;
  SpeedControlOutNew = F_P + SpeedControlIntegral;   //PI控制
  Speed_Error=SpeedControlOutNew-SpeedControlOutOld;
  
  //SpeedControlOutNew = SpeedControlOutOld*0.9 + SpeedControlOutNew*0.1;
}
/*-------------------------速度环的控制----------------------------------*/
void  Speed_Control_out(void) 
{
  SPEED_OUT=((Speed_Error * (SpeedCount+1)/Speed_Filter_Times)+SpeedControlOutOld);
  if(SPEED_OUT<(-900))
    SPEED_OUT=(-900);
  if(SPEED_OUT>900)
    SPEED_OUT=900;
}
/*-------------------------速度大小选择----------------------------------*/
void  Speed_chioce(void)
{
    switch(Speed_Flag)
    {
      case 0:
        if((fuck==2)&&(KEY_THREE==0))
        Car_Set_Speed=Po_Dao_Speed;
        else
        Car_Set_Speed=Car_Set_Speed_1;  //普通赛道
        BEEP_OFF;
        break;
      case 1:
        Car_Set_Speed=90;  //进环
        BEEP_ON;
        break;
      case 2:
        Car_Set_Speed=115;  //环中
        BEEP_OFF;
        break;
      case 3:
        Car_Set_Speed=100;  //出环
        BEEP_OFF;
        break;
      case 4:
        Car_Set_Speed=0;  //停车速度
        BEEP_OFF;
        break;  
      default :            //其他
        break;
    } 
}

/*--------------------------电机输出控制---------------------------------*/
void motor_shuchu(void)
{
     static    int16  motor_L_out1=0;
     static    int16  motor_R_out1=0;
     motor_L_out1=motor_L_out;
     motor_R_out1=motor_R_out;
    if(WorkMode==1)
     {
       motor_L_out=(int)(SPEED_OUT);
       motor_R_out=(int)(SPEED_OUT);
     }
     else if(WorkMode==2)
     {
       motor_L_out=(int)(-TURN_OUT);
       motor_R_out=(int)TURN_OUT;
     }
     else if(WorkMode==3)
     {
      motor_L_out=(int)((SPEED_OUT)-TURN_OUT);
      motor_R_out=(int)((SPEED_OUT)+TURN_OUT); 
     }
     if(Abs(motor_L_out-motor_L_out1)<Limit_Speed)
     {
       ;
     }
    else
    {
      if(motor_L_out>motor_L_out1)
        motor_L_out=motor_L_out1+Limit_Speed;
      if(motor_L_out<motor_L_out1)
        motor_L_out=motor_L_out1-Limit_Speed;
    }
    if(Abs(motor_R_out-motor_R_out1)<Limit_Speed)
     {
       ;
     }
    else
    {
      if(motor_R_out>motor_R_out1)
        motor_R_out=motor_R_out1+Limit_Speed;
      if(motor_R_out<motor_R_out1)
        motor_R_out=motor_R_out1-Limit_Speed;
    }
       if(motor_L_out>960)
        motor_L_out=960;
      else if(motor_L_out<-960)
        motor_L_out=(-960);
      if(motor_R_out>960)
        motor_R_out=960;
      else if(motor_R_out<-960)
        motor_R_out=(-960);  
        if(motor_L_out>=0)
        {
          ftm_pwm_duty(ftm2,ftm_ch1,motor_L_out+30);
          ftm_pwm_duty(ftm2,ftm_ch0,0);
        }
        else
        {
         ftm_pwm_duty(ftm2,ftm_ch1,0);
         ftm_pwm_duty(ftm2,ftm_ch0,Abs(motor_L_out)+30); 
        }
       if(motor_R_out>=0)
        {
          ftm_pwm_duty(ftm2,ftm_ch3,0);
          ftm_pwm_duty(ftm2,ftm_ch2,motor_R_out+30);
        }
        else 
        {
          ftm_pwm_duty(ftm2,ftm_ch3,Abs(motor_R_out)+30);
          ftm_pwm_duty(ftm2,ftm_ch2,0); 
        }  
}
/*-----------------------------------------------------------*/