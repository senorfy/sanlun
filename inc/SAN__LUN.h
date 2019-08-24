#ifndef _SAN__LUN_c
#define _SAN__LUN_c

#include "headfile.h"

#define RANK     7

#define LEFT_PISITION_GAIN           1.0        //定义左偏差调平值
#define RIGHT_PISITION_GAIN          1.0       //定义右偏差调平值
#define POSITION_BOUND               350        //定义偏差限幅值
#define BEEP_ON         gpio_set(E5,0)
#define BEEP_OFF        gpio_set(E5,1)
#define MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#define MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )
#define ad_L1_gain    adc_get(ADC0_SE9,ADC_12bit)
#define ad_L2_gain    adc_get(ADC0_SE8,ADC_12bit)
#define ad_R1_gain    adc_get(ADC0_SE11,ADC_12bit)
#define ad_R2_gain    adc_get(ADC0_SE10,ADC_12bit)
/*****--------------定义变量分界线-------------*****/

extern int8       Inductance_Kp;
extern int8       Inductance_Kd;
extern int8       Inductance_Kp1;
extern int8       Inductance_Kd1;
extern int8       huandao_A;
extern int8       huandao_B;
extern int8       fuck;
extern int16      Adc_Value[4];                   //从左到右的电感
extern int16      Adc_Value_guiyi[4];             //从左到右的电感归一化的值
extern uint16     AD_Value_Now[4];
extern uint16     AD_Value_Last[4];
extern uint16     AD_Value_Max[4];
extern uint16     AD_Value_Min[4];


extern float     NowError;                  //这一次误差
extern float     LastError;                 //上一次电感误差
extern float     Inductance_Error;          //这次误差和上次误差的差
extern float     NowError1;                  //这一次误差
extern float     LastError1;                 //上一次电感误差
extern float     Inductance_Error1;          //这次误差和上次误差的差
extern float     Cha1_error;                //中间对电感差比和误差
extern float     Cha2_error;                //旁边对电感差比和误差
extern float     Cha_error;                 //总电感差比和误差
extern float     fuzzy_kp;                  //模糊算得的kp值
extern float     fuzzy_kd;                  //模糊算得的kd值
extern float     TURN_OUT;                  //转向环输出
extern float     CHA_P;                     //转向环P
extern float     CHA_D;                     //转向环D


/*****-------------定义函数分界线---------------*****/

void     AD_Init(void);                                     //电感初始化
void     ELSE_Init(void);                                   //其它的初始化
void     Get_AD(void);                                      //获取AD值
void     TURN_OUT_DIR(void);
void     KP_Fuzzy(float position , float position_error);   //模糊PD
void     Turn_Out_Filter(void);                               //转向控制输出滤波      
float    position_filter(float position);                     //误差值滤波
int16    PID_Dir_error(float Now_Error);                      //电感PD调节 
int16    PID_Dir_error1(float Now_Error);                      //电感PD调节 
int16    Abs(int16 value);                                    //绝对值函数
float   Float_Abs(float value);
int32    diangan_gui_yi(int32 diangan_temp);                    //电感归一化
void    AD_GET_MAX_MIN(void);
void    Reed_End(void);
void    Start_Car();


#endif