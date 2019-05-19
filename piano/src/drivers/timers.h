/*
 * timers.h
 *
 *  Created on: 2019Äê4ÔÂ26ÈÕ
 *      Author: 17392
 */

#ifndef SRC_DRIVERS_TIMERS_H_
#define SRC_DRIVERS_TIMERS_H_

/*=====================================
name    :   timer_adc
function:   ADC sample function
input   :   none
output  :   none
======================================*/
void timer_adc(void)
{
    volatile uint32_t *b;
     int16_t i,max;
     int32_t maxn;
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
        for(i=10;i<N;i++)
        {
            if(max<adc_buffer[i])
            {
                max=adc_buffer[i];
                maxn=i;
            }
        }
        maxn=maxn*2560;
        *freq=(double)maxn/(N);
        if(freq[0]<20)
           oled_disp_sent(3,"+    ERROR     +",16);//display a string
       else if(freq[0]>20&&freq[0]<=100)
           oled_disp_sent(3,"+    20-100    +",16);//display a string
       else if(freq[0]>100&&freq[0]<=200)
           oled_disp_sent(3,"+   100-200    +",16);//display a string
       else if(freq[0]>200&&freq[0]<=300)
           oled_disp_sent(3,"+   200-300    +",16);//display a string
       else if(freq[0]>300&&freq[0]<=400)
           oled_disp_sent(3,"+   300-400    +",16);//display a string
       else if(freq[0]>400&&freq[0]<=500)
           oled_disp_sent(3,"+   400-500    +",16);//display a string
       else if(freq[0]>500&&freq[0]<=600)
           oled_disp_sent(3,"+   500-600    +",16);//display a string
       else if(freq[0]>600&&freq[0]<=700)
           oled_disp_sent(3,"+   600-700    +",16);//display a string
       else if(freq[0]>700&&freq[0]<=800)
           oled_disp_sent(3,"+   700-800    +",16);//display a string
       else if(freq[0]>800&&freq[0]<=900)
           oled_disp_sent(3,"+   800-900    +",16);//display a string
       else if(freq[0]>900&&freq[0]<=1000)
           oled_disp_sent(3,"+   900-1000    +",16);//display a string
       else if(freq[0]>1000&&freq[0]<=1100)
           oled_disp_sent(3,"+   1000-1100    +",16);//display a string
       else if(freq[0]>1100&&freq[0]<=1200)
           oled_disp_sent(3,"+   1100-1200    +",16);//display a string
       else if(freq[0]>1200&&freq[0]<=1300)
           oled_disp_sent(3,"+   1200-1300    +",16);//display a string


    }

}
/*=====================================
name    :   timer_dac
function:   DAC output function

input   :   none
output  :   none
======================================*/
void timer_dac(void)
{
    uint32_t *dac_count;
    dac_count=&sample_count;//get the current output position of sound array
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    *dac_count=*dac_count+1;
    if(*dac_count>N)//
        *dac_count=0;
    SSIDataPut(SSI1_BASE,sound[*dac_count]*attenuation_factor);

}



#endif /* SRC_DRIVERS_TIMERS_H_ */
