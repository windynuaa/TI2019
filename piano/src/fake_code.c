

/*
void main()//涓荤▼搴�
{
	hw_init();//纭欢鍒濆鍖�
	sw_init();//杞欢鍒濆鍖�
	menu();//涓昏彍鍗曠▼搴�
}

void menu()
{
	while()//寰幆
	{
		get_key()//鍒ゆ柇鎺у埗鎸夐敭
		switch(key)//
			case_sub_prom()杩涘叆瀛愬姛鑳�
		draw_menu()//缁樺埗涓昏彍鍗�
	}

}

void bluetooth()
{
	draw_menu();//缁樺埗涓昏彍鍗�
	set_mux();//閰嶇疆妯℃嫙閫夋嫨鍣�
	while()
	{
		get_key();//鑾峰彇鎸夐敭
		wait_for_exit();//绛夊緟閫�鍑烘寚浠�
	}
}

void piano()
{
	draw_menu();//缁樺埗鑿滃崟
	enable_timer_dac();//浣胯兘da杈撳嚭鏃堕挓
	while()
	{
		nop//绌洪棽绛夊緟
	}
}

void tuner()
{
	draw_menu();//缁樺埗鑿滃崟
	
	while()
	{
		get_key()
		switch()
		{
			tune_pasv()//琚姩鏍￠
			tune_actv()//涓诲姩鏍￠
			nop_();//绌洪棽绛夊緟
		}
			
	}
}

void tune_pasv()
{
	draw_menu();//缁樺埗鑿滃崟
	enable_adc();//浣胯兘妯℃暟杞崲
	enable_timer_dac();//璁剧疆鏁版ā閲囨牱鏃堕挓
	while()
	{
		get_key();//鍒ゆ柇鎺у埗鎸夐敭
		wait_for_exit();//绛夊緟閫�鍑烘寚浠�
	}
}
void tune_atcv()
{
	draw_menu();//缁樺埗鑿滃崟
	enable_pwm();//浣胯兘PWM杈撳嚭
	while()
	{
		get_key();//鍒ゆ柇鎺у埗鎸夐敭
		set_pwm_freq();//璁剧疆PWM杈撳嚭棰戠巼
		wait_for_exit();//绛夊緟閫�鍑烘寚浠�
	}
}

void keydect() interrupt //涓柇绋嬪簭 鏈夐敭鎸変笅鏃朵腑鏂�
{
	get_value();//鍒ゆ柇鐞撮敭
	set_spec();//鍚堟垚棰戣氨
	#disp_spec();//鏄剧ず棰戣氨
	disable_timer_dac();//绂佺敤闊抽杈撳嚭瀹氭椂鍣�
	*sound_output_enable=0;绂佺敤杈撳嚭
	ifft();//鍚堟垚鏃跺煙淇″彿
	set_timer_dac_freq();//璁剧疆杈撳嚭閲囨牱鐜�
	*sound_output_enable=1;浣胯兘杈撳嚭
	enable_timer_dac();//鍚敤闊抽杈撳嚭瀹氭椂鍣�
}


void timer_dac() interrupt //闊抽杈撳嚭瀹氭椂鍣ㄤ腑鏂�
{
	if(*sound_output_enable)//鍒ゆ柇鏄惁杈撳嚭
		spi_write(sound_buffer[sound_sp++]);//寮�濮嬫暟妯¤浆鎹�
	if(*sound_output_rst)//杈撳嚭閲嶇疆
		sound_sp=0;
	if(!(sound_sp<SOUND_BUFFER_SIZE))//鎸囬拡寰幆
		sound_sp=0;
}

void timer_adc() interrupt //鏁版ā閲囨牱瀹氭椂鍣ㄤ腑鏂�
{

	if(*tuner_input_enable)//鍒ゆ柇鏄惁閲囨牱
		tuner_buffer[tuner_sp++]=get_adc_value();//閲囨牱
	if(*tuner_output_rst)//閲囨牱閲嶇疆
		tuner_sp=0;
	if(tuner_sp==SOUND_BUFFER_SIZE)//鍗曟閲囨牱瀹屾垚
		sound_sp=0;
		fft();//璁＄畻棰戣氨
		cacl_freq();//璁＄畻棰戠巼
		disp_spec();//鏄剧ず棰戣氨
}

//鍒濆鍖栫被
hw_init();//纭欢鍒濆鍖�
sw_init();//杞欢鍒濆鍖�

//鍏朵粬绫�
set_mux();//閰嶇疆妯℃嫙閫夋嫨鍣�

//鎸夐敭鍒ゆ柇绫�
get_value();//鍒ゆ柇鐞撮敭
get_key();//鍒ゆ柇鎺у埗鎸夐敭

//PWM杈撳嚭
//enable_pwm();//浣胯兘PWM杈撳嚭
//set_pwm_freq();//璁剧疆PWM杈撳嚭棰戠巼

//DSP绫�
fft();//蹇�熷倕閲屽彾鍙樻崲
ifft();//鍚堟垚鏃跺煙淇″彿
cacl_freq();//璁＄畻棰戠巼
set_spec();//鍚堟垚棰戣氨
disp_spec();//鏄剧ず棰戣氨

//AD/DA绫�
enable_timer_dac();//鍚敤闊抽杈撳嚭瀹氭椂鍣�
disable_timer_dac();//绂佺敤闊抽杈撳嚭瀹氭椂鍣�
set_timer_dac_freq();//璁剧疆闊抽杈撳嚭閲囨牱鐜�
da_out()//妯℃暟杞崲杈撳嚭
enable_adc();//浣胯兘妯℃暟杞崲
enable_timer_adc();//鍚敤鏁版ā閲囨牱鏃堕挓
disable_timer_adc();//绂佺敤鏁版ā閲囨牱鏃堕挓
set_timer_adc_freq();//璁剧疆闊抽杈撳叆閲囨牱鐜�

//鍥惧儚鏄剧ず绫�
draw_menu();//缁樺埗鑿滃崟
led_wirte_char()//鐢讳竴涓瓧绗�
led_wirte_line()//鐢讳竴琛屽瓧绗�

//搴曞眰鍗忚绫�
spi_read()//SPI鍐欐暟鎹�
spi_write()//SPI璇绘暟鎹�
*/
