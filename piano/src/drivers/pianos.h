/*=====================================
name    :   pianoSDL
function:   piano like violin
input   :   none
output  :   none
======================================*/
void pianoSDL()
{

    attenuation_factor=1;
    static uint16_t i, j, key[8],echo_time_out=0;
    int min,echo_pin_data,control_key_data;


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
            //clean old spectrum
            for(i = 0; i <2*N; i++)
                spectrum[j] = 0;
            //configure new spectrum
            for(i = 0; i < 8; i++)
            {
                if(key[i]==1)
                {
                    spectrum[music[i]] =80;
                    spectrum[music[i]/2] =30;
                    spectrum[music[i]*2] =30;
                }
            }
            //get time domain data
            fix_fft(&spectrum[0],&spectrum[N], log2N, 1);

            //add offset to echo_time_out negative number
            min=0;
            for(i=0;i<=(2*N);i++)
            {
                if(spectrum[i]<min)
                    min=spectrum[i];
            }
            for(i=0;i<=(2*N);i++)
            {
                spectrum[i]=spectrum[i]-min;
            }


            IntDisable(INT_TIMER0A);

            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,0);
            count=0;
            echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
            echo_time_out=0;
            while(!(echo_pin_data))
            {
                echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
               echo_time_out++;
               if(echo_time_out>10000)
                   break;
            }

            while(GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2))
            {
                count++;
                if(count>20000)
                    break;
            }
            memcpy(sound,spectrum,4*N);
            count/=10;
            count+=1280;
            TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / count);//set new freq
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

    static uint16_t i, j, key[8],echo_time_out=0,key_pre[8];
    int min,echo_pin_data,control_key_data;
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

                    if(key[i]!=key_pre[i])
                    {
                        UARTprintf("%d",i+1);
                        attenuation_factor=1;
                    }
                }
            }

            if(attenuation_factor<0.06)
                attenuation_factor=0.000001;
            else
                attenuation_factor=attenuation_factor-0.03;

            for(i=0; i<8; i++)
            {
                key_pre[i]=key[i];
            }
            //jisuanpinlv
            fix_fft(&spectrum[0],&spectrum[N], log2N, 1);
            min=0;
            for(i=0;i<=(2*N);i++)
            {
                if(spectrum[i]<min)
                    min=spectrum[i];
            }
            for(i=0;i<=(2*N);i++)
            {
                spectrum[i]=spectrum[i]-min;
            }


            IntDisable(INT_TIMER0A);
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,0);
            count=0;
            echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
            echo_time_out=0;
            while(!(echo_pin_data))
            {
               echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
               echo_time_out++;
               if(echo_time_out>1000)
                   break;
            }

            while(GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2))
            {
                count++;
                if(count>4999)
                    break;
            }
            memcpy(sound,spectrum,4*N);
            count=count/1000;
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
/*=====================================
name    :   piano
function:   basic piano
input   :   none
output  :   none
======================================*/
void piano()
{
    //yingjianchushihua
    //dakaishizhong
    //xian shi cai dan
    static uint16_t i, j, key[8],key_pre[8];
    int min,control_key_data;

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
        {//jianceanjian

            //GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,GPIO_PIN_3);

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

                    if(key[i]!=key_pre[i])
                    {
                        UARTprintf("%d",i+1);
                        attenuation_factor=1;
                    }
                }
            }

            if(attenuation_factor<0.06)
                attenuation_factor=0.000001;
            else
                attenuation_factor=attenuation_factor-0.03;

            for(i=0; i<8; i++)
            {
                key_pre[i]=key[i];
            }
            //jisuanpinlv
            fix_fft(&spectrum[0],&spectrum[N], log2N, 1);
            min=0;
            for(i=0;i<=(2*N);i++)
            {
                if(spectrum[i]<min)
                    min=spectrum[i];
            }
            for(i=0;i<=(2*N);i++)
            {
                spectrum[i]=spectrum[i]-min;
            }


            IntDisable(INT_TIMER0A);
            //GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,0);
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
/*=====================================
name    :   pianoVOL
function:   piano with adjustable volume
input   :   none
output  :   none
======================================*/
void pianoVOL()
{
    //yingjianchushihua
    //dakaishizhong
    //xian shi cai dan
    static uint16_t i, j, key[8],echo_time_out=0;
    int min,echo_pin_data,control_key_data;
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
            min=0;
            for(i=0;i<=(2*N);i++)
            {
                if(spectrum[i]<min)
                    min=spectrum[i];
            }
            for(i=0;i<=(2*N);i++)
            {
                spectrum[i]=spectrum[i]-min;
            }

            for(i=0;i<=(2*N);i++)
            {
                 spectrum[i]=spectrum[i]*0.0002*count;
            }


            IntDisable(INT_TIMER0A);
            GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_3,0);
            count=0;
            echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
            echo_time_out=0;
            while(!(echo_pin_data))
            {
               echo_pin_data=GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2);
               echo_time_out++;
               if(echo_time_out>1000)
                   break;
            }

            while(GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_2))
            {
                count++;
                if(count>5000)
                    break;
            }
            memcpy(sound,spectrum,4*N);
            IntEnable(INT_TIMER0A);
        }
        else
            break;
    }

    TimerDisable(TIMER0_BASE, TIMER_A);
}

