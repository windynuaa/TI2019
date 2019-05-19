/*=====================================
name    :   pianoSDL
function:   piano like violin
input   :   none
output  :   none
======================================*/
void pianoSDL()
{

    attenuation_factor=1;
    static uint16_t i,echo_time_out=0;
    static uint8_t key[8],key_pre[8];
    int spectrum_min_value,echo_pin_data,control_key_data;


    oled_disp_sent(7,"++++++++++++++++",16);//display a string
    oled_disp_sent(6,"++    Piano   ++",16);//display a string
    oled_disp_sent(5,"++++ funnny ++++",16);//display a string
    oled_disp_sent(4,"++    *===*   ++",16);//display a string
    oled_disp_sent(3,"+     *   *    +",16);//display a string
    oled_disp_sent(2,"++     O**    ++",16);//display a string
    oled_disp_sent(1,"++++++++++++++++",16);//display a string
    oled_disp_sent(0,"back       sound",16);//display a string
    oled_refresh();

    TimerEnable(TIMER0_BASE, TIMER_A);
    while(1)
    {
        control_key_data=GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
        control_key_data=control_key_data>>1;
        if(control_key_data==2)
        {
            //send a trig to ultrasonic
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,GPIO_PIN_3);
            //detect key

            key[0] = (uint8_t) GPIOPinRead(GPIO_PORTG_BASE,A0);
            key[1] = (uint8_t) GPIOPinRead(GPIO_PORTK_BASE,A1);
            key[2] = (uint8_t) GPIOPinRead(GPIO_PORTK_BASE,A2);
            key[3] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A3);
            key[4] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A4);
            key[5] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A5);
            key[6] = (uint8_t) GPIOPinRead(GPIO_PORTH_BASE,A6);
            key[7] = (uint8_t) GPIOPinRead(GPIO_PORTH_BASE,A7);

            //clean old spectrum
            memset(spectrum,0,4*N);//memset is faster than "for" loop
            //detect key state
            if(memcmp(key_pre,key,8))//enter here if key state changed
            {
                //configure new spectrum
                for(i = 0; i < 8; i++)
                {
                    if(!key[i])
                    {
                        spectrum[music[i]] =80;
                    }
                }
                //save key
                memcpy(key_pre,key,8);//memcpy is faster than "for" loop
                //get time domain data (sound data)
                fix_fft(&spectrum[0],&spectrum[N], log2N, 1);
                //add offset to echo_time_out negative number
                spectrum_min_value=0;
                for(i=0;i<=N;i++)
                {
                    if(spectrum[i]<spectrum_min_value)
                        spectrum_min_value=spectrum[i];
                }
                for(i=0;i<=N;i++)
                {
                    spectrum[i]=spectrum[i]-spectrum_min_value;
                }
                //apply new sound data
                memcpy(sound,spectrum,4*N);//memcpy is faster than "for" loop
            }

            delay(DELAY_TIME);
            ultra_sonic_time_count=0;
            echo_time_out=0;

            IntDisable(INT_TIMER0A);//disable interrupt to avoid disturbing
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,0);//release trig to start distance detect

            echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
            while(!(echo_pin_data))//Wait until a high level occur on echo pin
            {
                echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
                if(echo_time_out++>1000)//wait too long,quit!
                   break;
            }

            while(GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2))//Wait until the high level disappear
            {
                if(ultra_sonic_time_count++>5000)////wait too long,quit!
                    break;
            }
            ultra_sonic_time_count+=1280;
            TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / ultra_sonic_time_count);//set new freq
            IntEnable(INT_TIMER0A);
        }
        else
            break;
    }
    TimerDisable(TIMER0_BASE, TIMER_A);
}
/*=====================================
name    :   pianoADV
function:   piano with 5 octaves
input   :   none
output  :   none
======================================*/
void pianoADV()
{

    static uint16_t i,echo_time_out=0;
    static uint8_t key[8],key_pre[8];
    int echo_pin_data,control_key_data,spectrum_min_value;
    oled_disp_sent(7,"++++++++++++++++",16);//display a string
    oled_disp_sent(6,"++    Piano   ++",16);//display a string
    oled_disp_sent(5,"++++Advanced++++",16);//display a string
    oled_disp_sent(4,"++    *===*   ++",16);//display a string
    oled_disp_sent(3,"+     *   *    +",16);//display a string
    oled_disp_sent(2,"++     *O*    ++",16);//display a string
    oled_disp_sent(1,"++++++++++++++++",16);//display a string
    oled_disp_sent(0,"back       sound",16);//display a string
    oled_refresh();
    TimerEnable(TIMER0_BASE, TIMER_A);
    while(1)
    {
        control_key_data=GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
        control_key_data=control_key_data>>1;
        if(control_key_data==1)
        {
            //send a trig to ultrasonic
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,GPIO_PIN_3);
            //detect key
            key[0] = (uint8_t) GPIOPinRead(GPIO_PORTG_BASE,A0);
            key[1] = (uint8_t) GPIOPinRead(GPIO_PORTK_BASE,A1);
            key[2] = (uint8_t) GPIOPinRead(GPIO_PORTK_BASE,A2);
            key[3] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A3);
            key[4] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A4);
            key[5] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A5);
            key[6] = (uint8_t) GPIOPinRead(GPIO_PORTH_BASE,A6);
            key[7] = (uint8_t) GPIOPinRead(GPIO_PORTH_BASE,A7);

            //clean old spectrum
            memset(spectrum,0,4*N);//memset is faster than "for" loop
            //detect key state
            if(memcmp(key_pre,key,8))//enter here if key state changed
            {
                //configure new spectrum
                for(i = 0; i < 8; i++)
                {
                    if(!key[i])//
                    {
                        spectrum[music[i]] =80;
                        if(key[i]!=key_pre[i])
                        {
                             UARTprintf("%d",i+1);
                        }
                    }
                }

                //save key
                memcpy(key_pre,key,8);//memcpy is faster than "for" loop
                //get time domain data (sound data)
                fix_fft(&spectrum[0],&spectrum[N], log2N, 1);
                //add offset to avoid negative number
                spectrum_min_value=0;
                for(i=0;i<=N;i++)
                {
                    if(spectrum[i]<spectrum_min_value)
                        spectrum_min_value=spectrum[i];
                }
                for(i=0;i<=N;i++)
                {
                    spectrum[i]=spectrum[i]-spectrum_min_value;
                }

                //
                attenuation_factor=1;
                //
                ultra_sonic_time_count=0;
                echo_time_out=0;

                IntDisable(INT_TIMER0A);//disable interrupt to avoid disturbing
                GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,0);//release trig to start distance detect
                echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
                while(!(echo_pin_data))//Wait until a high level occur on echo pin
                {
                    echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
                    if(echo_time_out++>1000)//wait too long,quit!
                       break;
                }

                while(GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2))//Wait until the high level disappear
                {
                    if(ultra_sonic_time_count++>4999)////wait too long,quit!
                        break;
                }
                ultra_sonic_time_count=ultra_sonic_time_count/1000;
                ultra_sonic_time_count=1280*pow(2,ultra_sonic_time_count);
                TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / ultra_sonic_time_count);
                //apply new sound data
                memcpy(sound,spectrum,4*N);//memcpy is faster than "for" loop
                IntEnable(INT_TIMER0A);
            }

            if(attenuation_factor>0.06)
                attenuation_factor-=ATTUN_DEC;
        }
        else
            break;
    }
    TimerDisable(TIMER0_BASE, TIMER_A);
}
/*=====================================
name    :   piano
function:   basic piano
input   :   none
output  :   none
======================================*/
void piano()
{
    static uint16_t i;
    static uint8_t key[8],key_pre[8];
    int control_key_data,spectrum_min_value;

    oled_disp_sent(7,"++++++++++++++++",16);//display a string
    oled_disp_sent(6,"++    Piano   ++",16);//display a string
    oled_disp_sent(5,"++++++++++++++++",16);//display a string
    oled_disp_sent(4,"++    *===*   ++",16);//display a string
    oled_disp_sent(3,"+     *   *    +",16);//display a string
    oled_disp_sent(2,"++     OO*    ++",16);//display a string
    oled_disp_sent(1,"++++++++++++++++",16);//display a string
    oled_disp_sent(0,"back       sound",16);//display a string
    oled_refresh();
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / 5120);
    TimerEnable(TIMER0_BASE, TIMER_A);
    while(1)
    {
        control_key_data=GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
        control_key_data=control_key_data>>1;
        if(control_key_data==3)
        {
            //detect key
            key[0] = (uint8_t) GPIOPinRead(GPIO_PORTG_BASE,A0);
            key[1] = (uint8_t) GPIOPinRead(GPIO_PORTK_BASE,A1);
            key[2] = (uint8_t) GPIOPinRead(GPIO_PORTK_BASE,A2);
            key[3] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A3);
            key[4] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A4);
            key[5] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A5);
            key[6] = (uint8_t) GPIOPinRead(GPIO_PORTH_BASE,A6);
            key[7] = (uint8_t) GPIOPinRead(GPIO_PORTH_BASE,A7);
            //clean old spectrum
            memset(spectrum,0,4*N);//memset is faster than "for" loop
            //detect key state
            if(memcmp(key_pre,key,8))//enter here if key state changed
            {
                //configure new spectrum
                for(i = 0; i < 8; i++)
                {
                    if(!key[i])//
                    {
                        spectrum[music[i]*2]    =30;
                        spectrum[music[i]]      =80;
                        spectrum[music[i]/2]    =30;
                        if(key[i]!=key_pre[i])
                        {
                             UARTprintf("%d",i+1);
                        }
                    }
                }

                //save key
                memcpy(key_pre,key,8);//memcpy is faster than "for" loop
                //get time domain data (sound data)
                fix_fft(&spectrum[0],&spectrum[N], log2N, 1);
                //add offset to avoid negative number
                spectrum_min_value=0;
                for(i=0;i<=N;i++)
                {
                    if(spectrum[i]<spectrum_min_value)
                        spectrum_min_value=spectrum[i];
                }
                for(i=0;i<=N;i++)
                {
                    spectrum[i]=spectrum[i]-spectrum_min_value;
                }

                attenuation_factor=1;
                IntDisable(INT_TIMER0A);
                //apply new sound data
                memcpy(sound,spectrum,4*N);//memcpy is faster than "for" loop
                IntEnable(INT_TIMER0A);
            }
            if(attenuation_factor>0.06)
                attenuation_factor-=ATTUN_DEC;
        }
        else
            break;

    }
    TimerDisable(TIMER0_BASE, TIMER_A);
}
/*=====================================
name    :   pianoVOL
function:   piano with adjustable volume and frequency

input   :   none
output  :   none
======================================*/
void pianoVOL()
{
    static uint16_t i,echo_time_out=0;
    static uint8_t key[8],key_pre[8];
    int echo_pin_data,control_key_data,spectrum_min_value;
    oled_disp_sent(7,"++++++++++++++++",16);//display a string
    oled_disp_sent(6,"++    Piano   ++",16);//display a string
    oled_disp_sent(5,"++++ VOLUME ++++",16);//display a string
    oled_disp_sent(4,"++    *===*   ++",16);//display a string
    oled_disp_sent(3,"+     *   *    +",16);//display a string
    oled_disp_sent(2,"++     **O    ++",16);//display a string
    oled_disp_sent(1,"++++++++++++++++",16);//display a string
    oled_disp_sent(0,"back       sound",16);//display a string
    oled_refresh();
    TimerEnable(TIMER0_BASE, TIMER_A);
    while(1)
    {
        attenuation_factor=1;
        control_key_data=GPIOPinRead(GPIO_PORTL_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
        control_key_data=control_key_data>>1;
        if(control_key_data==4)
        {
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,GPIO_PIN_3);
            //detect key
            key[0] = (uint8_t) GPIOPinRead(GPIO_PORTG_BASE,A0);
            key[1] = (uint8_t) GPIOPinRead(GPIO_PORTK_BASE,A1);
            key[2] = (uint8_t) GPIOPinRead(GPIO_PORTK_BASE,A2);
            key[3] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A3);
            key[4] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A4);
            key[5] = (uint8_t) GPIOPinRead(GPIO_PORTM_BASE,A5);
            key[6] = (uint8_t) GPIOPinRead(GPIO_PORTH_BASE,A6);
            key[7] = (uint8_t) GPIOPinRead(GPIO_PORTH_BASE,A7);
            //clean old spectrum
            memset(spectrum,0,4*N);//memset is faster than "for" loop
            //detect key state
            if(memcmp(key_pre,key,8))//enter here if key state changed
            {
                //configure new spectrum
                for(i = 0; i < 8; i++)
                {
                    if(!key[i])//
                    {
                        spectrum[music[i]*2]    =30;
                        spectrum[music[i]]      =80;
                        spectrum[music[i]/2]    =30;
                        if(key[i]!=key_pre[i])
                        {
                             UARTprintf("%d",i+1);
                        }
                    }
                }

                //save key
                memcpy(key_pre,key,8);//memcpy is faster than "for" loop
                //get time domain data (sound data)
                fix_fft(&spectrum[0],&spectrum[N], log2N, 1);
                //add offset to avoid negative number
                spectrum_min_value=0;
                for(i=0;i<=N;i++)
                {
                    if(spectrum[i]<spectrum_min_value)
                        spectrum_min_value=spectrum[i];
                }
                for(i=0;i<=N;i++)
                {
                    spectrum[i]=spectrum[i]-spectrum_min_value;
                }
                //change volume
                for(i=0;i<=N;i++)
                {
                    spectrum[i]=spectrum[i]*0.0002*ultra_sonic_time_count;
                }
                attenuation_factor=1;
                ultra_sonic_time_count=0;
                echo_time_out=0;

                IntDisable(INT_TIMER0A);//disable interrupt to avoid disturbing
                GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,0);//release trig to start distance detect
                echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
                while(!(echo_pin_data))//Wait until a high level occur on echo pin
                {
                    echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
                    if(echo_time_out++>1000)//wait too long,quit!
                       break;
                }

                while(GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2))//Wait until the high level disappear
                {
                    if(ultra_sonic_time_count++>4999)////wait too long,quit!
                        break;
                }
                ultra_sonic_time_count=ultra_sonic_time_count/1000;
                ultra_sonic_time_count=1280*pow(2,ultra_sonic_time_count);
                TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / ultra_sonic_time_count);
                //apply new sound data
                memcpy(sound,spectrum,4*N);//memcpy is faster than "for" loop
                IntEnable(INT_TIMER0A);
            }
            delay(DELAY_TIME);
            echo_time_out=0;
            ultra_sonic_time_count=0;
            IntDisable(INT_TIMER0A);
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,0);//release trig to start distance detect
            echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
            while(!(echo_pin_data))//Wait until a high level occur on echo pin
            {
                echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
                if(echo_time_out++>1000)//wait too long,quit!
                   break;
            }

            while(GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2))//Wait until the high level disappear
            {
                if(ultra_sonic_time_count++>4999)////wait too long,quit!
                    break;
            }
            IntEnable(INT_TIMER0A);
        }
        else
            break;
    }

    TimerDisable(TIMER0_BASE, TIMER_A);
}

