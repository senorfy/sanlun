#ifndef _OLED__SYSTEM_C
#define _OLED__SYSTEM_C

#include "headfile.h"


/*****--------------定义变量分界线-------------*****/
#define    KEY_YES             0               //按键按下
#define    KEY_NO              1               //按键不按下
#define    KEY_LEFT            gpio_get(F3)    //左边
#define    KEY_RIGHT           gpio_get(A7)    //右边
#define    KEY_UP              gpio_get(F2)    //上边
#define    KEY_DOWN            gpio_get(E4)    //下边
#define    KEY_MIDDLE          gpio_get(A6)    //中间
/*---------------拨码开关宏定义------------------*/
#define    KEY_ONE             gpio_get(F1)
#define    KEY_TWO             gpio_get(F0)
#define    KEY_THREE           gpio_get(A3)
#define    KEY_FOUR            gpio_get(A2)
#define    KEY_FIVE            gpio_get(A1)
#define    KEY_SIX             gpio_get(C7)
#define    KEY_SEVEN           gpio_get(I3)
#define    KEY_EIGHT           gpio_get(G3)
extern   uint8     Key_Check;



/*****-------------定义函数分界线---------------*****/
void Work_choice(void);                            //通过拨码开关选择小车的工作状态
void boma_open();                                  //拨码开关选择显示
void WU_XIANG_Init(void);                          //五向开关初始化
void Check_Key(void);                             //五向开关按键检测
void Switch_init(void);                           //拨码开关初始化
void Oled_WrDat_1(unsigned char data);
void OLED_ShowCN(unsigned char x, unsigned char y, char str, char polarity);
void Oled_Set_Pos_1(unsigned char x, unsigned char y);
void Oled_WrCmd_1(unsigned char cmd);
void  Primary_Menu(void);  
void  Show_Menu(void);
void  Alter_Menu(void);
void Oled_Clr(void);







#endif