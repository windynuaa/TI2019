
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
#include "hwinit.h"
#include "oled.h"
volatile static uint32_t smpl=0;
volatile static uint32_t adc_smpl=0;
volatile double freq[1];
 static int16_t adc_buffer[N*2];
 static uint16_t spectrum[128];
 static uint16_t sound[128];

 volatile static uint32_t g_ui32Flags=0;

 uint32_t pui32ADC0Value[1];

volatile uint8_t display_buffer[8][16][8]={0};

volatile  uint32_t ui32SysClock;
//hardware driver




void timer_pwm(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    HWREGBITW(&g_ui32Flags, 2) ^= 1;
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_2, g_ui32Flags);
}
void timer_adc(void)//samp_rate 2048 smp/s
{
    volatile uint32_t *b;
    static int16_t i,max,maxn;
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    b=&adc_smpl;
    ADCProcessorTrigger(ADC0_BASE, 3);
    while(!ADCIntStatus(ADC0_BASE, 3, false));
    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, pui32ADC0Value);
    if(*b<N)
    {
        adc_buffer[*b]=pui32ADC0Value[0];
        (*b)++;
    }
    else
    {
        *b=0;
        fix_fft(&adc_buffer[0], &adc_buffer[N], log2N, 0);
        max=0;
        maxn=0;
        for(i=0;i<N;i++)
        {
            if(max<adc_buffer[i])
            {
                max=adc_buffer[i];
                maxn=i;
            }
        }
        maxn=maxn*2048;
        *freq=(double)maxn/(2*N);
    }

}
void timer_dac(void)
{
    volatile uint32_t *b;
    b=&smpl;
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    *b=*b+1;
    if(*b>127)
        *b=0;
    SSIDataPut(SSI1_BASE,sound[*b]);
}
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
    maxn=maxn*4000;
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
        //jianceanjian

        //caijipinlv
        //freq=adc_get_value();

        if(freq[0]<20)
            disp_sent(3,"+    ERROR     +",16);//display a string

        UARTprintf("%f",freq[0]);
        //jisuanpinlv

        //xianshipinlv
        refresh_led();
    }
    //jieshuchuli
    TimerDisable(TIMER1_BASE, TIMER_A);
}

void piano()
{
    //yingjianchushihua
    //dakaishizhong
    //xian shi cai dan
    TimerEnable(TIMER0_BASE, TIMER_A);
    while(1)
    {
        //jianceanjian

        //caijipinlv

        //jisuanpinlv

        //xianshipinlv

    }
    //jieshuchuli
    TimerDisable(TIMER0_BASE, TIMER_A);
}






int main(void)
{
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

    //clean_led_all(1);
    while(1)
    {
        turner();

    }
}

