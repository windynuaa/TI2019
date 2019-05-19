
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


volatile static uint32_t sample_count=0;
volatile static uint32_t adc_smpl=0;
static uint16_t music[8] = {105,117,132,140,157,176,197,210};
volatile double freq[1];

 static int16_t adc_buffer[N*2];
 static int16_t spectrum[N*2];
 static int16_t sound[N*2];

volatile static uint32_t g_ui32Flags=0;

uint32_t pui32ADC0Value[1];

volatile uint8_t display_buffer[8][16][8]={0};

volatile  uint32_t ui32SysClock;
int count;
volatile  double attenuation_factor=1;

//hardware driver
#include "hwinit.h"
#include "oled.h"
#include "timers.h"
#include "pianos.h"


void turner()
{
    //double freq;
    //yingjianchushihua
    //xian shi cai dan
    int i;
    oled_disp_sent(7,"++++++++++++++++",16);//display a string
    oled_disp_sent(6,"++   Turner   ++",16);//display a string
    oled_disp_sent(5,"++++++++++++++++",16);//display a string
    oled_disp_sent(4,"+     Freq     +",16);//display a string
    oled_disp_sent(3,"+              +",16);//display a string
    oled_disp_sent(2,"+              +",16);//display a string
    oled_disp_sent(1,"++++++++++++++++",16);//display a string
    oled_disp_sent(0,"back       sound",16);//display a string
    oled_refresh();
    TimerEnable(TIMER1_BASE, TIMER_A);
    while(1)
    {

        i=GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
        i=i>>1;
        if(i==0)
        {    //jianceanjian
            SysCtlDelay(ui32SysClock / 1);
            //jisuanpinlv
            IntDisable(INT_TIMER1A);
            oled_refresh();
            IntEnable(INT_TIMER1A);
        }
        else
            break;
    }
    //jieshuchuli
    TimerDisable(TIMER1_BASE, TIMER_A);
}


int main(void)
{
    int control_key_data;
    ui32SysClock=SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

    console_init();
    adc_init();
    spi_init();
    oled_init();
    gpio_init();
    timer_init();

    oled_disp_sent(7,"================",16);//display a string
    oled_disp_sent(6,"++   Select   ++",16);//display a string
    oled_disp_sent(5,"++  Function  ++",16);//display a string
    oled_disp_sent(4,"++   Turner   ++",16);//display a string
    oled_disp_sent(3,"++   Piano    ++",16);//display a string
    oled_disp_sent(2,"================",16);//display a string
    oled_disp_sent(1,"1234567890",16);//display a string
    oled_refresh();
    while(1)
    {
        control_key_data=GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
        control_key_data=control_key_data>>1;
        switch(i)
        {
        case 0:
            {
                    turner();
                    oled_disp_sent(7,"======5555======",16);//display a string
                    oled_disp_sent(6,"++   Select   ++",16);//display a string
                    oled_disp_sent(5,"++  Function  ++",16);//display a string
                    oled_disp_sent(4,"++   Turner   ++",16);//display a string
                    oled_disp_sent(3,"++   Piano    ++",16);//display a string
                    oled_disp_sent(2,"================",16);//display a string
                    oled_disp_sent(1,"                ",16);//display a string
                    oled_refresh();
                    break;
            }
        case 1:
            {
                pianoADV();
                    oled_disp_sent(7,"================",16);//display a string
                    oled_disp_sent(6,"++   Select   ++",16);//display a string
                    oled_disp_sent(5,"++  Function  ++",16);//display a string
                    oled_disp_sent(4,"++   Turner   ++",16);//display a string
                    oled_disp_sent(3,"++   Piano    ++",16);//display a string
                    oled_disp_sent(2,"================",16);//display a string
                    oled_disp_sent(1,"                ",16);//display a string
                    oled_refresh();
                    break;
             }

        case 2:
                    {
                        pianoSDL();
                            oled_disp_sent(7,"================",16);//display a string
                            oled_disp_sent(6,"++   Select   ++",16);//display a string
                            oled_disp_sent(5,"++  Function  ++",16);//display a string
                            oled_disp_sent(4,"++   Turner   ++",16);//display a string
                            oled_disp_sent(3,"++   Piano    ++",16);//display a string
                            oled_disp_sent(2,"================",16);//display a string
                            oled_disp_sent(1,"                ",16);//display a string
                            oled_refresh();
                            break;
                    }

        case 3:
                            {
                                piano();

                                    oled_disp_sent(7,"================",16);//display a string
                                    oled_disp_sent(6,"++   Select   ++",16);//display a string
                                    oled_disp_sent(5,"++  Function  ++",16);//display a string
                                    oled_disp_sent(4,"++   Turner   ++",16);//display a string
                                    oled_disp_sent(3,"++   Piano    ++",16);//display a string
                                    oled_disp_sent(2,"================",16);//display a string
                                    oled_disp_sent(1,"                ",16);//display a string
                                    oled_refresh();
                                    break;
                            }

        case 4:
                            {
                                pianoVOL();

                                    oled_disp_sent(7,"================",16);//display a string
                                    oled_disp_sent(6,"++   Select   ++",16);//display a string
                                    oled_disp_sent(5,"++  Function  ++",16);//display a string
                                    oled_disp_sent(4,"++   Turner   ++",16);//display a string
                                    oled_disp_sent(3,"++   Piano    ++",16);//display a string
                                    oled_disp_sent(2,"================",16);//display a string
                                    oled_disp_sent(1,"                ",16);//display a string
                                    oled_refresh();
                                    break;
                            }

        }
    }
}

