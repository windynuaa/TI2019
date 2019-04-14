


void main()//主程序
{
	hw_init();//硬件初始化
	sw_init();//软件初始化
	menu();//主菜单程序
}

void menu()
{
	while()//循环
	{
		get_key()//判断控制按键
		switch(key)//
			case_sub_prom()进入子功能
		draw_menu()//绘制主菜单
	}

}

void bluetooth()
{
	draw_menu();//绘制主菜单
	set_mux();//配置模拟选择器
	while()
	{
		get_key();//获取按键
		wait_for_exit();//等待退出指令
	}
}

void piano()
{
	draw_menu();//绘制菜单
	enable_timer_dac();//使能da输出时钟
	while()
	{
		nop//空闲等待
	}
}

void tuner()
{
	draw_menu();//绘制菜单
	
	while()
	{
		get_key()
		switch()
		{
			tune_pasv()//被动校频
			tune_actv()//主动校频
			nop_();//空闲等待
		}
			
	}
}

void tune_pasv()
{
	draw_menu();//绘制菜单
	enable_adc();//使能模数转换
	enable_timer_dac();//设置数模采样时钟
	while()
	{
		get_key();//判断控制按键
		wait_for_exit();//等待退出指令
	}
}
void tune_atcv()
{
	draw_menu();//绘制菜单
	enable_pwm();//使能PWM输出
	while()
	{
		get_key();//判断控制按键
		set_pwm_freq();//设置PWM输出频率
		wait_for_exit();//等待退出指令
	}
}

void keydect() interrupt //中断程序 有键按下时中断
{
	get_value();//判断琴键
	set_spec();//合成频谱
	#disp_spec();//显示频谱
	disable_timer_dac();//禁用音频输出定时器
	*sound_output_enable=0;禁用输出
	ifft();//合成时域信号
	set_timer_dac_freq();//设置输出采样率
	*sound_output_enable=1;使能输出
	enable_timer_dac();//启用音频输出定时器
}


void timer_dac() interrupt //音频输出定时器中断
{
	if(*sound_output_enable)//判断是否输出
		spi_write(sound_buffer[sound_sp++]);//开始数模转换
	if(*sound_output_rst)//输出重置
		sound_sp=0;
	if(!(sound_sp<SOUND_BUFFER_SIZE))//指针循环
		sound_sp=0;
}

void timer_adc() interrupt //数模采样定时器中断
{

	if(*tuner_input_enable)//判断是否采样
		tuner_buffer[tuner_sp++]=get_adc_value();//采样
	if(*tuner_output_rst)//采样重置
		tuner_sp=0;
	if(tuner_sp==SOUND_BUFFER_SIZE)//单次采样完成
		sound_sp=0;
		fft();//计算频谱
		cacl_freq();//计算频率
		disp_spec();//显示频谱
}

//初始化类
hw_init();//硬件初始化
sw_init();//软件初始化

//其他类
set_mux();//配置模拟选择器

//按键判断类
get_value();//判断琴键
get_key();//判断控制按键

//PWM输出
enable_pwm();//使能PWM输出
set_pwm_freq();//设置PWM输出频率

//DSP类
fft();//快速傅里叶变换
ifft();//合成时域信号
cacl_freq();//计算频率
set_spec();//合成频谱
disp_spec();//显示频谱

//AD/DA类
enable_timer_dac();//启用音频输出定时器
disable_timer_dac();//禁用音频输出定时器
set_timer_dac_freq();//设置音频输出采样率
da_out()//模数转换输出
enable_adc();//使能模数转换
enable_timer_adc();//启用数模采样时钟
disable_timer_adc();//禁用数模采样时钟
set_timer_adc_freq();//设置音频输入采样率

//图像显示类
draw_menu();//绘制菜单
led_wirte_char()//画一个字符
led_wirte_line()//画一行字符

//底层协议类
spi_read()//SPI写数据
spi_write()//SPI读数据