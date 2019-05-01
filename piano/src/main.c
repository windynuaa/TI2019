
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "utils/uartstdio.h"
#include "math.h"
#include "string.h"
#include "FFT.h"
#include "code.h"


volatile static uint32_t smpl=0;
volatile static uint32_t adc_smpl=0;

volatile double freq[1];

 static int16_t adc_buffer[N*2];
 static int16_t spectrum[N*2];
 static int16_t sound[N*2];

volatile static uint32_t g_ui32Flags=0;

 uint32_t pui32ADC0Value[1];

volatile uint8_t display_buffer[8][16][8]={0};

volatile  uint32_t ui32SysClock;
int count;
//hardware driver
#include "hwinit.h"
#include "oled.h"
#include "timers.h"



double adc_get_value()
{
    static int16_t alti[N];
    static int16_t  fx[2*N];
    static uint16_t icnt,max,maxn;
    icnt=0;
    while(1)
    {
        ADCProcessorTrigger(ADC0_BASE, 3);
        while(!ADCIntStatus(ADC0_BASE, 3, false));
        ADCIntClear(ADC0_BASE, 3);
        ADCSequenceDataGet(ADC0_BASE, 3, pui32ADC0Value);
        if(icnt<N)
        {
            alti[icnt] = pui32ADC0Value[0];
            fx[icnt] = alti[icnt];
            fx[N+icnt] = 0;
            icnt++;
        }
        else
        {
            icnt=0;
            fix_fft(&fx[0], &fx[N], log2N, 0);
            break;
        }
        SysCtlDelay(ui32SysClock / 12000);
    }
    max=0;
    for(icnt=5;icnt<(N/2);icnt++)
    {
        if(fx[icnt]>max)
        {
            max=fx[icnt];
            maxn=icnt;
        }
    }
    maxn=maxn*2560;
    return (double)maxn/N;
}
void turner()
{
    //double freq;
    //yingjianchushihua
    //xian shi cai dan
    disp_sent(7,"++++++++++++++++",16);//display a string
    disp_sent(6,"++   Turner   ++",16);//display a string
    disp_sent(5,"++++++++++++++++",16);//display a string
    disp_sent(4,"+     Freq     +",16);//display a string
    disp_sent(3,"+              +",16);//display a string
    disp_sent(2,"+              +",16);//display a string
    disp_sent(1,"++++++++++++++++",16);//display a string
    disp_sent(0,"back       sound",16);//display a string
    refresh_led();
    TimerEnable(TIMER1_BASE, TIMER_A);
    while(1)
    {
        if(GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_4)&GPIO_PIN_4)
        {    //jianceanjian

            //caijipinlv
            //freq=adc_get_value();

            SysCtlDelay(ui32SysClock / 1);
            //jisuanpinlv
            IntDisable(INT_TIMER1A);
            //xianshipinlv
            //refresh_led_line(3);
            refresh_led();
            IntEnable(INT_TIMER1A);
        }
        else
            break;
    }
    //jieshuchuli
    TimerDisable(TIMER1_BASE, TIMER_A);
}

/*
void freq_adj()
{
       if()
       {

       }
       else
       {

       }
}
*/
void pianoSDL()
{
    //yingjianchushihua
    //dakaishizhong
    //xian shi cai dan
    static uint16_t i, j, key[8];
    int max,kk;
    volatile uint32_t *keyr=GPIO_PORTN_BASE;
    static uint16_t music[8] = {105,117,132,140,157,176,197,210};
    disp_sent(7,"++++++++++++++++",16);//display a string
    disp_sent(6,"++    Piano   ++",16);//display a string
    disp_sent(5,"++++ funnny ++++",16);//display a string
    disp_sent(4,"++    *===*   ++",16);//display a string
    disp_sent(3,"+     *   *    +",16);//display a string
    disp_sent(2,"++   ** **    ++",16);//display a string
    disp_sent(1,"++++++++++++++++",16);//display a string
    disp_sent(0,"back       sound",16);//display a string
    refresh_led();
    TimerEnable(TIMER0_BASE, TIMER_A);
    while(1)
    {

        if(GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_5)&GPIO_PIN_5)
        {//jianceanjian

            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,GPIO_PIN_3);

            if(!GPIOPinRead(GPIO_PORTG_BASE,A0))
                key[0] = 1;
            else
                key[0] = 0;
            if(!GPIOPinRead(GPIO_PORTK_BASE,A1))
                key[1] = 1;
            else
                key[1] = 0;
            if(!GPIOPinRead(GPIO_PORTK_BASE,A2))
                key[2] = 1;
            else
                key[2] = 0;
            if(!GPIOPinRead(GPIO_PORTM_BASE,A3))
                key[3] = 1;
            else
                key[3] = 0;
            if(!GPIOPinRead(GPIO_PORTM_BASE,A4))
                key[4] = 1;
            else
                key[4] = 0;
            if(!GPIOPinRead(GPIO_PORTM_BASE,A5))
                key[5] = 1;
            else
                key[5] = 0;
            if(!GPIOPinRead(GPIO_PORTH_BASE,A6))
                key[6] = 1;
            else
                key[6] = 0;
            if(!GPIOPinRead(GPIO_PORTH_BASE,A7))
                key[7] = 1;
            else
                key[7] = 0;
            for(j = 0; j <2*N; j++)
                spectrum[j] = 0;
            for(i = 0; i < 8; i++)
            {
                if(key[i]==1)
                {
                    spectrum[music[i]] =80;
                    spectrum[music[i]*2] =30;
                }
            }
            //jisuanpinlv
            fix_fft(&spectrum[0],&spectrum[N], log2N, 1);
            max=0;
            for(i=0;i<=(2*N);i++)
            {
                if(spectrum[i]>max)
                    max=spectrum[i];
            }
            for(i=0;i<=(2*N);i++)
            {
                spectrum[i]+=max;
            }


            IntDisable(INT_TIMER0A);
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,0);
            count=0;
            kk=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
            while(!(kk))
               kk=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
            while(GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2))
            {
                count++;
                if(count>20000)
                    break;
            }
            memcpy(sound,spectrum,4*N);
            count/=10;
            count+=1280;
            TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / count);
            IntEnable(INT_TIMER0A);
            //xianshipinlv
        }
        else
            break;

    }
    //jieshuchuli
    TimerDisable(TIMER0_BASE, TIMER_A);
}

void pianoADV()
{
    //yingjianchushihua
    //dakaishizhong
    //xian shi cai dan
    static uint16_t i, j, key[8];
    int max,kk;
    volatile uint32_t *keyr=GPIO_PORTN_BASE;
    static uint16_t music[8] = {105,117,132,140,157,176,197,210};
    disp_sent(7,"++++++++++++++++",16);//display a string
    disp_sent(6,"++    Piano   ++",16);//display a string
    disp_sent(5,"++++Advanced++++",16);//display a string
    disp_sent(4,"++    *===*   ++",16);//display a string
    disp_sent(3,"+     *   *    +",16);//display a string
    disp_sent(2,"++   ** **    ++",16);//display a string
    disp_sent(1,"++++++++++++++++",16);//display a string
    disp_sent(0,"back       sound",16);//display a string
    refresh_led();
    TimerEnable(TIMER0_BASE, TIMER_A);
    while(1)
    {

        if(GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_5)&GPIO_PIN_5)
        {//jianceanjian

            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,GPIO_PIN_3);

            if(!GPIOPinRead(GPIO_PORTG_BASE,A0))
                key[0] = 1;
            else
                key[0] = 0;
            if(!GPIOPinRead(GPIO_PORTK_BASE,A1))
                key[1] = 1;
            else
                key[1] = 0;
            if(!GPIOPinRead(GPIO_PORTK_BASE,A2))
                key[2] = 1;
            else
                key[2] = 0;
            if(!GPIOPinRead(GPIO_PORTM_BASE,A3))
                key[3] = 1;
            else
                key[3] = 0;
            if(!GPIOPinRead(GPIO_PORTM_BASE,A4))
                key[4] = 1;
            else
                key[4] = 0;
            if(!GPIOPinRead(GPIO_PORTM_BASE,A5))
                key[5] = 1;
            else
                key[5] = 0;
            if(!GPIOPinRead(GPIO_PORTH_BASE,A6))
                key[6] = 1;
            else
                key[6] = 0;
            if(!GPIOPinRead(GPIO_PORTH_BASE,A7))
                key[7] = 1;
            else
                key[7] = 0;
            for(j = 0; j <2*N; j++)
                spectrum[j] = 0;
            for(i = 0; i < 8; i++)
            {
                if(key[i]==1)
                {
                    spectrum[music[i]] =80;
                    spectrum[music[i]*2] =30;
                }
            }
            //jisuanpinlv
            fix_fft(&spectrum[0],&spectrum[N], log2N, 1);
            max=0;
            for(i=0;i<=(2*N);i++)
            {
                if(spectrum[i]>max)
                    max=spectrum[i];
            }
            for(i=0;i<=(2*N);i++)
            {
                spectrum[i]+=max;
            }


            IntDisable(INT_TIMER0A);
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,0);
            count=0;
            kk=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
            while(!(kk))
               kk=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
            while(GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2))
            {
                count++;
                if(count>9998)
                    break;
            }
            memcpy(sound,spectrum,4*N);
            count=count/2000;
            count=1280*pow(2,count);
            TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / count);
            IntEnable(INT_TIMER0A);
            //xianshipinlv
        }
        else
            break;

    }
    //jieshuchuli
    TimerDisable(TIMER0_BASE, TIMER_A);
}
void piano()
{
    //yingjianchushihua
    //dakaishizhong
    //xian shi cai dan
    static uint16_t i, j, key[8];
    int max;
    static uint16_t music[8] = {105,117,132,140,157,176,197,210};
    disp_sent(7,"++++++++++++++++",16);//display a string
    disp_sent(6,"++    Piano   ++",16);//display a string
    disp_sent(5,"++++++++++++++++",16);//display a string
    disp_sent(4,"++    *===*   ++",16);//display a string
    disp_sent(3,"+     *   *    +",16);//display a string
    disp_sent(2,"++   ** **    ++",16);//display a string
    disp_sent(1,"++++++++++++++++",16);//display a string
    disp_sent(0,"back       sound",16);//display a string
    refresh_led();
    TimerEnable(TIMER0_BASE, TIMER_A);
    while(1)
    {

        if(GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_5)&GPIO_PIN_5)
        {//jianceanjian

            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,GPIO_PIN_3);

            if(!GPIOPinRead(GPIO_PORTG_BASE,A0))
                key[0] = 1;
            else
                key[0] = 0;
            if(!GPIOPinRead(GPIO_PORTK_BASE,A1))
                key[1] = 1;
            else
                key[1] = 0;
            if(!GPIOPinRead(GPIO_PORTK_BASE,A2))
                key[2] = 1;
            else
                key[2] = 0;
            if(!GPIOPinRead(GPIO_PORTM_BASE,A3))
                key[3] = 1;
            else
                key[3] = 0;
            if(!GPIOPinRead(GPIO_PORTM_BASE,A4))
                key[4] = 1;
            else
                key[4] = 0;
            if(!GPIOPinRead(GPIO_PORTM_BASE,A5))
                key[5] = 1;
            else
                key[5] = 0;
            if(!GPIOPinRead(GPIO_PORTH_BASE,A6))
                key[6] = 1;
            else
                key[6] = 0;
            if(!GPIOPinRead(GPIO_PORTH_BASE,A7))
                key[7] = 1;
            else
                key[7] = 0;
            for(j = 0; j <2*N; j++)
                spectrum[j] = 0;
            for(i = 0; i < 8; i++)
            {
                if(key[i]==1)
                {
                    spectrum[music[i]] =80;
                    spectrum[music[i]/2] =30;
                    spectrum[music[i]*2] =30;
                }
            }
            //jisuanpinlv
            fix_fft(&spectrum[0],&spectrum[N], log2N, 1);
            max=0;
            for(i=0;i<=(2*N);i++)
            {
                if(spectrum[i]>max)
                    max=spectrum[i];
            }
            for(i=0;i<=(2*N);i++)
            {
                spectrum[i]+=max;
            }


            IntDisable(INT_TIMER0A);
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,0);
            memcpy(sound,spectrum,4*N);
            IntEnable(INT_TIMER0A);
            //xianshipinlv
        }
        else
            break;

    }
    //jieshuchuli
    TimerDisable(TIMER0_BASE, TIMER_A);
}


void pianon()
{
    //yingjianchushihua
    //dakaishizhong
    //xian shi cai dan
    static uint16_t i, j, key[8];
    uint8_t key_reg,key_regl;
    static uint16_t music[8] = {105,117,132,140,157,176,197,210};
    disp_sent(7,"++++++++++++++++",16);//display a string
    disp_sent(6,"++    Piano   ++",16);//display a string
    disp_sent(5,"++++++++++++++++",16);//display a string
    disp_sent(4,"++   *=====*   ++",16);//display a string
    disp_sent(3,"+    *     *   +",16);//display a string
    disp_sent(2,"++  **   **   ++",16);//display a string
    disp_sent(1,"++++++++++++++++",16);//display a string
    disp_sent(0,"back       sound",16);//display a string
    refresh_led();
    TimerEnable(TIMER0_BASE, TIMER_A);
    while(1)
    {

        if(GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_5)&GPIO_PIN_5)
        {//jianceanjian

            key_reg=0;
            key_reg=GPIOPinRead(GPIO_PORTH_BASE,A6|A7);
            key_reg=key_reg<<6;
            key_reg|=GPIOPinRead(GPIO_PORTL_BASE,A0|A1|A2|A3|A4|A5);

            if(key_reg!=key_regl)
            {
                for(j = 0; j <2*N; j++)
                    spectrum[j] = 0;
                j=0;
                for(i = 1; i!=0 ; i<<1)
                {
                    if(key_reg&i)
                        spectrum[music[j]] =100;
                    j++;
                }
                UARTprintf("%x",key_reg);
                //jisuanpinlv

                fix_fft(&spectrum[0],&spectrum[N], log2N, 1);

                for(i=0;i<=(2*N);i++)
                {
                    spectrum[i]+=350;
                }

                IntDisable(INT_TIMER0A);
                memcpy(sound,spectrum,4*N);
                IntEnable(INT_TIMER0A);
                key_reg=key_regl;
            }

            //xianshipinlv
        }
        else
            break;

    }
    //jieshuchuli
    TimerDisable(TIMER0_BASE, TIMER_A);
}






int main(void)
{
    int i;
    ui32SysClock=SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

    InitConsole();
    adc_init();
    spi_init();
    oled_init();
    gpio_init();
    timer_init();

    disp_sent(7,"================",16);//display a string
    disp_sent(6,"++   Select   ++",16);//display a string
    disp_sent(5,"++  Function  ++",16);//display a string
    disp_sent(4,"++   Turner   ++",16);//display a string
    disp_sent(3,"++   Piano    ++",16);//display a string
    disp_sent(2,"================",16);//display a string
    disp_sent(1,"1234567890",16);//display a string
    refresh_led();
    while(1)
    {
        if(GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_4)&GPIO_PIN_4)
        {
            turner();
                disp_sent(7,"================",16);//display a string
                disp_sent(6,"++   Select   ++",16);//display a string
                disp_sent(5,"++  Function  ++",16);//display a string
                disp_sent(4,"++   Turner   ++",16);//display a string
                disp_sent(3,"++   Piano    ++",16);//display a string
                disp_sent(2,"================",16);//display a string
                disp_sent(1,"                ",16);//display a string
                refresh_led();
        }
        if(GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_5)&GPIO_PIN_5)
        {
            pianoSDL();
                disp_sent(7,"================",16);//display a string
                disp_sent(6,"++   Select   ++",16);//display a string
                disp_sent(5,"++  Function  ++",16);//display a string
                disp_sent(4,"++   Turner   ++",16);//display a string
                disp_sent(3,"++   Piano    ++",16);//display a string
                disp_sent(2,"================",16);//display a string
                disp_sent(1,"                ",16);//display a string
                refresh_led();
        }
    }
}

