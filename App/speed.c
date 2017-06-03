/*  Include-------------------------------------------------------------------*/
	#include "common.h"
	#include "include.h"
	#include "MK60_it.h"
    #include "speed.h"
    #include <math.h>

/*  定义变量------------------------------------------------------------------*/
    int pid_speed,ideal,speed_max,speed_min,zhidao_speed,wandao_speed,brake_speed;
    int pwm,speed,djsd;
    uint8 zhidao_flag,wandao_flag;
    uint8 speed_array[5];
    int et,et1,et2,pianyi_duty,angel_duty;
    float  Kp=12,Ki=0.9,Kd=3;

float jueduizhif(float x) 
{ 
    x=x>=0?x:-x;
    
    return x; 
} 

void set_speed(int speed)//输出速度
{
    if(speed>=0)
    {
        ftm_pwm_duty(MOTORFTM,MOTORFTM_B,speed);    //正转 占空比 1000代表百分百
        ftm_pwm_duty(MOTORFTM,MOTORFTM_A,0);        //反转
    }
    else 
    {
        ftm_pwm_duty(FTM0,FTM_CH3,0);
        ftm_pwm_duty(FTM0,FTM_CH2,0);
    }
#if 0
    if(speed<0)
    {
        ftm_pwm_duty(FTM0,FTM_CH3,0);
        ftm_pwm_duty(FTM0,FTM_CH2,abs_jdz(speed));
    }
#endif
}

void get_pulse(void)//输入速度,编码器获得速度
{
    //Servo_count_1[0]=(int)(Servo_count_1[0]*0.4+Servo_count_1[1]*0.3+\
    //                       Servo_count_1[2]*0.2+Servo_count_1[3]*0.1);
    djsd = speed_array[0];
    LCD_Show_Number(36,4,djsd);
}

int Getspeed(int ideal,int now)//处理速度PID,输入now为电机目前速度djsd，ideal为设置目标速度
{ 
    if(now<ideal) pid_speed++;
    else pid_speed--;
    if(pid_speed>200) pid_speed=200;
    if(pid_speed<0) pid_speed=0;
    return pid_speed;
}
