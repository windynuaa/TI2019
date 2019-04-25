/*
 * hwinit.h
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: 17392
 */

#ifndef SRC_DRIVERS_HWINIT_H_
#define SRC_DRIVERS_HWINIT_H_

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
void gpio_init()
{

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
    TimerLoadSet(TIMER2_BASE, TIMER_A, ui32SysClock / 1280);
    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();

    /*
    TimerEnable(TIMER0_BASE, TIMER_A);
    TimerEnable(TIMER1_BASE, TIMER_A);
    */
    TimerEnable(TIMER2_BASE, TIMER_A);

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
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);//cs
    GPIOPinConfigure(GPIO_PA4_SSI0XDAT0);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_5);//cmd
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_6);//rst
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
    SSIConfigSetExpClk(SSI1_BASE,ui32SysClock,SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,50000000,12);
    SSIEnable(SSI1_BASE);
}




#endif /* SRC_DRIVERS_HWINIT_H_ */
