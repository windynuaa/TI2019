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
#include "utils/uartstdio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#define USER_LED1  GPIO_PIN_0
#define USER_LED2  GPIO_PIN_1

volatile uint32_t g_ui32SysClock;
volatile uint32_t g_ui32Flags;
volatile uint32_t ui32SysClock;
uint32_t pui32ADC0Value[1];

void InitConsole(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 115200, 16000000);
}

void timer_pwm(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    HWREGBITW(&g_ui32Flags, 0) ^= 1;
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, g_ui32Flags);
}
void timer_adc(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    HWREGBITW(&g_ui32Flags, 0) ^= 1;
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, g_ui32Flags);
}
void timer_dac(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    HWREGBITW(&g_ui32Flags, 0) ^= 1;
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, g_ui32Flags);
}

void adc_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);
}

void timer_init()
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / 2 / 10);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, ui32SysClock / 2 / 10);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER2_BASE, TIMER_A, ui32SysClock / 2 / 10);
    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();
    /*
    TimerEnable(TIMER0_BASE, TIMER_A);
    TimerEnable(TIMER1_BASE, TIMER_A);
    TimerEnable(TIMER2_BASE, TIMER_A);
    */
    IntEnable(INT_TIMER0A);
    IntEnable(INT_TIMER1A);
    IntEnable(INT_TIMER2A);

}
void spi_init()
{
    //FOR DISPLAY
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0XDAT0);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_5);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_4);
    SSIClockSourceSet(SSI0_BASE,SSI_CLOCK_SYSTEM);
    SSIConfigSetExpClk(SSI0_BASE,ui32SysClock,SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,10000,8);
    SSIEnable(SSI0_BASE);
    //FOR DAC
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB5_SSI1CLK);
    GPIOPinConfigure(GPIO_PB4_SSI1FSS);
    GPIOPinConfigure(GPIO_PE4_SSI1XDAT0);
    GPIOPinTypeUART(GPIO_PORTB_BASE,GPIO_PIN_5 | GPIO_PIN_4);
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4);
    SSIClockSourceSet(SSI1_BASE,SSI_CLOCK_SYSTEM);
    SSIConfigSetExpClk(SSI1_BASE,ui32SysClock,SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,10000,8);
    SSIEnable(SSI1_BASE);
}
void oled_init()
{
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,0);
    SSIDataPut(SSI0_BASE,0X81);
    SSIDataPut(SSI0_BASE,0xFF);//shezhiduibidu
    SSIDataPut(SSI0_BASE,0X8D);//dakaidianzibeng
    SSIDataPut(SSI0_BASE,0X14);
    SSIDataPut(SSI0_BASE,0XAF);//kaixianshi
    SSIDataPut(SSI0_BASE,0xA5);//ceshipingmu
}
void oled_write_cmd(uint32_t val)
{
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,0);
    SSIDataPut(SSI0_BASE,val);
}
void oled_write_data(uint32_t val)
{
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,GPIO_PIN_5);
    SSIDataPut(SSI0_BASE,val);
}

void adc_get_value()
{
    ADCProcessorTrigger(ADC0_BASE, 3);
    while(!ADCIntStatus(ADC0_BASE, 3, false));
    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, pui32ADC0Value);
}

int main(void)
{

    ui32SysClock=SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

    InitConsole();
    adc_init();
    timer_init();
    spi_init();
    oled_init();

    while(1)
    {

        UARTprintf("AIN0 = %4d\r", pui32ADC0Value[0]);
        // This function provides a means of generating a constant length
        // delay.  The function delay (in cycles) = 3 * parameter.  Delay
        //250ms arbitrarily.
        SSIDataPut(SSI0_BASE,0X14);
        //SysCtlDelay(ui32SysClock / 12);
    }
}
