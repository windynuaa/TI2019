//*****************************************************************************
//
// single_ended.c - Example demonstrating how to configure the ADC for
//                  single ended operation.
//
// Copyright (c) 2010-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 2.1.4.178 of the Tiva Firmware Development Package.
//
//*****************************************************************************
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
volatile static uint32_t smpl=0;
volatile static uint16_t spectrum[128];
volatile static uint16_t sound[128];

uint32_t pui32ADC0Value[1];

volatile uint8_t display_buffer[8][16][8]={0};
volatile uint8_t dictionary_buffer[255][8]={{0x00,0x00,0x3E,0x48,0x48,0x3E,0x00,0x00}};

volatile  uint32_t ui32SysClock;
//hardware driver

#include "oled.h"
#include "hwinit.h"


void timer_pwm(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    //HWREGBITW(&g_ui32Flags, 0) ^= 1;
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
}
void timer_adc(void)
{
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    //HWREGBITW(&g_ui32Flags, 0) ^= 1;
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
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
    static int16_t alti[128];
    static int16_t x[N], fx[2*N];
    static uint16_t icnt,max,maxn;
    icnt=0;
    while(1)
    {
        ADCProcessorTrigger(ADC0_BASE, 3);
        while(!ADCIntStatus(ADC0_BASE, 3, false));
        ADCIntClear(ADC0_BASE, 3);
        ADCSequenceDataGet(ADC0_BASE, 3, pui32ADC0Value);if(icnt != 128)
        {
            alti[icnt] = pui32ADC0Value[0];
            fx[icnt] = alti[icnt];
            fx[N+icnt] = 0;
            icnt++;
        }
        else
        {
            fix_fft(&fx[0], &fx[N], log2N, 0);
            break;
        }
        SysCtlDelay(ui32SysClock / 12000);
    }
    max=0;
    for(icnt=5;icnt<128;icnt++)
    {
        if(fx[icnt]>max)
        {
            max=fx[icnt];
            maxn=icnt;
        }
    }
    return maxn/128*4000;
}
void turner()
{
    double freq;
    //yingjianchushihua
    //xian shi cai dan
    disp_sent(7,"++++++++++++++++",16);//display a string
    disp_sent(6,"++---Turner---++",16);//display a string
    disp_sent(5,"++++++++++++++++",16);//display a string
    disp_sent(4,"+-----Freq-----+",16);//display a string
    disp_sent(3,"+--------------+",16);//display a string
    disp_sent(2,"+--------------+",16);//display a string
    disp_sent(1,"+--------------+",16);//display a string
    disp_sent(0,"back-------sound",16);//display a string
    while(1)
    {
        //jianceanjian

        //caijipinlv
        freq=adc_get_value();
        //jisuanpinlv

        //xianshipinlv

    }
    //jieshuchuli

}

void piano()
{
    //yingjianchushihua
    //dakaishizhong
    //xian shi cai dan

    while(1)
    {
        //jianceanjian

        //caijipinlv

        //jisuanpinlv

        //xianshipinlv

    }
    //jieshuchuli

}






int main(void)
{
    int i,j;
    char a[16]={0};
    ui32SysClock=SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
    InitConsole();
    adc_init();
    timer_init();
    spi_init();
    oled_init();
    disp_char(1,1,0);
    clean_led_all(1);
    while(1)
    {
        refresh_led();
        for(i=0;i<64;i++)
        {
            for(j=0;j<128;j++)
            {
                refresh_led();
                disp_sent(0,a,10);
            }
        }
    }
}

