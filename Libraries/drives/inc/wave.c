#include "wave.h"
#include "KEA128_uart.h"

#define tx_num	32

unsigned char TxBuffer[tx_num];
unsigned char count=0; 

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

/**************************向物理串口发一个字节***************************************
*******************************************************************************/
unsigned char UART_Putc(unsigned char data)			//
{
	uart_putchar (uart2,data); //发送字节'A'
	return data;
}

unsigned char Uart1_Put_Char(unsigned char DataToSend)
{
	//TxBuffer[count++] = DataToSend;  
        uart_putchar (uart2,DataToSend);
	return DataToSend;
}

unsigned char Uart1_Put_Int16(uint16_t DataToSend)
{
	unsigned char sum = 0;
	TxBuffer[count++] = BYTE1(DataToSend);
	TxBuffer[count++] = BYTE0(DataToSend);
	sum += BYTE1(DataToSend);
	sum += BYTE0(DataToSend);
	return sum;
}


void Uart1_Send_AF(signed int aa,signed int bb,signed int cc,signed int dd,signed int ee,signed int ff,signed int gg,signed int hh)
{
	unsigned char sum = 0;
	count=0;
	sum += Uart1_Put_Char(0x88);
	sum += Uart1_Put_Char(0xAF);
	sum += Uart1_Put_Char(0x1C);
	sum += Uart1_Put_Char(BYTE1(aa));//1
	sum += Uart1_Put_Char(BYTE0(aa));
	sum += Uart1_Put_Char(BYTE1(bb));//2
	sum += Uart1_Put_Char(BYTE0(bb));
	sum += Uart1_Put_Char(BYTE1(cc));//3
	sum += Uart1_Put_Char(BYTE0(cc));
	sum += Uart1_Put_Char(BYTE1(dd));//4
	sum += Uart1_Put_Char(BYTE0(dd));
	sum += Uart1_Put_Char(BYTE1(ee));//5
	sum += Uart1_Put_Char(BYTE0(ee));
	sum += Uart1_Put_Char(BYTE1(ff));//6
	sum += Uart1_Put_Char(BYTE0(ff));
	Uart1_Put_Char(0);
	Uart1_Put_Char(0);
	Uart1_Put_Char(0);
	Uart1_Put_Char(0);
	Uart1_Put_Char(0);
	Uart1_Put_Char(0);
	sum += Uart1_Put_Char(BYTE1(gg));//7,4500->45'//这是姿态!!!
	sum += Uart1_Put_Char(BYTE0(gg));
	sum += Uart1_Put_Char(BYTE1(hh));//8
	sum += Uart1_Put_Char(BYTE0(hh));
	Uart1_Put_Char(0);
	Uart1_Put_Char(0);
	Uart1_Put_Char(0);
	Uart1_Put_Char(0);
	Uart1_Put_Char(0);
	Uart1_Put_Char(0);
	Uart1_Put_Char(sum);
}

void send_wave(void)
{
	char count_1=0;
	while(count_1<tx_num)
      UART_Putc(TxBuffer[count_1++]);
}
///////////////////////////////////////////////////////////////////////

void printhh(void)
  {
	UART_Putc(0x0d);       			 //output'CR'
	UART_Putc(0x0A);       			 //output'CR'
  } 
  
void print5n(unsigned int x)
  {	  
	   UART_Putc((x/10000)+0x30);           //计算万位数字
	   UART_Putc(((x%10000)/1000)+0x30);    //计算千位数字
	   UART_Putc(((x%1000)/100)+0x30);      //计算百位数字
	   UART_Putc(((x%100)/10)+0x30);        //计算十位数字
	   UART_Putc((x%10)+0x30);              //计算个位数字
  }
  
void print4n(unsigned int x)
  {	  
	  UART_Putc((x/1000)+0x30);    //计算千位数字
	  UART_Putc(((x%1000)/100)+0x30);      //计算百位数字
	  UART_Putc(((x%100)/10)+0x30);        //计算十位数字
	  UART_Putc((x%10)+0x30);              //计算个位数字
  }
void print3n(unsigned int x)
{
	UART_Putc((x/100)+0x30);      //计算百位数字
	UART_Putc(((x%100)/10)+0x30);        //计算十位数字
	UART_Putc((x%10)+0x30);   
}
void print2n(unsigned int x)
{
  
	UART_Putc((x/10)+0x30);        //计算十位数字
	UART_Putc((x%10)+0x30);   
}
