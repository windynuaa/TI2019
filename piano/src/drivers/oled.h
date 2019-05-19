/*
 * oled.h
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author:
 */

#ifndef SRC_DRIVERS_OLED_H_
#define SRC_DRIVERS_OLED_H_

/*
name    :   oled_write_cmd
function:   write a command byte to oled controller
input   :
        val: data to be sent
output  :   none
*/
void oled_write_cmd(uint32_t val)
{
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,0);//write command when cmd = 0
    SysCtlDelay(ui32SysClock / 3000);
    SSIDataPut(SSI0_BASE,val);
}
/*
name    :   oled_write_data
function:   write a data byte to oled controller
input   :
        val: data to be sent
output  :   none
*/
void oled_write_data(uint32_t val)
{
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,GPIO_PIN_5);//write command when cmd = 1
    SysCtlDelay(ui32SysClock / 3000);
    SSIDataPut(SSI0_BASE,val);
}
/*
name    :   oled_init
function:   initialize oled controller
input   :   none
output  :   none
*/
void oled_init()
{
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,0);//let cmd=0
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,0);//let rst=0 to reset oled
    SysCtlDelay(ui32SysClock / 1);//delay 1 second
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,GPIO_PIN_6);//let rst=1 to enable oled
    SysCtlDelay(ui32SysClock / 10);//delay 0.1 second

    //please reference SSD1306 command table
    SSIDataPut(SSI0_BASE,0X81);
    SSIDataPut(SSI0_BASE,0xFF);

    SSIDataPut(SSI0_BASE,0X8D);
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
    SSIDataPut(SSI0_BASE,0xC8);

    SSIDataPut(SSI0_BASE,0XAF);
    SysCtlDelay(ui32SysClock / 1);
    SSIDataPut(SSI0_BASE,0xA4);
}

/*
name    :   oled_disp_char
function:   display a char on screen
input   :
        x:  x-location 0~127
        y:  y-location 0~7
        c:  char to display
output  :   none
*/
void oled_disp_char(int x,int y,char c)//display a char
{
    memcpy(display_buffer[y][x],dictionary_buffer[c-32],8);
}

/*
name    :   oled_disp_sent
function:   display a string on screen
input   :
        y:  y-location 0~7
        *buf:the pointer of the string
        len: the length of the string
output  :   none
*/
void oled_disp_sent(int y,char *buf,int len)//display a string
{
    int i;
    if(len>16)
        UARTprintf("out range!\n");
    else
    {
        for(i=0;i<len;i++)
        {
            oled_disp_char(i,y,buf[i]);
        }
    }
}

/*=====================================
name    :   oled_refresh
function:   refresh oled's ram to display correct content
            whenever the display_buffer is changed, this function should be called to enable the change .
input   :   none
output  :   none
======================================*/
void oled_refresh()
{
    int y,x,k;
    for(y=0;y<8;y++)
    {
        oled_write_cmd(0xb0+y);
        oled_write_cmd(0x10);
        oled_write_cmd(0x00);
        for(x=0;x<16;x++)
        {
            for(k=0;k<8;k++)
            {
                oled_write_data(display_buffer[y][x][k]);
            }
        }
    }
}

/*
name    :   oled_clean_all
function:   clean oled buffer
input   :   none
output  :   none
*/
void oled_clean_all()//clean oled ram
{
    int i,x,y;
    oled_write_cmd(0xb0);
    oled_write_cmd(0x10);
    oled_write_cmd(0x00);
    for(x=0;x<16;x++)
    {
        for(y=0;y<8;y++)
        {
            for(i=0;i<8;i++)
                display_buffer[y][x][i]=0;
        }
    }
}



#endif /* SRC_DRIVERS_OLED_H_ */
