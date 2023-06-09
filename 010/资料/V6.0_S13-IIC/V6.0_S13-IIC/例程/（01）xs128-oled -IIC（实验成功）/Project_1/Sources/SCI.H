#ifndef SCI_H
#define SCI_H

#include <MC9S12XS128.h>

/*=========波特率设置===========*/ /*  IREN==0时  BR = 16MHZ/(16 * 9600) = 104（总线频率为16M时）   */
#define   sci0bd    48       
                              //625---96M时是9600
                              //573---88M时是9600
                              //521---80M时是9600
                              //469---72M时是9600
                              //417---64M时是9600
                              //365---56M时是9600
                              //313---48M时是9600
                              //260---40M时是9600
                              //208---32M时是9600
                              //156---24M时是9600
                              
                              //313---96M时是19200
                              //286---88M时是19200
                              //260---80M时是19200
                              //234---72M时是19200
                              //208---64M时是19200
                              //182---56M时是19200
                              //156---48M时是19200
                              //130---40M时是19200
                              //104---32M时是19200
                              
                              //52-----96M时是115200
                              //48-----88M时是115200
                              //43-----80M时是115200
                              //39-----72M时是115200
                              //35-----64M时是115200
                              //30-----56M时是115200
                              //26-----48M时是115200
                              //22-----40M时是115200
                              //17-----32M时是115200
                              
                             
                             
void Sci_Init(void);
int Sci_Receive(void) ;
void Sci_Tx(unsigned int tx_date) ;                            
void Sci_Num(unsigned short num,unsigned short length);
void Sci_puts(unsigned char *string);
                             
#endif                             


/***************************************************************
*主函数写法参考，可以直接发送寄存器里的值，如发送AD的值
* Sci_Tx(ATD0DR0) ;
****************************************************************/

/*==============================================================
void main(void)
{
    Sci_Init();
    for(;;)
    {
        sci_r=Sci_Receive() ; //把接收的数据放在sci_r中
        Sci_Tx(sci_r) ;       //把接收到的数据又重新发回去
    }
}


==============================================================*/