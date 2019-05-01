/*
 * hwinit.h
 *
 *  ini
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author:
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
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
        GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE,GPIO_PIN_2);//PWM
        //key*8
#define A0 GPIO_PIN_1
#define A1 GPIO_PIN_4
#define A2 GPIO_PIN_5
#define A3 GPIO_PIN_0
#define A4 GPIO_PIN_1
#define A5 GPIO_PIN_2
#define A6 GPIO_PIN_0
#define A7 GPIO_PIN_1
        static uint8_t key[8];
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
        GPIOPinTypeGPIOInput(GPIO_PORTG_BASE,A0);
        GPIOPinTypeGPIOInput(GPIO_PORTK_BASE,A1);
        GPIOPinTypeGPIOInput(GPIO_PORTK_BASE,A2);
        GPIOPinTypeGPIOInput(GPIO_PORTM_BASE,A3);
        GPIOPinTypeGPIOInput(GPIO_PORTM_BASE,A4);
        GPIOPinTypeGPIOInput(GPIO_PORTM_BASE,A5);
        GPIOPinTypeGPIOInput(GPIO_PORTH_BASE,A6);
        GPIOPinTypeGPIOInput(GPIO_PORTH_BASE,A7);
        //control*3
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
        GPIOPinTypeGPIOInput(GPIO_PORTL_BASE,GPIO_PIN_4|GPIO_PIN_5);// PIANO | TURNER

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
        GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE,GPIO_PIN_3);// PIANO | TURNER
        GPIOPinTypeGPIOInput(GPIO_PORTN_BASE,GPIO_PIN_2);// PIANO | TURNER
        //select*2

        //debug*1

}
void gpio_initn()
{
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
        GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE,GPIO_PIN_2);//PWM
        //key*8
        /*
#define A0 GPIO_PIN_0   //PL0
#define A1 GPIO_PIN_1   //PL1
#define A2 GPIO_PIN_2   //PL2
#define A3 GPIO_PIN_3   //PL3
#define A4 GPIO_PIN_4   //PL4
#define A5 GPIO_PIN_5   //PL5
#define A6 GPIO_PIN_0   //PH0
#define A7 GPIO_PIN_1   //PH1
*/
       // static uint8_t key[8];
        //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
        //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
        //GPIOPinTypeGPIOInput(GPIO_PORTG_BASE,A0|A1|A2|A3|A4|A5);
        //GPIOPinTypeGPIOInput(GPIO_PORTH_BASE,A6|A7);

        //control*3
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
        GPIOPinTypeGPIOInput(GPIO_PORTL_BASE,GPIO_PIN_4|GPIO_PIN_5);// PIANO | TURNER
        //select*2

        //debug*1

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
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / 5120);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerClockSourceSet(TIMER0_BASE,TIMER_CLOCK_SYSTEM);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, ui32SysClock / 2560);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER2_BASE, TIMER_A, ui32SysClock / 1);
    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();


    //TimerEnable(TIMER0_BASE, TIMER_A);
    //TimerEnable(TIMER1_BASE, TIMER_A);
    //TimerEnable(TIMER2_BASE, TIMER_A);

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
    GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_4);
    SSIClockSourceSet(SSI0_BASE,SSI_CLOCK_SYSTEM);
    SSIConfigSetExpClk(SSI0_BASE,ui32SysClock,SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,10000,8);
    SSIEnable(SSI0_BASE);

    //FOR DAC
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB5_SSI1CLK);
    GPIOPinConfigure(GPIO_PB4_SSI1FSS);//cs
    GPIOPinConfigure(GPIO_PE4_SSI1XDAT0);
    GPIOPinTypeSSI(GPIO_PORTB_BASE,GPIO_PIN_5 | GPIO_PIN_4);
    GPIOPinTypeSSI(GPIO_PORTE_BASE, GPIO_PIN_4);
    SSIClockSourceSet(SSI1_BASE,SSI_CLOCK_SYSTEM);
    SSIConfigSetExpClk(SSI1_BASE,ui32SysClock,SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,50000000,12);
    SSIEnable(SSI1_BASE);
}




#endif /* SRC_DRIVERS_HWINIT_H_ */
