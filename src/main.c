#include "headfile.h"
   
/*-----------------------------------
          *电感采集变量*
-----------------------------------*/
int16  Adc_Value[4];                   //从左到右的电感
int16  Adc_Value_guiyi[4];             //从左到右的电感归一化的值
/*-------------------------------------
          *电感采集最大值最小值*
---------------------------------------*/
uint16   AD_Value_Now[4] ={0,0,0,0};
uint16   AD_Value_Last[4]={0,0,0,0};
uint16   AD_Value_Max[4] ={0,0,0,0};
uint16   AD_Value_Min[4] ={10000,10000,10000,10000};
/*------------------------------------
         *电感PD控制变量*
--------------------------------------*/
float     Cha1_error;                  //中间对电感差比和误差
float     Cha2_error;                  //旁边对电感差比和误差
float     Cha_error;                   //总电感差比和误差
float     NowError=0.0;                //这一次误差
float     LastError=0.0;               //上一次误差
float     Inductance_Error;            //这次误差和上次误差的差
float     NowError1=0.0;                //这一次误差
float     LastError1=0.0;               //上一次误差
float     Inductance_Error1;            //这次误差和上次误差的差
float     fuzzy_kp = 0.0;              //模糊算得的kp值
float     fuzzy_kd = 0.0;              //模糊算得的kd值
float     CHA_P;                       //转向环P
float     CHA_D;                       //转向环D
/*-------------------------------------
        *转向速度控制变量*
---------------------------------------*/
int16 sudu_turn_L=0;              //左轮转向速度
int16 sudu_turn_R=0;              //右轮转向速度
/*--------------------------------------
        *编码器控制变量*
----------------------------------------*/
int16 ActualSpeed_L;                //左轮脉冲数
int16 ActualSpeed_R;                //右轮脉冲数
int8  temp1_Dir;                    //左轮方向  1正0反
int8  temp2_Dir;                    //右轮方向  0正1反
/*---------------------------------------
        *电机输出控制变量*
----------------------------------------*/
//速度环
float   SpeedControlOutOld=0;          //旧的速度
float   SpeedControlOutNew=0;          //新的速度
float   Speed_Error;                   //新的速度与旧的速度差
float   SPEED_OUT=0;                     //速度环输出
float   TURN_OUT;                      //转向环输出
float   PID_SPEED_P=10;                //速度环P
float   PID_SPEED_I=0.1;             //速度环I
float   SpeedControlIntegral=0;
float   SpeedError;
int8     SpeedCount=0;                 //速度一点一点给的变量
int16    motor_L_out;                  //左边电机输出
int16    motor_R_out;                  //右边电机输出
int16    Car_Actual_Speed;             //车的真实速度
int16    Car_Set_Speed;               //车的理想速度
int16    Car_Set_Speed_1=95;             //车的理想速度
uint8    Limit_Speed=180;
uint8    Po_Dao_Speed=110;
/*--------------------------------------
        *小车的状态*
---------------------------------------*/
uint8    WorkMode;                   //判断小车工作状态
/*--------------------------------------
        *定时器变换需要的变量*
---------------------------------------*/
int8     AD_Time_Flag=0;            //AD采集时间控制的标志位
int8     Speed_Flag=0;               //速度选择标志位
int8     huandao_A=0;               //判断环岛的条件
int8     huandao_B=0;               //出环岛的条件
int8     fuck=0;

uint8    Key_Check=0;               //检测五向开关按键
/*--------------------------------------
        *模糊放大倍数*
---------------------------------------*/
int8    Inductance_Kp=20;//41
int8    Inductance_Kd=19;//45
int8    Inductance_Kp1=41;
int8    Inductance_Kd1=10;

/*-------------------一条华丽的分割线--------------------------*/

   int main(void)
{
    get_clk();                      //获取时钟频率 必须执行
    AD_Init();                      //电感初始化
    ELSE_Init();                    //其它的初始化
    FTM_Init();                     //电机pwm和编码器初始化
    Switch_init();                 //拨码开关初始化 
    Work_choice();                 //通过拨码开关选择小车的工作状态
    WU_XIANG_Init();               //五向开关初始化
    AD_GET_MAX_MIN();              //获得赛道的最大最小值
    if(KEY_TWO==0)                 //拨码复位发车
    Start_Car();
    Primary_Menu();
    while(1)
    {
      //boma_open();
     //  Uart1_Send_AF(Cha_error,Inductance_Error,CHA_P,CHA_D,0,0,0,0);
      // Uart1_Send_AF(ActualSpeed_L,ActualSpeed_R,Car_Actual_Speed,SpeedControlIntegral,motor_L_out,SpeedError,Car_Set_Speed,0);
  //    Uart1_Send_AF(Adc_Value_guiyi[0],Adc_Value_guiyi[1],Adc_Value_guiyi[2],Adc_Value_guiyi[3],0,0,0,0);
       Check_Key();
       if(Key_Check!=0)
       Primary_Menu(); 
    }
}
