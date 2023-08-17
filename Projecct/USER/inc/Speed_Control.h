#ifndef _SPEED__CONCTOL_C
#define _SPEED__CONCTOL_C

#include "headfile.h"
 

#define Speed_Filter_Times   6                           //把速度分为四份，逐份加速度

/*----------------定义变量分界线--------------------*/
extern   float  SpeedError;
extern   int8     Speed_Flag;                   //速度选择标志位
extern   int8     temp1_Dir;                   //左轮方向  1正0反
extern   int8     temp2_Dir;                   //右轮方向  0正1反
extern   int16    Car_Actual_Speed;            //车的真实速度
extern   int16    Car_Set_Speed;               //车的理想速度
extern   int16    Car_Set_Speed_1;               //车的理想速度
extern   int16    motor_L_out;                 //左边电机输出
extern   int16    motor_R_out;                 //右边电机输出
extern   uint8    WorkMode;                    //判断小车工作状态
extern   int8     SpeedCount;                  //速度一点一点给的变
extern   int16    ActualSpeed_L;               //左轮脉冲数
extern   int16    ActualSpeed_R;               //右轮脉冲数
extern   float   SPEED_OUT;                   //速度环输出
extern   float   PID_SPEED_P;                  //速度环P
extern   float   PID_SPEED_I;                  //速度环I
extern   float   SpeedControlOutOld;          //旧的速度
extern   float   SpeedControlOutNew;          //新的速度
extern   float   Speed_Error;                 //新的速度与旧的速度差
extern   float   SpeedControlIntegral;        //速度环积分
extern   uint8    Limit_Speed;                 //速度变化范围
extern   uint8    Po_Dao_Speed;                

/*-----------------定义函数分界线-------------------*/
int16       speed_collect_L();                                //左边编码器读数和判方向
int16       speed_collect_R();                                //右边编码器读数和判方向
void        get_speed();                                     //获取编码器的速度和算出中间速度
void        Speed_Control_out(void);                         //速度环的控制
void        motor_shuchu(void);                              //电机输出控制
void        Speed_Control(void);                              //速度环控制变量
void        FTM_Init(void);                                    //电机pwm和编码器初始化
void        Speed_chioce(void);

#endif