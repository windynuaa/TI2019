/*
 * oled.h
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: 17392
 */

#ifndef SRC_DRIVERS_OLED_H_
#define SRC_DRIVERS_OLED_H_


void oled_write_cmd(uint32_t val)
{
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,0);
    SysCtlDelay(ui32SysClock / 3000);
    SSIDataPut(SSI0_BASE,val);
}
void oled_write_data(uint32_t val)
{
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,GPIO_PIN_5);
    SysCtlDelay(ui32SysClock / 3000);
    SSIDataPut(SSI0_BASE,val);
}
void oled_init()
{
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,0);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,0);
    SysCtlDelay(ui32SysClock / 1);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,GPIO_PIN_6);
    SysCtlDelay(ui32SysClock / 10);
    SSIDataPut(SSI0_BASE,0X81);//shezhiduibidu
    SSIDataPut(SSI0_BASE,0xFF);

    SSIDataPut(SSI0_BASE,0X8D);//dakaidianzibeng
    SSIDataPut(SSI0_BASE,0X14);

    SSIDataPut(SSI0_BASE,0X20);
    SSIDataPut(SSI0_BASE,0X02);

    SSIDataPut(SSI0_BASE,0x21);
    SSIDataPut(SSI0_BASE,0);
    SSIDataPut(SSI0_BASE,127);

    SSIDataPut(SSI0_BASE,0X22);
    SSIDataPut(SSI0_BASE,0);
    SSIDataPut(SSI0_BASE,7);

    SSIDataPut(SSI0_BASE,0x40);

    SSIDataPut(SSI0_BASE,0XAF);//kaixianshi
    SSIDataPut(SSI0_BASE,0xA4);//ceshipingmu
}


void disp_char(int x,int y,char c)//display a char
{
    memcpy(display_buffer[y][x],dictionary_buffer[c],8);
}

void disp_sent(int y,char *buf,int len)//display a string
{
    int i;
    if(len>16)
        UARTprintf("out range!\n");
    else
    {
        for(i=0;i<len;i++)
        {
            disp_char(i,y,buf[i]);
        }
    }
}

void oled_draw_point(uint16_t x,uint16_t y,int on)
{
    uint8_t pg=y/8;
    uint8_t rg=0x80>>(y%8);
    disp_char(x,pg,rg);
}
void refresh_led()//refresh oled ram
{
    int i,j,k;
    for(i=0;i<8;i++)
    {
        oled_write_cmd(0xb0+i);
        UARTprintf("%x\n",0xb0+i);
        oled_write_cmd(0x10);
        oled_write_cmd(0x00);
        for(j=15;j>-1;j--)
        {
            for(k=0;k<8;k++)
            {
                oled_write_data(display_buffer[i][j][k]);
                UARTprintf("%x ",display_buffer[i][j][k]);
            }
        }
    }
}
void refresh_led_line(int y)//refresh oled ram
{
    int i,j,k;
    oled_write_cmd(0xb0+y);
    oled_write_cmd(0x10);
    oled_write_cmd(0x00);
    for(j=15;j>-1;j--)
    {
        for(k=0;k<8;k++)
        {
            oled_write_data(display_buffer[i][j][k]);
            UARTprintf("%x ",display_buffer[i][j][k]);
        }
    }
}

void clean_led_all(int y)//clean oled ram
{
    int i,j,k;
    oled_write_cmd(0xb0+y);
    oled_write_cmd(0x10);
    oled_write_cmd(0x00);
    for(j=0;j<16;j++)
    {
        for(k=0;k<8;k++)
        {
            for(i=0;i<8;i++)
                display_buffer[j][k][i]=0;
        }
    }
}
/*
 *
 *
 *      disp_sent(7,"----------------",16)//display a string
        disp_sent(6,"----------------",16)//display a string
        disp_sent(5,"----------------",16)//display a string
        disp_sent(4,"----------------",16)//display a string
        disp_sent(3,"----------------",16)//display a string
        disp_sent(2,"----------------",16)//display a string
        disp_sent(1,"----------------",16)//display a string
        disp_sent(0,"----------------",16)//display a string
 * */


#endif /* SRC_DRIVERS_OLED_H_ */
