/*
 * ServoCtl.c
 *
 *  Created on: 2018年9月21日
 *      Author: admin
 */
#include "ServoCtl.h"



void servo_init(uint16_t *initAngle)
{
    I2C0_Init();

    PCA9685_set_freq(50);

    int i = 0;
    for(i = 0;i<6;i++)
        servo_n_angle_set(i,initAngle[i]);
}

void hand_set_servo()
{
    extern uint8_t  servoUpdate;//global variables, defined in main.c
    extern uint16_t servoVal[6];//

    while(1){
        while(!servoUpdate)
            ;
        servoUpdate = 0;

        servo_all_update(servoVal);
    }
}

void servo_n_angle_set(uint8_t n, uint16_t angle)
{
    static uint16_t angle_last[16] = {760,850,600,770,1475,1000};//机械臂初始化位置

    uint16_t t = angle_last[n];
    //步进4表示舵机的分辨率
    while(1)
    {
        if(t - angle < -5)
            t+=5;
        else if(t - angle > 5)
            t-=5;
        else
        {
            PCA9685_pulse_us_set(n, t);
            break;
        }
        PCA9685_pulse_us_set(n, t);
        delay_ms(15);               //延时时间用以控制舵机运行速度
    }

    //保存此次舵机位置
    angle_last[n] = angle;
}
void servo_all_update(uint16_t *val)
{
    int i = 0;
    for(i=0;i<6;i++){
        servo_n_angle_set(i, val[i]);
    }
}

void goto_pos_1_middle()
{
    servo_n_angle_set(1,1070);
    servo_n_angle_set(0,1400);
    servo_n_angle_set(2,980);
    servo_n_angle_set(1,1350);
    servo_n_angle_set(2,1160);
    servo_n_angle_set(1,1680);
    servo_n_angle_set(2,1280);
    servo_n_angle_set(1,1770);
    servo_n_angle_set(5,1810);
    servo_n_angle_set(1,1170);
    servo_n_angle_set(2,680);
    servo_n_angle_set(1,870);
    servo_n_angle_set(0,2100);
}
void PCA9685_set_freq(float freq)
{
    uint8_t prescale;
    uint8_t oldmode, newmode;
    float prescaleval;

    //prescaleval = floor(25000000/(4096*freq*0.915)) - 1;
    prescaleval = 25000000;
    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval /= 0.915;
    prescaleval -= 1;
    prescale = (uint8_t)(prescaleval + 0.5);

    pca9685_reg_write(MODE1, 0x00);// restart

    pca9685_reg_read(MODE1, &oldmode);
    newmode = ( (oldmode&0x7F) | 0x10 );    // sleep
    pca9685_reg_write(MODE1, newmode);          // go to sleep
    pca9685_reg_write(PRE_SCALE, prescale);     // set the prescaler
    pca9685_reg_write(MODE1, oldmode);
    delay_ms(1);

    pca9685_reg_write(MODE1, oldmode | 0xa1);//开始工作
}

void PCA9685_set_PWM(uint8_t num, uint16_t on, uint16_t off)
{
    uint8_t on_H = on>>8;
    uint8_t on_L = on&0xFF;
    uint8_t off_H = off>>8;
    uint8_t off_L = off&0xFF;

    pca9685_reg_write(LED0_ON_L+4*num, on_L);
    pca9685_reg_write(LED0_ON_H+4*num, on_H);
    pca9685_reg_write(LED0_OFF_L+4*num, off_L);
    pca9685_reg_write(LED0_OFF_H+4*num, off_H);
}

void PCA9685_pulse_us_set(uint8_t num, uint16_t us)//50Hz,20ms
{
    uint16_t pulse = (uint16_t)(128*us/625);//(4096*us/20000)
    PCA9685_set_PWM(num, 0, pulse);
}

void pca9685_reg_write(uint8_t reg_add, uint8_t data)
{
    I2CWriteRegOneByte(PCA9685_I2C_ADD, PCA9685_ADD, reg_add, data);
}

void pca9685_reg_read(uint8_t reg_add, uint8_t *data)
{
    I2CReadRegOneByte(PCA9685_I2C_ADD, PCA9685_ADD, reg_add, data);
}
