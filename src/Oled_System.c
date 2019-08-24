#include "Oled_System.h"

/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    首页中文字符16位进制
-----------------------------------------------------------*/
const char China[][32] = 
{

{0x40,0x44,0x24,0xA4,0x94,0x8C,0x84,0xFF,0x84,0x8C,0x94,0xA4,0x24,0x44,0x40,0x00,
 0x40,0x40,0x40,0x5F,0x4A,0x4A,0x4A,0x4A,0x4A,0x4A,0x4A,0x5F,0x40,0x40,0x40,0x00},/*"查",0*/

{0x00,0x20,0x20,0xA8,0x6C,0x2A,0x39,0x28,0xA8,0x2A,0x6C,0xA8,0x20,0x20,0x00,0x00,
 0x02,0x82,0x81,0x90,0x92,0x4A,0x49,0x45,0x24,0x22,0x10,0x08,0x01,0x02,0x02,0x00},/*"参",1*/
 
{0x40,0x20,0xF8,0x07,0xF0,0xA0,0x90,0x4C,0x57,0x24,0xA4,0x54,0x4C,0x80,0x80,0x00,
 0x00,0x00,0xFF,0x00,0x1F,0x80,0x92,0x52,0x49,0x29,0x24,0x12,0x08,0x00,0x00,0x00},/*"修",0*/

{0x04,0x84,0x84,0x84,0x84,0xFC,0x40,0x30,0xCC,0x0B,0x08,0x08,0xF8,0x08,0x08,0x00,
 0x00,0x7F,0x20,0x10,0x10,0x08,0x80,0x40,0x21,0x16,0x08,0x16,0x21,0x40,0x80,0x00},/*"改",1*/
 
{0x00,0x00,0x00,0xFC,0x44,0x44,0x44,0x45,0x46,0x44,0x44,0x44,0x44,0x7C,0x00,0x00,
 0x40,0x20,0x18,0x07,0x00,0xFC,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFC,0x00,0x00},/*"启",0*/

{0x40,0x44,0xC4,0x44,0x44,0x44,0x40,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
 0x10,0x3C,0x13,0x10,0x14,0xB8,0x40,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00},/*"动",1*/
};
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    OLED写数据
-----------------------------------------------------------*/
void Oled_WrDat_1(unsigned char data)
{
    unsigned char i=8;

    OLED_DC(1);
    OLED_SCL(0);
    while(i--)
    {
        if(data&0x80)
            OLED_SDA(1);
        else
            OLED_SDA(0);
        
        OLED_SCL(1);           
        OLED_SCL(0);   
        data<<=1;    
    }	
}
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    OLED设立坐标
-----------------------------------------------------------*/
void Oled_Set_Pos_1(unsigned char x, unsigned char y)
{
    Oled_WrCmd_1(0xb0+y);
    Oled_WrCmd_1(((x&0xf0)>>4)|0x10);
    Oled_WrCmd_1(x&0x0f);
} 
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    OLED写命令
-----------------------------------------------------------*/
void Oled_WrCmd_1(unsigned char cmd)
{
    unsigned char i=8;

    OLED_DC(0);
    //asm("nop");
    OLED_SCL(0);
    while(i--)
    {
        if(cmd&0x80)
            OLED_SDA(1);
        else
            OLED_SDA(0);
        
        OLED_SCL(1);
	//asm("nop");             
        OLED_SCL(0);
        cmd<<=1;
    }
}
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    OLED全屏清除
-----------------------------------------------------------*/
void Oled_Clr(void)
{
    unsigned char y,x;

    for(y=0;y<8;y++)
    {
        Oled_WrCmd_1(0xb0+y);
        Oled_WrCmd_1(0x01);
        Oled_WrCmd_1(0x10);
        for(x=0;x<128;x++)
            Oled_WrDat_1(0x00);
    }
}
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    OLED显示中文
-----------------------------------------------------------*/
void OLED_ShowCN(unsigned char x, unsigned char y, char str, char polarity)
{
    unsigned char i = 0;
    Oled_Set_Pos_1(x,y);
    if(polarity == 1)
    {
        for(i=0;i<16;i++)
            Oled_WrDat_1(China[str][i]);
        Oled_Set_Pos_1(x,y+1);
        for(i=16;i<32;i++)
            Oled_WrDat_1(China[str][i]);
    }
    else
    {
        for(i=0;i<16;i++)
            Oled_WrDat_1(~China[str][i]);
        Oled_Set_Pos_1(x,y+1);
        for(i=16;i<32;i++)
            Oled_WrDat_1(~China[str][i]);
    }
}
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    拨码开关选择小车的工作状态
-----------------------------------------------------------*/
void Work_choice(void)   
{
    if(KEY_SEVEN==0&&KEY_EIGHT==1)     //用第七和第八个拨码开关
      WorkMode=1;
    if(KEY_SEVEN==1&&KEY_EIGHT==0)
      WorkMode=2;
    if(KEY_SEVEN==0&&KEY_EIGHT==0||KEY_SEVEN==1&&KEY_EIGHT==1)
      WorkMode=3;
}
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    拨码开关选择显示
-----------------------------------------------------------*/
void boma_open()  
{
}
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    五向开关初始化
-----------------------------------------------------------*/
void WU_XIANG_Init(void)
{
    gpio_init(E4,GPI,1);    //下
    port_pull(E4);
    gpio_init(A7,GPI,1);    //右
    port_pull(A7);
    gpio_init(F2,GPI,1);    //上
    port_pull(F2);
    gpio_init(A6,GPI,1);    //中
    port_pull(A6);
    gpio_init(F3,GPI,1);    //左
    port_pull(F3);
}
/*-----------------------------------------------------------*/
void Switch_init(void)    //拨码开关初始化
{
    gpio_init(F1,GPI,1);    //拨码第一个开关
    port_pull(F1);
    gpio_init(F0,GPI,1);    //拨码第二个开关
    port_pull(F0);
    gpio_init(A3,GPI,1);    //拨码第三个开关
    port_pull(A3);
    gpio_init(A2,GPI,1);    //拨码第四个开关
    port_pull(A2);
    gpio_init(A1,GPI,1);    //拨码第五个开关
    port_pull(A1);
    gpio_init(C7,GPI,1);    //拨码第六个开关
    port_pull(C7);
    gpio_init(I3,GPI,1);    //拨码第七个开关
    port_pull(I3);
    gpio_init(G3,GPI,1);    //拨码第八个开关
    port_pull(G3);    
}
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    五向开关检测
-----------------------------------------------------------*/
void Check_Key(void)            
{
    if(KEY_LEFT == KEY_YES)          //左
    {    
      Key_Check = 1;
      systick_delay_ms(200);
    }
    else if(KEY_RIGHT == KEY_YES)          //右
    {
      Key_Check = 2;
      systick_delay_ms(200);
    }
    else if(KEY_UP == KEY_YES)    //上
    {
        Key_Check = 3;
        systick_delay_ms(200);
    }
    else if(KEY_DOWN == KEY_YES)    //下
    {
        Key_Check = 4;
        systick_delay_ms(200);
    }
    else if(KEY_MIDDLE == KEY_YES)    //中键
    {
      Key_Check = 5;
      systick_delay_ms(200);
    }
    else
      Key_Check = 0;
}
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    首页显示
-----------------------------------------------------------*/
void  Primary_Menu(void)  
{
   static int choice = 2;
    if(Key_Check==1)    //左移
    {
      choice--;
    if(choice<0)
      choice = 0;
    }
    if(Key_Check==2)    //右移
    {
      choice++;
    if(choice>1)
      choice = 1;
    }
    if(Key_Check==3)    //上按
      choice = 2;
    if(Key_Check==4)    //下按
      choice = 0;
    for(int i=0;i<3;i++)
      {
        if(i!=2)
        {
        OLED_ShowCN(20+60*i, 5, 2*i,choice!=i);
        OLED_ShowCN(20+60*i+16, 5, 2*i+1,choice!=i);
        }
        if(i==2)
        {
          OLED_ShowCN(52, 1, 2*i,choice!=i);
          OLED_ShowCN(68, 1, 2*i+1,choice!=i);
        }
      } 
    if(Key_Check==5)
    {
      switch(choice)
         {
         case 0:
           Show_Menu();
        	break;
         case 1:
           Alter_Menu();
                break;
         case 2:
           Start_Car();
                break;
         default:
                break;
         }
    }      
}
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    显示参数（俊源）
-----------------------------------------------------------*/
void  Show_Menu(void)
{
  static int flag = 0;
  Oled_Clr();
  while(1)
  {
    if(flag==0)
    {
       OLED_P8x16Str(0,0,"L2:  ");
       OLED_Print_Num(23,0,Adc_Value[0]);
       OLED_P8x16Str(0,2,"L1:  ");
       OLED_Print_Num(23,2,Adc_Value[1]);     
       OLED_P8x16Str(0,4,"R1:  ");
       OLED_Print_Num(23,4,Adc_Value[2]);
       OLED_P8x16Str(0,6,"R2:  ");
       OLED_Print_Num(23,6,Adc_Value[3]); 
    }
    if(flag==1)
    {
       OLED_P8x16Str(0,0,"L2_G:");
       OLED_Print_Num(40,0,Adc_Value_guiyi[0]);
       OLED_P8x16Str(0,2,"L1_G:");
       OLED_Print_Num(40,2,Adc_Value_guiyi[1]);     
       OLED_P8x16Str(0,4,"R1_G:");
       OLED_Print_Num(40,4,Adc_Value_guiyi[2]);
       OLED_P8x16Str(0,6,"R2_G:");
       OLED_Print_Num(40,6,Adc_Value_guiyi[3]);
    }
    if(flag==2)
    {
      OLED_P8x16Str(0,0,"CHA1 ");
      OLED_P8x16Str(0,2,"CHA2 ");
      OLED_P8x16Str(0,4,"TURN ");
      OLED_Print_Num1(40,0,(int16)Cha1_error);
      OLED_Print_Num1(40,2,(int16)Cha2_error);
      OLED_Print_Num1(40,4,(int16)TURN_OUT);
    }
    if(flag==3)
    {
       OLED_P8x16Str(0,0,"MaxL2");
       OLED_Print_Num1(40,0,AD_Value_Max[0]);
       OLED_P8x16Str(0,2,"MaxL1");
       OLED_Print_Num1(40,2,AD_Value_Max[1]);
       OLED_P8x16Str(0,4,"MaxR1");
       OLED_Print_Num1(40,4,AD_Value_Max[2]); 
       OLED_P8x16Str(0,6,"MaxR2");
       OLED_Print_Num1(40,6,AD_Value_Max[3]);
    }
    if(flag==4)
    {
      OLED_P8x16Str(0,0,"SP_L");
      OLED_P8x16Str(0,2,"SP_R");
      OLED_P8x16Str(0,4,"L__R");
      OLED_Print_Num1(40,0,ActualSpeed_L);
      OLED_Print_Num1(40,2,ActualSpeed_R);
      OLED_Print_Num1(40,4,Car_Actual_Speed);
    }
    Check_Key();
    if(Key_Check==1)
    {
      Oled_Clr();
      flag--;
      if(flag<0)
        flag=4;
    }
    if(Key_Check==2)
    {
      Oled_Clr();
      flag++;
      if(flag>4)
        flag=0;
    }
    if(Key_Check==5)
    {
      Oled_Clr();
      return;     
    }  
  }
}
/*-----------------------------------------------------------
  * @author  陈德宁
  * @date    2018.3.24
  * @note    修改参数界面（大佬）
-----------------------------------------------------------*/
char *string[7]={"TURN_P","TURN_D","SPED_P","SPED_I","SPEED ","Limit ","PO_DAO"};
void Alter_Menu(void)
{
 static int flag1 = 0;
 Oled_Clr();
 while(1)
 {
   for(int i=0;i<7;i++)
   {
     OLED_ShowStr(0,i,string[i],flag1!=i);
   }
   Variate_Display(40,0,Inductance_Kp);
   Variate_Display(40,1,Inductance_Kd);
   Variate_Display(40,2,PID_SPEED_P);
   Variate_Display(40,3,PID_SPEED_I);
   Variate_Display(40,4,Car_Set_Speed_1);
   Variate_Display(40,5,Limit_Speed);
   Variate_Display(40,6,Po_Dao_Speed);
   Check_Key();
   if(Key_Check==3)
    {
      flag1--;
      if(flag1<0)
        flag1=6;
    }
    if(Key_Check==4)
    {
      flag1++;
      if(flag1>6)
        flag1=0;
    }
   if(Key_Check==1)
   {
     switch(flag1)
     {
       case 0:
       Inductance_Kp--;     break;
       case 1:
       Inductance_Kd--;     break;
       case 2:
       PID_SPEED_P--;       break;
       case 3:
       PID_SPEED_I--;       break;
       case 4:
       Car_Set_Speed_1--;   break;
       case 5:
       Limit_Speed--;       break;
       case 6:
       Po_Dao_Speed--;      break;
       default:
                            break;    
     }
   }
     if(Key_Check==2)
   {
     switch(flag1)
     {
       case 0:
       Inductance_Kp++;     break;
       case 1:
       Inductance_Kd++;     break;
       case 2:
       PID_SPEED_P++;       break;
       case 3:
       PID_SPEED_I++;       break;
       case 4:
       Car_Set_Speed_1++;   break;
       case 5:
       Limit_Speed++;       break;
       case 6:
       Po_Dao_Speed++;      break;
       default:
                            break;    
     }
   }  
   if(Key_Check==5)
    {
      Oled_Clr();
      return;     
    }  
 } 
}
/*-----------------------------------------------------------*/