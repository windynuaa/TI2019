/*
 * hwinit.h
 *
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author:
 */


#ifndef SRC_DRIVERS_HWINIT_H_
#define SRC_DRIVERS_HWINIT_H_

//
//  name : console_init
//  Initialize the USART output
//

void console_init(void)
{
    //configure pins
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    //configure USART controller
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 115200, 16000000);
}

//
//  name : gpio_init
//  Initialize the input port
//

void gpio_init()
{
        //piano key
#define A0 GPIO_PIN_1
#define A1 GPIO_PIN_4
#define A2 GPIO_PIN_5
#define A3 GPIO_PIN_0
#define A4 GPIO_PIN_1
#define A5 GPIO_PIN_2
#define A6 GPIO_PIN_0
#define A7 GPIO_PIN_1

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
        //control key *3
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
        GPIOPinTypeGPIOInput(GPIO_PORTL_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);// K1 K2 K3
        //ultrasonic module
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
        GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE,GPIO_PIN_3);// trig
        GPIOPinTypeGPIOInput(GPIO_PORTN_BASE,GPIO_PIN_2);//  echo



}
//
//  name : adc_init
//  Initialize the ADC module
//
void adc_init()
{
    //configure input pin
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
    //configure ADC controller
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);
}
//
//  name : timer_init
//  Initialize timers
//

void timer_init()
{
    //configure sound output timer
   SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
   TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
   TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / 5120);//sample rate = 5120
   TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
   TimerClockSourceSet(TIMER0_BASE,TIMER_CLOCK_SYSTEM);
   //configure sample timer
   SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
   TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
   TimerLoadSet(TIMER1_BASE, TIMER_A, ui32SysClock / 2560);//sample rate = 5120
   TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
   //enable interrupt
   IntMasterEnable();
   IntEnable(INT_TIMER0A);
   IntEnable(INT_TIMER1A);
}

//
//  name : spi_init
//  Initialize the SPI module
//
void spi_init()
{
    //FOR DISPLAY 10KHz

    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);//clk
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);//cs
    GPIOPinConfigure(GPIO_PA4_SSI0XDAT0);//do
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_5);//cmd
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_6);//rst
    GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_4);
    SSIClockSourceSet(SSI0_BASE,SSI_CLOCK_SYSTEM);
    SSIConfigSetExpClk(SSI0_BASE,ui32SysClock,SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,10000,8);
    SSIEnable(SSI0_BASE);

    //FOR DAC 50MHz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB5_SSI1CLK);//clk
    GPIOPinConfigure(GPIO_PB4_SSI1FSS);//cs
    GPIOPinConfigure(GPIO_PE4_SSI1XDAT0);//do
    GPIOPinTypeSSI(GPIO_PORTB_BASE,GPIO_PIN_5 | GPIO_PIN_4);
    GPIOPinTypeSSI(GPIO_PORTE_BASE, GPIO_PIN_4);
    SSIClockSourceSet(SSI1_BASE,SSI_CLOCK_SYSTEM);
    SSIConfigSetExpClk(SSI1_BASE,ui32SysClock,SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,50000000,12);
    SSIEnable(SSI1_BASE);
}




#endif /* SRC_DRIVERS_HWINIT_H_ */
